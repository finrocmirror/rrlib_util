//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) AG Robotersysteme TU Kaiserslautern
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    sFileIOUtils.h
 *
 * \author  Bernd Helge Schaefer
 * \author  Jens Wettach
 * \date    15.11.05
 *
 * \brief   Contains static class sFileIOUtils
 *
 */
//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#ifndef _rrlib_util_sFileIOUtils_h_
#define _rrlib_util_sFileIOUtils_h_

//STL includes
#include <string>
#include <vector>
#include <map>

extern "C"
{
#include <arpa/inet.h> // inet_ntoa
}

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
  static bool GetAllFilesInDirectory(std::string dir, std::vector<std::string> &files);

  /*!
   * \brief Returns the current directory
   *
   * \return Returns a string containing the current directory
   */
  static std::string GetCurrentDirectory();
  /*!
   * \brief Setsthe current directory
   *
   * Changes the current directory to \param dir .
   * \return returns an error code similar to the chdir C command
   */
  static int ChangeCurrentDirectory(const std::string& dir);

  /*!
   * \brief Creates a new directory at the path provided as parameter.
   *
   * \param path Complete relative or absolute path to be created.
   * \return returns false if directory creation fails, true otherwise.
   * The existance of the folder is not regarded as a failure here!
   */
  static bool CreateDirectory(const std::string& path); // throw(runtime_error);

  /*!
   * \brief Creates a new temporary file via "mktemp".
   *
   * \return the new temp file
   */
  static std::string CreateTempfile();

  /*!
   * \brief Removes file with given name.
   */
  static void DeleteFile(const std::string& filename);

  /*!
   * \brief Calls "gzip" on input file and writes result to output file.
   *
   * \note output file gets suffix ".gz" automatically if not yet the case.
   */
  static void CompressFile(const std::string& input_filename, std::string& output_filename);

  /*!
   * \brief Calls "gunzip" on input file and writes result to output file.
   *
   * \note input file must have suffix ".gz".
   */
  static void DecompressFile(const std::string& input_filename, const std::string& output_filename);



  /*! Expands the given filename via a pipe and echo command in order to replace all contained environment variables with their actual value.
   *
   * \param file_name   file name to be expanded (will contain the result afterwards)
   *
   * \returns Whether the method could be executed without failure or not
   */
  static bool ShellExpandFilename(std::string &file_name) __attribute__((__warn_unused_result__));

  /*! Expands the given filename via a pipe and echo command in order to replace all contained environment variables with their actual value.
  *
  * Thus variables as e.g. $MCAPROJECTHOME can be used for specifying OIV files in scene description files.
  *
  * \param result      reference to std::string object that should contain the result afterwards
  * \param file_name   file name to be expanded
  *
  * \returns Whether the method could be executed without failure or not
  */
  static bool ShellExpandFilename(std::string &result, const std::string& file_name) __attribute__((__warn_unused_result__));


  /*!
   *    Splits the given filename into directory, single file name and file extension
   *    \param complete_name complete file name (input)
   *    \param file_dir directory (output)
   *    \param file_base single file name (output)
   *    \param file_ext file extension (output)
   */
  static void SplitFullQualifiedFilename(const std::string& complete_name, std::string& file_dir, std::string& file_base, std::string& file_ext);


  /*!
   * Retrieves network host name via "hostname" and returns result.
   * \param fqdn whether FQDN  (Fully  Qualified Domain Name) or short name shall be retrieved
   */
  static std::string GetHostName(bool fqdn = true);


  /*!
   * Retrieves ip address of host with given network name via "gethostbyname" and returns result.
   */
  static struct in_addr HostToIpViaGetHostByName(const std::string& name);

  /*!
   * Retrieves ip address of host with given network name via "nslookup" and returns result.
   */
  static struct in_addr HostToIpViaNslookup(const std::string& name);

  /*!
   * Retrieves ip address of host with given network name via "host" and returns result.
   */
  static struct in_addr HostToIpViaHost(const std::string& name);

  /*!
   * Retrieves ip address of host with given network name from "/etc/hosts" and returns result.
   */
  static struct in_addr HostToIpViaHostsFile(const std::string& name);

  /*!
   * Retrieves ip address of host with given network name using
   * 1. \sa HostToIpViaHostsFile()
   * 2. \sa HostToIpViaHostx()
   * 2. \sa HostToIpViaNslookup()
   */
  static struct in_addr HostToIp(const std::string& name);

  /*!
   * Fetches file with given source_file_name from server (either addressed by network name or ip address) at given source_directory
   * and puts it to the given target_directory (via <system( rsync -av ...)> ).
   *
   * \params source_host_name network name of server
   * \params source_host_ip_address ip address name of server (used alternatively to its name)
   * \params source_directory directory on server
   * \params source_file_name file to fetch from server
   * \params target_directory local directory for fetched file
   * \params optional_rsync_flags optional flags for rsync command, appended to -av
   *
   * \returns result of system call
   */
  static int RSyncFile(const std::string& source_host_name, const std::string& source_host_ip_address, const std::string& source_directory, const std::string& source_file_name, const std::string& target_directory, const std::string &optional_rsync_flags = "");


  /*!
   * Fetches files with given source_file_names from server (either addressed by network name or ip address) at given source_directory
   * and puts it to the given target_directory (via <system( rsync -avr --files-from ...)> ). Uses temp file on local host to
   * compose list with files to fetch.
   *
   * \params source_host_name network name of server
   * \params source_host_ip_address ip address name of server (used alternatively to its name)
   * \params source_directory directory on server
   * \params source_file_names files to fetch from server
   * \params target_directory local directory for fetched file
   * \params optional_rsync_flags optional flags for rsync command, appended to -avr
   *
   * \returns result of system call
   */
  static int RSyncFiles(const std::string& source_host_name, const std::string& source_host_ip_address, const std::string& source_directory, const std::vector<std::string>& source_file_names, const std::string& target_directory, const std::string &optional_rsync_flags = "");


  /*!
   * Checks whether given file is available on local host or can be rsync'ed from resource server and returns full qualified file_name on local host.
   * The following checks are performed (with decreasing priority):
   * 1. check location of file: "./ + resource_repository + filename"
   * 2. check location of file: "local_resource_directory + resource_repository + filename"
   * 3. check location of file: "server_resource_directory + resource_repository + filename" --> rsync to "local_resource_directory + resource_repository + file_name"
   * As soon as one check succeeds the remaining checks are not executed.
   *
   * \param file_name name of file to search and fetch (may contain relative path)
   * \param full_local_file_name full qualified name of file on local host after successful check/fetch operation (result)
   * \param resource_repository relative path to be used as resource repository (on local host and on server, may be empty)
   * \param resource_server network name of resource server (optional)
   * \param local_resource_directory absolute path to resource_repository on local host (may be empty)
   * \param server_resource_directory absolute path to resource_repository on server (may be empty)
   * \param use_cache whether to take local host name and server ip address from local static cache or not
   *
   * \returns success of check/fetch operation
   */
  static bool CheckAndGetFile(const std::string &file_name, std::string &full_local_file_name, const std::string& resource_repository = "", const std::string& resource_server = "", const std::string& local_resource_directory = "", const std::string& server_resource_directory = "", bool use_cache = false);

  /*!
   * Clear cached local host name and server ip addresses
   * \sa CheckAndGetFile()
   */
  static void ClearCaches();

  /*!
   * Clear cached resource file names
   * \sa CheckAndGetFile()
   */
  static void ClearResourceCache();

private:
  static std::string cached_local_host; //!< local static variable to store name of local host
  static std::map<std::string, std::string> host_name_to_ip_cache; //!< local static variable to store server ip addresses
  static std::map<std::string, std::string> resource_cache; //!< local static variable to store names of already loaded resource files
};
//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}; // namespace util
}; // namespace rrlib
#endif
