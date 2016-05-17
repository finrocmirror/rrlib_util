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
/*!\file    rrlib/util/sFileIOUtils.h
 *
 * \author  Bernd Helge Schaefer
 * \author  Jens Wettach
 *
 * \date    2016-04-28
 *
 * \brief   Contains functions for file handling
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#ifndef _rrlib_util_fileio_h_
#define _rrlib_util_fileio_h_

//rrlib includes
#include "rrlib/logging/messages.h"

//STL includes
#include <string>
#include <vector>

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{
namespace fileio
{
/*!
 * \brief Returns all files in a given directory
 *
 * \return true if the directory could be read
 * \throws runtime_error if \param directory cannot be opened
 */
bool GetAllFilesInDirectory(const std::string& directory, std::vector<std::string> &files);

/*!
 * \brief Returns the current directory
 *
 * \return a string containing the current directory
 * \throws runtime_error if the current directory cannot be retrieved
 */
std::string GetCurrentDirectory();

/*!
 * \brief Changes the current directory to \param directory .
 * \return true if the directory could be changed
 * \throws runtime_error if the directory cannot be changed
 */
bool ChangeCurrentDirectory(const std::string& directory);

/*!
 * \brief Creates a new directory at the \param path.
 *
 * \param path Complete relative or absolute path to be created.
 * \return returns true if directory could be created
 * \throws runtime_error if the directory cannot be created
 * The existance of the folder is not regarded as a failure here!
 */
bool CreateDirectory(const std::string& path);

/*!
 * \brief Creates a new temporary file via "mktemp".
 * \param root_directory directory for the temporary file (optional)
 * \return the newly created temporary file
 * \throws runtime_error if the file creation fails
 */
std::string CreateTempFile(const std::string& root_directory = "");

/*!
 * \brief Creates a new temporary directory via "mktemp".
 * \param root_directory directory for the temporary directory (optional)
 * \return the newly created temporary directory
 * \throws runtime_error if the directory creation fails
 */
std::string CreateTempDirectory(const std::string& root_directory = "");

/*!
 * \brief Removes the file with \param file_name.
 * \return true if file could be removed
 * \throws runtime_error if file removal fails
 */
bool DeleteFile(const std::string& file_name);

/*!
 * \brief Removes the directory with \param directory_name.
 * \return true if directory could be removed
 * \throws runtime_error if directory removal fails
 */
bool DeleteDirectory(const std::string& directory_name);

/*!
 * \brief Tests if file with \param file_name exists
 *
 * \return true if file exists, false otherwise
 */
bool FileExists(const std::string &file_name);

/*!
 * \brief Counts number of lines in \param file_name
 *
 * \return numboer of lines
 * \throws runtime_error if file cannot be opened
 */
size_t CountLineNumbers(const std::string &file_name);

/*! Expands the \param file_name via a pipe and echo command in order to replace all contained environment variables with their actual value.
 *
 * \param file_name file name to be expanded (will contain the result afterwards)
 *
 * \return true if file name could be expanded
 * \throws runtime_error if expansion of file name failed
 */
bool ShellExpandFilename(std::string &file_name) __attribute__((__warn_unused_result__));

/*! Expands the \param file_name via a pipe and echo command in order to replace all contained environment variables with their actual value.
 *
 * \param file_name file name to be expanded
 *
 * \return expanded file name in case of success
 * \throws runtime_error if expansion of file name failed
 */
std::string ShellExpandFilename(const std::string &file_name)  __attribute__((__warn_unused_result__));

/*! Expands the \param file_name via a pipe and echo command in order to replace all contained environment variables with their actual value.
 *
 * \param file_name file name to be expanded
 * \param result will contain the expanded file name
 *
 * \return true if file name could be expanded
 * \throws runtime_error if expansion of file name failed
 */
bool ShellExpandFilename(std::string &result, const std::string& file_name) __attribute__((__warn_unused_result__));

/*!
 *    Splits the given filename into directory, single file name and file extension
 *    \param complete_name complete file name (input)
 *    \param file_dir directory (output)
 *    \param file_base single file name (output)
 *    \param file_ext file extension (output)
 */
void SplitFullQualifiedFilename(const std::string& complete_name, std::string& file_dir, std::string& file_base, std::string& file_ext);

/*
 * Extracts the file extension from \param file_name
 * \param file_name file name with extension
 * \returns file extension (may be empty)
 */
std::string GetFileExtension(const std::string &file_name);


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}; // namespace fileio
}; // namespace util
}; // namespace rrlib
#endif

