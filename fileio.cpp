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
/*!\file    rrlib/util/sFileIOUtils.cpp
 *
 * \author  Bernd Helge Schaefer
 * \author  Jens Wettach
 * \author  Tim Braun
 *
 * \date    2016-04-28
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#include "rrlib/util/fileio.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

extern "C"
{
#include <unistd.h>
#include <dirent.h>
#include <wordexp.h>
#include <sys/stat.h>
#include <sys/types.h>
}

#include "rrlib/util/join.h"
#include "rrlib/logging/messages.h"

//----------------------------------------------------------------------
// Debug
//----------------------------------------------------------------------
#include <cassert>
#include <cstring>
#include <cerrno>

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------
using namespace std;

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{
namespace fileio
{


//----------------------------------------------------------------------
// GetAllFilesInDirectory()
//----------------------------------------------------------------------
bool GetAllFilesInDirectory(const std::string& dir, std::vector<std::string> &files)
{
  DIR *dp;
  struct dirent *dirp;
  files.clear();
  if ((dp  = opendir(dir.c_str())) == NULL)
  {
    throw runtime_error("Cannot open directory " + dir + ": " + strerror(errno));
  }

  while ((dirp = readdir(dp)) != NULL)
  {
    files.push_back(std::string(dirp->d_name));
  }

  closedir(dp);
  return true;
}



//----------------------------------------------------------------------
// GetCurrentDirectory()
//----------------------------------------------------------------------
std::string GetCurrentDirectory()
{
  char *temp_path(nullptr);
  // POSIX.1 extension allocates buffer for path if given buffer is NULL and size = 0
  temp_path = getcwd(temp_path, 0);
  if (temp_path == nullptr)
  {
    throw runtime_error("Cannot get current directory: " + string(strerror(errno)));
  }
  std::string path(temp_path);
  path += "/";
  free(temp_path);
  return path;
}

//----------------------------------------------------------------------
// ChangeCurrentDirectory()
//----------------------------------------------------------------------
bool ChangeCurrentDirectory(const std::string& dir)
{
  if (chdir(dir.c_str()) != 0)
  {
    throw runtime_error("Cannot change to directory <" + dir + ">: " + strerror(errno));
  }
  return true;
}

//----------------------------------------------------------------------
// CreateDirectory()
//----------------------------------------------------------------------
bool CreateDirectory(const std::string& path)    //throw(runtime_error)
{
  if (mkdir(path.c_str(), S_IFDIR | S_IRWXU) != 0)
  {
    throw runtime_error("Cannot create directory <" + path + ">: " + strerror(errno));
  }
  return true;
}

//----------------------------------------------------------------------
// CreateTemp()
//----------------------------------------------------------------------
std::string CreateTemp(const std::string& root_directory, bool directory)
{
  std::string command = std::string("mktemp") + (directory ? " -d " : "") + (!root_directory.empty() ? (" -p " + root_directory) : "");
  RRLIB_LOG_PRINT(DEBUG, "executing command <", command, ">");
  FILE * pipe = popen(command.c_str(), "r");
  char buf[ 1024 ];
  if (fgets(buf, sizeof(buf), pipe) == 0)
  {
    throw runtime_error("Error creating temp file!");
  }
  std::string tempfile = buf;
  tempfile = tempfile.substr(0, tempfile.find("\n"));
  pclose(pipe);
  return tempfile;
} // CreateTemp()

//----------------------------------------------------------------------
// CreateTempFile()
//----------------------------------------------------------------------
std::string CreateTempFile(const std::string& root_directory)
{
  return CreateTemp(root_directory, false);
} // CreateTempFile()

//----------------------------------------------------------------------
// CreateTempDirectory()
//----------------------------------------------------------------------
std::string CreateTempDirectory(const std::string& root_directory)
{
  return CreateTemp(root_directory, true);
} // CreateTempDirectory()

//----------------------------------------------------------------------
// DeleteFile()
//----------------------------------------------------------------------
bool DeleteFile(const std::string& filename)
{
  if (remove(filename.c_str()) != 0)
  {
    throw runtime_error("Could not delete file <" + filename + ">: " + strerror(errno));
  }
  return true;
} // DeleteFile()

//----------------------------------------------------------------------
// DeleteDirectory()
//----------------------------------------------------------------------
bool DeleteDirectory(const std::string& directoryname)
{
  if (remove(directoryname.c_str()) != 0)
  {
    throw runtime_error("Could not delete directory <" + directoryname + ">: " + strerror(errno));
  }
  return true;
}

//----------------------------------------------------------------------
// FileExists()
//----------------------------------------------------------------------
bool FileExists(const std::string &filename)
{
  return (access(filename.c_str(), F_OK) != -1);
} // FileExists()


//----------------------------------------------------------------------
// CountLineNumbers()
//----------------------------------------------------------------------
size_t CountLineNumbers(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.good())
    throw runtime_error("Could not open file <" + filename + ">.");
  return std::count(std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n');
} // CountLineNumbers()


//----------------------------------------------------------------------
// ShellExpandFilename()
//----------------------------------------------------------------------
bool ShellExpandFilename(std::string &file_name)
{
  return ShellExpandFilename(file_name, file_name);
} // ShellExpandFilename()


//----------------------------------------------------------------------
// ShellExpandFilename()
//----------------------------------------------------------------------
std::string ShellExpandFilename(const std::string &file_name)
{
  std::string result("");
  if (!ShellExpandFilename(result, file_name))
    throw runtime_error("Cannot expand file name <" + file_name + ">");
  return result;
} // ShellExpandFilename()


//----------------------------------------------------------------------
// ShellExpandFilename()
//----------------------------------------------------------------------
bool ShellExpandFilename(std::string &result, const std::string &file_name)
{
  std::string file_name_to_expand(file_name);
  result.clear();
  wordexp_t expansion;
  int error = wordexp(file_name_to_expand.c_str(), &expansion, WRDE_SHOWERR | WRDE_UNDEF);
  if (error)
  {
    const char *error_msg = 0;
    switch (error)
    {
    case WRDE_BADCHAR:
      error_msg = "Illegal occurrence of newline or one of |, &, ;, <, >, (, ), {, }";
      break;
    case WRDE_BADVAL:
      error_msg = "An undefined shell variable was referenced";
      break;
    case WRDE_NOSPACE:
      error_msg = "Out of memory";
      break;
    case WRDE_SYNTAX:
      error_msg = "Shell syntax error, such as unbalanced parentheses or unmatched quotes";
      break;
    default:
      error_msg = "Unknown error";
    }
    throw std::runtime_error("Could not expand '" + file_name_to_expand + "': " + error_msg + "!");
  }

  std::stringstream stream;
  stream << util::Join(expansion.we_wordv + expansion.we_offs, expansion.we_wordv + expansion.we_offs + expansion.we_wordc, " ");
  wordfree(&expansion);

  result = stream.str();

  return true;
} // ShellExpandFilename()


//----------------------------------------------------------------------
// SplitFullQualifiedFilename()
//----------------------------------------------------------------------
void SplitFullQualifiedFilename(const std::string& complete_name, std::string& file_dir, std::string& file_base, std::string& file_ext)
{

  std::string::size_type pos_slash = complete_name.find_last_of("/");
  std::string::size_type pos_name = pos_slash + 1;

  if (pos_slash == std::string::npos)
  {
    // no slash found
    file_dir = "./";
    pos_name = 0;
    pos_slash = 0;
  }
  else
  {
    file_dir = complete_name.substr(0, pos_slash);
  }

  std::string::size_type pos_dot = complete_name.find_last_of(".");
  if (pos_dot == std::string::npos || pos_dot < pos_slash)
  {
    // no dot found or dot in directory
    file_base = complete_name.substr(pos_name);
    file_ext = "";
  }
  else
  {
    file_base = complete_name.substr(pos_name, pos_dot - pos_name);
    file_ext = complete_name.substr(pos_dot);
  }

} // SplitFullQualifiedFilename()


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}
