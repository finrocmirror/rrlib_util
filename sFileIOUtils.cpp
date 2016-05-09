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
 * \date    2005-11-15
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#include "rrlib/util/sFileIOUtils.h"

#include "rrlib/util/fileio.h"

//----------------------------------------------------------------------
// Debug
//----------------------------------------------------------------------

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
// class sFileIOUtils::GetAllFilesInDirectory()
//----------------------------------------------------------------------
bool sFileIOUtils::GetAllFilesInDirectory(std::string dir, std::vector<std::string> &files)
{
  return fileio::GetAllFilesInDirectory(dir, files);
}


//----------------------------------------------------------------------
// class sFileIOUtils::GetCurrentDirectory()
//----------------------------------------------------------------------
std::string sFileIOUtils::GetCurrentDirectory()
{
  return fileio::GetCurrentDirectory();
}


//----------------------------------------------------------------------
// class sFileIOUtils::ChangeCurrentDirectory()
//----------------------------------------------------------------------
bool sFileIOUtils::ChangeCurrentDirectory(const std::string& dir)
{
  return fileio::ChangeCurrentDirectory(dir);
}


//----------------------------------------------------------------------
// class sFileIOUtils::CreateDirectory()
//----------------------------------------------------------------------
bool sFileIOUtils::CreateDirectory(const std::string& path)
{
  return fileio::CreateDirectory(path);
}


//----------------------------------------------------------------------
// class sFileIOUtils::CreateTempfile()
//----------------------------------------------------------------------
std::string sFileIOUtils::CreateTempfile()
{
  return fileio::CreateTempFile();
} // CreateTempfile()


//----------------------------------------------------------------------
// class sFileIOUtils::DeleteFile()
//----------------------------------------------------------------------
void sFileIOUtils::DeleteFile(const std::string& filename)
{
  fileio::DeleteFile(filename);
} // DeleteFile()


//----------------------------------------------------------------------
// class sFileIOUtils::FileExists()
//----------------------------------------------------------------------
bool sFileIOUtils::FileExists(const std::string &filename)
{
  return fileio::FileExists(filename);
} // FileExists()


//----------------------------------------------------------------------
// class sFileIOUtils::CountLineNumbers()
//----------------------------------------------------------------------
size_t sFileIOUtils::CountLineNumbers(const std::string &filename)
{
  return fileio::CountLineNumbers(filename);
} // CountLineNumbers()


//----------------------------------------------------------------------
// class sFileIOUtils::ShellExpandFilename()
//----------------------------------------------------------------------
bool sFileIOUtils::ShellExpandFilename(std::string &file_name)
{
  return fileio::ShellExpandFilename(file_name);
} // ShellExpandFilename()


//----------------------------------------------------------------------
// class sFileIOUtils::ShellExpandFilename()
//----------------------------------------------------------------------
std::string sFileIOUtils::ShellExpandFilename(const std::string &file_name)
{
  return fileio::ShellExpandFilename(file_name);
} // ShellExpandFilename()


//----------------------------------------------------------------------
// class sFileIOUtils::ShellExpandFilename()
//----------------------------------------------------------------------
bool sFileIOUtils::ShellExpandFilename(std::string &result, const std::string &file_name)
{
  return fileio::ShellExpandFilename(result, file_name);
} // ShellExpandFilename()


//----------------------------------------------------------------------
// class sFileIOUtils::SplitFullQualifiedFilename()
//----------------------------------------------------------------------
void sFileIOUtils::SplitFullQualifiedFilename(const std::string& complete_name, std::string& file_dir, std::string& file_base, std::string& file_ext)
{
  return fileio::SplitFullQualifiedFilename(complete_name, file_dir, file_base, file_ext);
} // SplitFullQualifiedFilename()


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
