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
 * \date    2005-11-15
 *
 * \brief   Contains static class sFileIOUtils
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#ifndef _rrlib_util_sFileIOUtils_h_
#define _rrlib_util_sFileIOUtils_h_

//rrlib includes
#include "rrlib/util/string.h"
#include "rrlib/logging/messages.h"

//STL includes
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iterator>

//boost includes
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

class sFileIOUtils
{
public:
  /*!
   * \brief Returns all files in a given directory
   *
   * \return Returns whether or not the read was possible
   */
  static bool GetAllFilesInDirectory(std::string dir, std::vector<std::string> &files)
  __attribute__((deprecated("USE rrlib::util::fileio::GetAllFilesInDirectory()")));

  /*!
   * \brief Returns the current directory
   *
   * \return Returns a string containing the current directory
   */
  static std::string GetCurrentDirectory()
  __attribute__((deprecated("USE rrlib::util::fileio::GetCurrentDirectory()")));

  /*!
   * \brief Setsthe current directory
   *
   * Changes the current directory to \param dir .
   * \return returns an error code similar to the chdir C command
   */
  static bool ChangeCurrentDirectory(const std::string& dir)
  __attribute__((deprecated("USE rrlib::util::fileio::ChangeCurrentDirectory()")));

  /*!
   * \brief Creates a new directory at the path provided as parameter.
   *
   * \param path Complete relative or absolute path to be created.
   * \return returns false if directory creation fails, true otherwise.
   * The existance of the folder is not regarded as a failure here!
   */
  static bool CreateDirectory(const std::string& path)
  __attribute__((deprecated("USE rrlib::util::fileio::CreateDirectory()")));

  /*!
   * \brief Creates a new temporary file via "mktemp".
   *
   * \return the new temp file
   */
  static std::string CreateTempfile()
  __attribute__((deprecated("USE rrlib::util::fileio::CreateTempFile()")));

  /*!
   * \brief Removes file with given name.
   */
  static void DeleteFile(const std::string& filename)
  __attribute__((deprecated("USE rrlib::util::fileio::DeleteFile()")));

  /*!
   * \brief Test if file exists for given file name
   *
   * \returns true if file exists
   */
  static bool FileExists(const std::string &filename)
  __attribute__((deprecated("USE rrlib::util::fileio::FileExists()")));

  /*!
   * \brief Counts # lines in given file
   *
   * \returns # lines
   */
  static size_t CountLineNumbers(const std::string &filename)
  __attribute__((deprecated("USE rrlib::util::fileio::CountLineNumbers()")));


  /*!
   * \brief Writes content of given container to file with given name
   *
   * \returns true iff file could be processed as expected
   *
   * \note If filename has suffix ".bz2" it is compressed accordingly.
   */
  template <class ConstForwardIterator>
  static bool WriteContainerToFile(ConstForwardIterator begin, ConstForwardIterator end, const std::string& filename)
  __attribute__((deprecated("USE rrlib::serialization instead")));


  template <class Container>
  static bool WriteContainerToFile(const Container &container, const std::string& filename)
  __attribute__((deprecated("USE rrlib::serialization instead")));


  /*!
   * \brief Reads file with given name and writes its content to given container
   *
   * \returns true iff file could be processed as expected
   *
   * \note If filename has suffix ".bz2" it is decompressed accordingly before reading.
   */
  template <class Container>
  static bool ReadContainerFromFile(Container &container, const std::string& filename)
  __attribute__((deprecated("USE rrlib::serialization instead")));


  /*! Expands the given filename via a pipe and echo command in order to replace all contained environment variables with their actual value.
   *
   * \param file_name   file name to be expanded (will contain the result afterwards)
   *
   * \returns Whether the method could be executed without failure or not
   */
  static bool ShellExpandFilename(std::string &file_name)
  __attribute__((__warn_unused_result__))
  __attribute__((deprecated("USE rrlib::util::fileio::ShellExpandFilename()")));

  /*! Expands the given filename via a pipe and echo command in order to replace all contained environment variables with their actual value.
   *
   * \param file_name   file name to be expanded
   *
   * \returns Expanded file name
   */
  static std::string ShellExpandFilename(const std::string &file_name)
  __attribute__((__warn_unused_result__))
  __attribute__((deprecated("USE rrlib::util::fileio::ShellExpandFilename()")));

  /*! Expands the given filename via a pipe and echo command in order to replace all contained environment variables with their actual value.
  *
  * Thus variables as e.g. $MCAPROJECTHOME can be used for specifying OIV files in scene description files.
  *
  * \param result      reference to std::string object that should contain the result afterwards
  * \param file_name   file name to be expanded
  *
  * \returns Whether the method could be executed without failure or not
  */
  static bool ShellExpandFilename(std::string &result, const std::string& file_name)
  __attribute__((__warn_unused_result__))
  __attribute__((deprecated("USE rrlib::util::fileio::ShellExpandFilename()")));

  /*!
   *    Splits the given filename into directory, single file name and file extension
   *    \param complete_name complete file name (input)
   *    \param file_dir directory (output)
   *    \param file_base single file name (output)
   *    \param file_ext file extension (output)
   */
  static void SplitFullQualifiedFilename(const std::string& complete_name, std::string& file_dir, std::string& file_base, std::string& file_ext)
  __attribute__((deprecated("USE rrlib::util::fileio::SplitFullQualifiedFilename()")));

  /*
   * Extracts the file extension from a given filename
   * \param filename complete file name
   * \returns file extension if existing, an empty string else
   */
  static std::string GetFileExtension(const std::string &filename)
  __attribute__((deprecated("USE rrlib::util::fileio::GetFileExtension()")));

} __attribute__((deprecated("USE functions from rrlib::util::fileio")));

//======================================================================
// Implementation of template functions
//======================================================================

//----------------------------------------------------------------------
// class sFileIOUtils::WriteContainerToFile()
//----------------------------------------------------------------------
template <class ConstForwardIterator>
bool sFileIOUtils::WriteContainerToFile(ConstForwardIterator begin, ConstForwardIterator end, const std::string& filename)
{
  std::ofstream output_file_stream;
  RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, "got file <", filename, ">");
  if (util::EndsWith(filename, ".bz2"))
  {
    RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, "compressing");
    boost::iostreams::filtering_ostream out;
    out.push(boost::iostreams::bzip2_compressor());
    output_file_stream.open(filename.c_str());
    if (output_file_stream)
    {
      out.push(output_file_stream);
      std::copy(begin, end, std::ostream_iterator<typename ConstForwardIterator::value_type>(out));
      return true;
    }
  }
  else
  {
    output_file_stream.open(filename.c_str());
    if (output_file_stream)
    {
      std::copy(begin, end, std::ostream_iterator<typename ConstForwardIterator::value_type>(output_file_stream));
      output_file_stream.close();
      return true;
    }
  }
  return false;
};

//----------------------------------------------------------------------
// class sFileIOUtils::WriteContainerToFile()
//----------------------------------------------------------------------
template <class Container>
bool sFileIOUtils::WriteContainerToFile(const Container &container, const std::string& filename)
{
  return WriteContainerToFile(container.begin(), container.end(), filename);
};

//----------------------------------------------------------------------
// class sFileIOUtils::ReadContainerFromFile()
//----------------------------------------------------------------------
template <class Container>
bool sFileIOUtils::ReadContainerFromFile(Container &container, const std::string& filename)
{
  std::ifstream input_file_stream;
  RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, "got file <", filename, ">");
  if (util::EndsWith(filename, ".bz2"))
  {
    RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, "decompressing");
    boost::iostreams::filtering_istream in;
    in.push(boost::iostreams::bzip2_decompressor());
    input_file_stream.open(filename.c_str());
    if (input_file_stream)
    {
      in.push(input_file_stream);
      std::copy(std::istream_iterator<typename Container::value_type>(in), std::istream_iterator<typename Container::value_type>(), std::back_inserter(container));
      RRLIB_LOG_PRINT(ERROR, "got ", container.size(), " container elements from file ", filename);
      return true;
    }
  }
  else
  {
    input_file_stream.open(filename.c_str());
    if (input_file_stream)
    {
      std::copy(std::istream_iterator<typename Container::value_type>(input_file_stream), std::istream_iterator<typename Container::value_type>(), std::back_inserter(container));
      RRLIB_LOG_PRINT(ERROR, "got ", container.size(), " container elements from file ", filename);
    }
    input_file_stream.close();
    return true;
  }
  return false;
};


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}; // namespace util
}; // namespace rrlib
#endif
