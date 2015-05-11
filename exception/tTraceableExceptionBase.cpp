//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/util/exception/tTraceableExceptionBase.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2014-01-24
 *
 */
//----------------------------------------------------------------------
#include "rrlib/util/exception/tTraceableExceptionBase.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#if __linux__
#include <execinfo.h>
#include <unistd.h>
#endif

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------
struct tMapEntry
{
  void *begin;
  void *end;
  std::string filename;
};

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------
const size_t cCALLS_TO_SKIP = 2;

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------
#ifndef __linux__
#define RRLIB_UTIL_EXCEPTION_DISABLE_TRACING
#endif

#ifndef RRLIB_UTIL_EXCEPTION_DISABLE_TRACING
namespace
{
std::string LookupSelf()
{
  char self[1024];
  std::stringstream link;
  link << "/proc/" << getpid() << "/exe";
  ssize_t length = readlink(link.str().c_str(), self, sizeof(self));
  if (static_cast<size_t>(length) < sizeof(self))
  {
    self[length] = 0;
  }
  return self;
}

std::vector<tMapEntry> ReadMaps() noexcept
{
  std::vector<tMapEntry> map_entries;

  try
  {
    std::stringstream proc_maps;
    proc_maps << "/proc/" << getpid() << "/maps";
    FILE *maps = fopen(proc_maps.str().c_str(), "r");
    if (maps)
    {
      char buffer[1024];
      while (!feof(maps))
      {
        if (fgets(buffer, sizeof(buffer), maps) != NULL)
        {
          std::stringstream input(buffer);
          char begin[64];
          std::string size;
          input >> begin >> size >> size >> size >> size;
          if (size != "0")
          {
            char *end = begin;
            for (; *end != '-'; ++end);
            *end++ = 0;
            map_entries.push_back({reinterpret_cast<void *>(strtoll(begin, nullptr, 16)), reinterpret_cast<void *>(strtoll(end, nullptr, 16)), ""});
            std::ws(input);
            std::getline(input, map_entries.back().filename);
          }
        }
      }
      fclose(maps);
      auto keep = map_entries.begin();
      for (auto read = keep; read != map_entries.end(); ++read)
      {
        if (read != keep)
        {
          if (read->begin == keep->end && read->filename == keep->filename)
          {
            keep->end = read->end;
          }
          else
          {
            *(++keep) = *read;
          }
        }
      }
      map_entries.erase(++keep, map_entries.end());
    }
  }
  catch (std::bad_alloc &error)
  {
    std::cerr << "Error during address mapping: " << error.what() << std::endl;
    map_entries.clear();
  }

  return map_entries;
}

std::string LookupLocation(void *address, const std::vector<tMapEntry> &map_entries, const std::string &self)
{
  try
  {
    for (auto it = map_entries.begin(); it != map_entries.end(); ++it)
    {
      if (it->begin <= address && address <= it->end)
      {
        std::string location;

        if (it->filename != self)
        {
          address = reinterpret_cast<void *>(reinterpret_cast<char *>(address) - reinterpret_cast<char *>(it->begin));
        }
        address = reinterpret_cast<void *>(reinterpret_cast<char *>(address) - 1);

        std::stringstream run_addr2line;
        std::string filename = it->filename;
        size_t position = 0;
        while ((position = filename.find_first_of("\\\"", position)) != filename.npos)
        {
          filename.insert(position, "\\");
          position += 2;
        }
        run_addr2line << "addr2line -fpCe \"" << filename << "\" " << address << " 2> /dev/null";
        FILE *pipe = popen(run_addr2line.str().c_str(), "r");
        if (pipe)
        {
          while (!feof(pipe))
          {
            char buffer[128];
            if (fgets(buffer, sizeof(buffer), pipe) != NULL)
            {
              location += buffer;
            }
          }
        }
        pclose(pipe);
        location.erase(location.find_last_not_of("\n\r\t ") + 1);

        if (!location.empty())
        {
          auto unknown = location.find("at ??");
          if (unknown != location.npos)
          {
            location.erase(unknown);
            location += "from " + it->filename;
          }
          return location;
        }
      }
    }
  }
  catch (std::bad_alloc &error)
  {
    std::cerr << "Error during location lookup: " << error.what() << std::endl;
  }

  return "??";
}

std::terminate_handler original_terminate = nullptr;

void terminate() noexcept
{
  try
  {
    auto exception = std::current_exception();
    if (exception)
    {
      std::rethrow_exception(exception);
    }
  }
  catch (const tTraceableExceptionBase &exception)
  {
    std::cerr << "=== Uncaught traceable exception ===\nBacktrace:\n" << exception.Backtrace() << std::endl;
  }
  catch (...)
  {}

  original_terminate();
  abort();
}

}

#endif

//----------------------------------------------------------------------
// tTraceableExceptionBase constructors
//----------------------------------------------------------------------
tTraceableExceptionBase::tTraceableExceptionBase() :
#if defined(NDEBUG) || defined(RRLIB_UTIL_EXCEPTION_DISABLE_TRACING)
  stack_trace_depth(0)
{}
#else
  stack_trace_depth(backtrace(this->stack_trace, cMAX_STACK_TRACE_DEPTH))
{
  if (!original_terminate)
  {
    original_terminate = std::set_terminate(terminate);
  }
}
#endif

//----------------------------------------------------------------------
// tTraceableExceptionBase destructor
//----------------------------------------------------------------------
tTraceableExceptionBase::~tTraceableExceptionBase()
{}

//----------------------------------------------------------------------
// tTraceableExceptionBase SomeExampleMethod
//----------------------------------------------------------------------
const char *tTraceableExceptionBase::Backtrace() const noexcept
{
  if (this->stack_trace_depth == 0)
  {
    return "<Backtrace was optimized out>";
  }

#ifndef RRLIB_UTIL_EXCEPTION_DISABLE_TRACING
  if (this->buffered_backtrace.empty())
  {
    try
    {
      std::stringstream backtrace;

      std::string self = LookupSelf();
      std::vector<tMapEntry> map_entries = ReadMaps();

      char address_example[64];
      snprintf(address_example, sizeof(address_example), "%p", reinterpret_cast<void *>(-1));
      char format_string[8];
      snprintf(format_string, sizeof(format_string), "0x%%0%zux", strlen(address_example) - 2);

      for (size_t i = cCALLS_TO_SKIP; i < this->stack_trace_depth; ++i)
      {
        char formatted_address[sizeof(address_example)];
        snprintf(formatted_address, sizeof(formatted_address), format_string, this->stack_trace[i]);
        backtrace << "#" << (i - cCALLS_TO_SKIP) << "  " << formatted_address;
        backtrace << " in " << LookupLocation(this->stack_trace[i], map_entries, self);
        backtrace << "\n";
      }

      this->buffered_backtrace = backtrace.str();
    }
    catch (std::bad_alloc &error)
    {
      std::cerr << "Error while creating backtrace: " << error.what() << std::endl;
      return "";
    }
  }
  return this->buffered_backtrace.c_str();
#else
  // just to suppress warnings, should never be reached
  return "<No backtrace available>";
#endif
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
