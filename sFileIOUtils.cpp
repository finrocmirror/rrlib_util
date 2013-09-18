//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
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

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

extern "C"
{
#include <netdb.h> // struct hostent, gethostbyname
#include <unistd.h>
#include <dirent.h>
#include <wordexp.h>
}

#include "rrlib/util/sStringUtils.h"
#include "rrlib/util/join.h"
#include "rrlib/logging/messages.h"

//----------------------------------------------------------------------
// Debug
//----------------------------------------------------------------------
#include <cassert>

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

//----------------------------------------------------------------------
// initialization of static class vars
//----------------------------------------------------------------------
std::string sFileIOUtils::cached_local_host = "";
std::map<std::string, std::string> sFileIOUtils::host_name_to_ip_cache = std::map<std::string, std::string>();
std::map<std::string, std::string> sFileIOUtils::resource_cache = std::map<std::string, std::string>();



bool sFileIOUtils::GetAllFilesInDirectory(std::string dir, std::vector<std::string> &files)
{
  DIR *dp;
  struct dirent *dirp;
  if ((dp  = opendir(dir.c_str())) == NULL)
  {
    return false;
  }

  while ((dirp = readdir(dp)) != NULL)
  {
    files.push_back(std::string(dirp->d_name));
    //std::cout << "Found: " << dirp->d_name << std::endl;
  }

  closedir(dp);
  return true;
}



//----------------------------------------------------------------------
// class sFileIOUtils::GetCurrentDirectory()
//----------------------------------------------------------------------
std::string sFileIOUtils::GetCurrentDirectory()
{
  char *temp_path(NULL);
  // POSIX.1 extension allocates buffer for path if given buffer is NULL and size = 0
  temp_path = getcwd(temp_path, 0);
  std::string path(temp_path);
  path += "/";
  free(temp_path);
  return path;
}

//----------------------------------------------------------------------
// class sFileIOUtils::ChangeCurrentDirectory()
//----------------------------------------------------------------------
int sFileIOUtils::ChangeCurrentDirectory(const std::string& dir)
{
  return chdir(dir.c_str());
}

//----------------------------------------------------------------------
// class sFileIOUtils::CreateDirectory()
//----------------------------------------------------------------------
bool sFileIOUtils::CreateDirectory(const std::string& path)    //throw(runtime_error)
{
  std::stringstream sys_call;
  sys_call << "mkdir -p " << path;

  if (system(sys_call.str().c_str()) == -1)
  {
    RRLIB_LOG_PRINTF(USER, "sFileIOUtils>> Error creating dir: '%s'\n", path.c_str());
//     std::stringstream error_msg;
//     error_msg << "sFileIOUtils>> Error creating Dir:\n"
//     << path << endl;
    //throw runtime_error(error_msg.str());
    return false;
  }
  else
  {
//     RRLIB_LOG_PRINTF(USER, "sFileIOUtils>> Directory: '%s' successfully created.\n", path.c_str());
    return true;
  }
}

//----------------------------------------------------------------------
// class sFileIOUtils::CreateTempfile()
//----------------------------------------------------------------------
std::string sFileIOUtils::CreateTempfile()
{
  FILE * pipe = popen("mktemp", "r");
  char buf[ 1024 ];
  if (fgets(buf, sizeof(buf), pipe) == 0)
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::CreateTempfile() >> Error creating temp file!\n");
    exit(EXIT_FAILURE);
  }
  std::string tempfile = buf;
  tempfile = tempfile.substr(0, tempfile.find("\n"));
  pclose(pipe);
  return tempfile;
} // CreateTempfile()

//----------------------------------------------------------------------
// class sFileIOUtils::DeleteFile()
//----------------------------------------------------------------------
void sFileIOUtils::DeleteFile(const std::string& filename)
{
  unlink(filename.c_str());
} // DeleteFile()

//----------------------------------------------------------------------
// class sFileIOUtils::CompressFile()
//----------------------------------------------------------------------
void sFileIOUtils::CompressFile(const std::string& input_filename, std::string& output_filename)
{
  if (!sStringUtils::EndsWith(output_filename, ".gz"))
    output_filename += ".gz";
  std::stringstream cmd;
  cmd << "gzip -c " << input_filename << " > " << output_filename;
  if (system(cmd.str().c_str()) != 0)
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils>> Execution of command '%s' failed!\n", cmd.str().c_str());
    exit(EXIT_FAILURE);
  }
} // CompressFile()

//----------------------------------------------------------------------
// class sFileIOUtils::DecompressFile()
//----------------------------------------------------------------------
void sFileIOUtils::DecompressFile(const std::string& input_filename, const std::string& output_filename)
{
  assert(sStringUtils::EndsWith(input_filename, ".gz"));
  std::stringstream cmd;
  cmd << "gunzip -c " << input_filename << " > " << output_filename;
  if (system(cmd.str().c_str()) != 0)
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils>> Execution of command '%s' failed!\n", cmd.str().c_str());
    exit(EXIT_FAILURE);
  }
} // DecompressFile()

//----------------------------------------------------------------------
// class sFileIOUtils::FileExists()
//----------------------------------------------------------------------
bool sFileIOUtils::FileExists(const std::string &filename)
{
  // catch empty file
  if (filename == "")
  {
    return false;
  }

  // test if file exists
  FILE* file = fopen(filename.c_str(), "rb");
  if (file == 0)
  {
    return false;
  }
  fclose(file);

  return true;
}


//----------------------------------------------------------------------
// class sFileIOUtils::ShellExpandFilename()
//----------------------------------------------------------------------
bool sFileIOUtils::ShellExpandFilename(std::string &file_name)
{
  return ShellExpandFilename(file_name, file_name);
} // ShellExpandFilename()

//----------------------------------------------------------------------
// class sFileIOUtils::ShellExpandFilename()
//----------------------------------------------------------------------
std::string sFileIOUtils::ShellExpandFilename(const std::string &file_name)
{
  std::string result("");
  if (ShellExpandFilename(result, file_name))
    return result;
  else
    return "";
} // ShellExpandFilename()


//----------------------------------------------------------------------
// class sFileIOUtils::ShellExpandFilename()
//----------------------------------------------------------------------
bool sFileIOUtils::ShellExpandFilename(std::string &result, const std::string &file_name)
{
  //result = "";  //in case &result == &file_name, then it causes trouble.
  wordexp_t expansion;
  int error = wordexp(file_name.c_str(), &expansion, WRDE_SHOWERR | WRDE_UNDEF);
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
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::%s >> Could not expand '%s': %s!\n", __FUNCTION__, file_name.c_str(), error_msg);
    return false;
  }

  std::stringstream stream;
  stream << util::Join(expansion.we_wordv + expansion.we_offs, expansion.we_wordv + expansion.we_offs + expansion.we_wordc, " ");
  wordfree(&expansion);

  result = stream.str();

  return true;
} // ShellExpandFilename()

//----------------------------------------------------------------------
// class sFileIOUtils::SplitFullQualifiedFilename()
//----------------------------------------------------------------------
void sFileIOUtils::SplitFullQualifiedFilename(const std::string& complete_name, std::string& file_dir, std::string& file_base, std::string& file_ext)
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

  //    cerr << "pos_slash: " << pos_slash << endl;
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
// class sFileIOUtils::GetHostName()
//----------------------------------------------------------------------
std::string sFileIOUtils::GetHostName(bool fqdn)
{
  //RRLIB_LOG_PRINTF(USER, "sFileIOUtils::GetHostName() >>> started\n");
  std::string cmd = fqdn ? "hostname -f" : "hostname";
  FILE * pipe = popen(cmd.c_str(), "r");
  char buf[ 1024 ];
  if (fgets(buf, sizeof(buf), pipe) == 0)
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::GetHostName(bool fqdn) >> Error querying host name!\n");
    exit(EXIT_FAILURE);
  }
  pclose(pipe);
  std::string name(buf);
  sStringUtils::TrimWhitespace(name);
  //boost::trim(name);
  //RRLIB_LOG_PRINTF(USER, "sFileIOUtils::GetHostName() >>> finished with name <%s>\n", name.c_str());
  return name;
} // GetHostName()

//----------------------------------------------------------------------
// class sFileIOUtils::HostToIpViaGetHostByName()
//----------------------------------------------------------------------
struct ::in_addr sFileIOUtils::HostToIpViaGetHostByName(const std::string& name)
{
  struct in_addr address;
  address.s_addr = 0;
  struct hostent *host_ent = gethostbyname(name.c_str());       //alternative (from kernel/tTCPSocket): GetHostByName( name );
  if (host_ent)
  {
    address = * ((struct in_addr *) host_ent->h_addr_list[ 0 ]);
    RRLIB_LOG_PRINTF(USER, "ip address of host <%s> = <%s>\n", name.c_str(), inet_ntoa(address));
  }
  else
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::GetIpAddressOfHost() >>> could not get ip address of host <%s>\n", name.c_str());
  }
  return address;
} //HostToIpViaGetHostByName()


//----------------------------------------------------------------------
// class sFileIOUtils::HostToIpViaNslookup()
//----------------------------------------------------------------------
struct in_addr sFileIOUtils::HostToIpViaNslookup(const std::string & name)
{
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIpViaNslookup() >>> started with host <%s>\n", name.c_str());
  struct in_addr address;
  address.s_addr = 0;

  std::stringstream command;
  command << "nslookup \"" << name << "\"";
  RRLIB_LOG_PRINTF(USER, "command = <%s>\n", command.str().c_str());
  FILE * pipe = popen(command.str().c_str(), "r");
  if (!pipe)
  {
    perror("error\n");
    return address;
  }
  std::stringstream result;
  char buf[ 512 ];
  while (fgets(buf, 512, pipe) != NULL)
  {
    result << buf;
  }
  pclose(pipe);
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIpViaNslookup() >>> host = <%s> , result = <%s> \n", name.c_str(), result.str().c_str());

  std::string result_str(result.str());
  std::string search_token("Name:");
  std::string::size_type pos = result_str.find(search_token);
  if (pos == std::string::npos)
  {
    RRLIB_LOG_PRINTF(ERROR, "Could not find token <%s> in nslookup result ... returning <%s> \n", search_token.c_str(), inet_ntoa(address));
    return address;
  }
  result_str.erase(0, pos + search_token.length());
  RRLIB_LOG_PRINTF(USER, "pos = %zd\n", pos);

  search_token = "Address:";
  pos = result_str.find(search_token);
  if (pos == std::string::npos)
  {
    RRLIB_LOG_PRINTF(ERROR, "Could not find token <%s> in nslookup result ... returning <%s> \n", search_token.c_str(), inet_ntoa(address));
    return address;
  }
  RRLIB_LOG_PRINTF(USER, "pos = %zd\n", pos);

  std::string found_name(result_str.substr(0, pos));
  sStringUtils::TrimWhitespace(found_name);
  //boost::trim(found_name);
  std::string ip(result_str.substr(pos + search_token.length()));
  sStringUtils::TrimWhitespace(ip);
  //boost::trim(ip);

  RRLIB_LOG_PRINTF(USER, "found_name <%s> , name <%s> \n", found_name.c_str(), name.c_str());

  if (found_name != name)
  {
    RRLIB_LOG_PRINTF(ERROR, "nslookup failed .... returning <%s> \n", inet_ntoa(address));
    return address;
  }
  RRLIB_LOG_PRINTF(USER, "found_name <%s> , ip <%s> \n", found_name.c_str(), ip.c_str());

  inet_aton(ip.c_str(), &address);

  //return ip.c_str();
  return address;
} // HostToIpViaNslookup()


//----------------------------------------------------------------------
// class sFileIOUtils::HostToIpViaHost()
//----------------------------------------------------------------------
struct in_addr sFileIOUtils::HostToIpViaHost(const std::string & name)
{
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIpViaHost() >>> started with host <%s>\n", name.c_str());
  struct in_addr address;
  address.s_addr = 0;

  std::stringstream command;
  command << "host -t A \"" << name << "\"";
  RRLIB_LOG_PRINTF(USER, "command = <%s>\n", command.str().c_str());
  FILE * pipe = popen(command.str().c_str(), "r");
  if (!pipe)
  {
    perror("error\n");
    return address;
  }
  std::stringstream result;
  char buf[ 512 ];
  while (fgets(buf, 512, pipe) != NULL)
  {
    result << buf;
  }
  pclose(pipe);
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIpViaHost() >>> host = <%s> , result = <%s> \n", name.c_str(), result.str().c_str());

  std::string result_str(result.str());
  std::vector<std::string> tokens;
  sStringUtils::Tokenize(result_str, tokens, " \t");

  for_each(tokens.begin(), tokens.end(), sStringUtils::Trim<std::string>());
  RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::HostToIpViaHost() >>> got %d tokens:\n", tokens.size());
  RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, Join(tokens, "\n"));

  assert(tokens.size() == 4);
  RRLIB_LOG_PRINTF(USER, "found_name <%s> , ip <%s> \n", tokens[0].c_str(), tokens[3].c_str());

  inet_aton(tokens[3].c_str(), &address);
  return address;
} // HostToIpViaHost()

//----------------------------------------------------------------------
// class sFileIOUtils::HostToIpViaHostsFile()
//----------------------------------------------------------------------
struct in_addr sFileIOUtils::HostToIpViaHostsFile(const std::string & name)
{
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIpViaHostsFile() >>> started with host <%s>\n", name.c_str());
  struct in_addr address;
  address.s_addr = 0;

  ifstream hosts_file("/etc/hosts");

  char line[ 1024 ];
  std::string line_str, ip_address;
  std::vector<std::string> tokens;
  bool found(false);
  while (!hosts_file.eof() && !found)
  {
    hosts_file.getline(line, 1024);
    line_str = std::string(line);
    if (line_str.length() > 0 && line_str.find("#") == std::string::npos)
    {
      tokens.clear();
      sStringUtils::Tokenize(line_str, tokens, " \t");

      if (find(tokens.begin(), tokens.end(), name) != tokens.end())
      {
        for (std::vector<std::string>::const_iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
        {
          if (inet_aton(iter->c_str(), &address))
          {
            ip_address = *iter;
            RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIpViaHostsFile() >>> got ip <%s> of host <%s> from hosts file\n", ip_address.c_str(), name.c_str());
            found = true;
            break;
          }
        }
      }
    }
  }
  hosts_file.close();
  return address;
} // HostToIpViaHostsFile()


//----------------------------------------------------------------------
// class sFileIOUtils::HostToIp()
//----------------------------------------------------------------------
struct in_addr sFileIOUtils::HostToIp(const std::string & name)
{
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIp() >>> started with host <%s>\n", name.c_str());

  struct in_addr address;
  address.s_addr = 0;

  if ((address = sFileIOUtils::HostToIpViaHostsFile(name)).s_addr != 0)
  {
    RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIp() >>> got ip <%s> of host <%s> from hosts_file\n", inet_ntoa(address), name.c_str());
  }
  else if ((address = sFileIOUtils::HostToIpViaHost(name)).s_addr != 0)
  {
    RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIp() >>> got ip <%s> of host <%s> via <host -t A>\n", inet_ntoa(address), name.c_str());
  }
  else if ((address = sFileIOUtils::HostToIpViaNslookup(name)).s_addr != 0)
  {
    RRLIB_LOG_PRINTF(USER, "sFileIOUtils::HostToIp() >>> got ip <%s> of host <%s> via <nslookup>\n", inet_ntoa(address), name.c_str());
  }
  else
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::HostToIp() >>> could not get ip of host <%s>\n", name.c_str());
  }

  return address;
} // HostToIp()


//----------------------------------------------------------------------
// class sFileIOUtils::RSyncFile()
//----------------------------------------------------------------------
int sFileIOUtils::RSyncFile(const std::string& source_host_name, const std::string& source_host_ip_address, const std::string& source_directory, const std::string& source_file_name, const std::string& target_directory, const std::string &optional_rsync_flags)
{
  std::stringstream rsync_command;
  rsync_command << "rsync -av" << optional_rsync_flags << " ";
  if (source_host_ip_address == "")
  {
    rsync_command << inet_ntoa(sFileIOUtils::HostToIp(source_host_name));
  }
  else
  {
    rsync_command << source_host_ip_address;
  }
  rsync_command << ":"
                << source_directory
                << source_file_name
                << " "
                << target_directory;

  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::RSyncFile() >>> executing <%s> ...\n", rsync_command.str().c_str());
  int ret = system(rsync_command.str().c_str());
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::RSyncFile() >>> ... done.\n");

  RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::RSyncFile() >>> finished with result %d\n", ret);
  return ret;
} // RSyncFile()


//----------------------------------------------------------------------
// class sFileIOUtils::RSyncFiles()
//----------------------------------------------------------------------
int sFileIOUtils::RSyncFiles(const std::string& source_host_name, const std::string& source_host_ip_address, const std::string& source_directory, const std::vector<std::string>& source_file_names, const std::string& target_directory, const std::string &optional_rsync_flags)
{
  std::string file_list_file_name(target_directory + "sfileioutils_rsyncfiles.txt");
  ofstream tmp_file_list(file_list_file_name.c_str());
  std::ostream_iterator<std::string> tmp_file_list_iterator(tmp_file_list, "\n");
  unique_copy(source_file_names.begin(), source_file_names.end(), tmp_file_list_iterator);
  tmp_file_list.close();

  std::stringstream rsync_command;
  rsync_command << "rsync -avr" << optional_rsync_flags << " --files-from=" << file_list_file_name << " ";
  if (source_host_ip_address == "")
  {
    rsync_command << inet_ntoa(sFileIOUtils::HostToIp(source_host_name));
  }
  else
  {
    rsync_command << source_host_ip_address;
  }
  rsync_command << ":"
                << source_directory
                << " "
                << target_directory;

  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::RSyncFiles() >>> executing <%s> ...\n", rsync_command.str().c_str());
  int ret = system(rsync_command.str().c_str());
  RRLIB_LOG_PRINTF(USER, "sFileIOUtils::RSyncFiles() >>> ... done.\n");

  RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::RSyncFiles() >>> finished with result %d\n", ret);
  return ret;
} // RSyncFiles()


//----------------------------------------------------------------------
// class sFileIOUtils::CheckAndGetFile()
//----------------------------------------------------------------------
bool sFileIOUtils::CheckAndGetFile(const std::string &file_name, std::string &full_local_file_name, const std::string& resource_repository, const std::string& resource_server, const std::string& local_resource_directory, const std::string& server_resource_directory, bool use_cache)
{
  RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> started with local_resource_directory <%s>, resource_repository <%s>, file_name <%s>, resource_server <%s>, server_resource_directory <%s>\n", local_resource_directory.c_str(), resource_repository.c_str(), file_name.c_str(), resource_server.c_str(), server_resource_directory.c_str());

  //!#####################################################################################################
  //! step 0: check whether token "resource_repository + filename" is in local cache
  //!         and thus file is *assumed* to have already been loaded since last clearing of cache
  //!#####################################################################################################
  std::map<std::string, std::string>::iterator resource_cache_entry;
  if (use_cache && (resource_cache_entry = sFileIOUtils::resource_cache.find(resource_repository + file_name)) != sFileIOUtils::resource_cache.end())
  {
    full_local_file_name = resource_cache_entry->second;
    return true;
  }


  //!#####################################################################################################
  //! step 1: check whether file can be loaded from local host in local directory
  //!         location of file is: "./ + resource_repository + filename"
  //!         --> resource_repository is extracted from relative path within given scene description file
  //!#####################################################################################################
  full_local_file_name = "./" + resource_repository + file_name;

  RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> 1. check: trying to load <%s>\n", full_local_file_name.c_str());
  ifstream try_1(full_local_file_name.c_str());
  if (try_1)
  {
    try_1.close();
  }
  else
  {
    //!#################################################################################################################
    //! step 2: check whether file can be loaded from local host in given local_resource_directory
    //!         location of file is: "local_resource_directory + resource_repository + filename"
    //!         --> resource_repository is extracted from relative path within given scene description file
    //!#################################################################################################################

    // replace possible environment variables in local_resource_directory by corresponding values
    std::string expanded_local_resource_directory;
    if (!sFileIOUtils::ShellExpandFilename(expanded_local_resource_directory, local_resource_directory + "/"))
    {
      RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::%s >> Could not expand local resource directory!\n", __FUNCTION__);
      return false;
    }
    full_local_file_name = (expanded_local_resource_directory + resource_repository + file_name);

    RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> 2. check: trying to load <%s>\n", full_local_file_name.c_str());
    ifstream try_2(full_local_file_name.c_str());
    if (try_2)
    {
      try_2.close();
    }
    else
    {
      //!#################################################################################################################
      //! step 3: check whether file can be loaded from resource server in given server_resource_directory
      //!         location of file is: "server_resource_directory + resource_repository + filename"
      //!#################################################################################################################

      // get local host name
      std::string local_host;
      if (use_cache && sFileIOUtils::cached_local_host.length() > 0)
      {
        local_host = sFileIOUtils::cached_local_host;
        RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> retrieved local_host <%s> from cache\n", local_host.c_str());
      }
      else
      {
        local_host = sFileIOUtils::cached_local_host = sFileIOUtils::GetHostName();
      }

      // get server ip address
      std::string server(resource_server);
      std::string server_ip_address;
      if (server != "")
      {
        // retrieve ip address of optional resource server
        std::map<std::string, std::string>::iterator pos;
        if (use_cache && ((pos = sFileIOUtils::host_name_to_ip_cache.find(server)) != sFileIOUtils::host_name_to_ip_cache.end()))
        {
          server_ip_address = pos->second;
          RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> retrieved ip address <%s> of host <%s> from cache\n", server_ip_address.c_str(), server.c_str());
        }
        else
        {
          server_ip_address = inet_ntoa(sFileIOUtils::HostToIp(server));
          RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> got ip address <%s> of host <%s>\n", server_ip_address.c_str(), server.c_str());

          if (server_ip_address == "0.0.0.0")
          {
            RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::constructor >>> zero ip address ... clearing server\n");
            server = "";
          }
          else
          {
            sFileIOUtils::host_name_to_ip_cache[ server ] = server_ip_address;
          }
        }
      }

      // start check
      if (server != "")   //&& server != local_host)
      {
        RRLIB_LOG_PRINTF(DEBUG_VERBOSE_1, "sFileIOUtils::CheckAndGetFile() >>> 3. check: trying to rsync <%s:%s> to <%s> \n", server_ip_address.c_str(), (server_resource_directory + resource_repository + file_name).c_str(), expanded_local_resource_directory.c_str());

        // rsync from <resource_server:server_resource_directory + resource_repository>
        //       to <local_resource_directory> on local host

        if (sFileIOUtils::RSyncFile("", server_ip_address, server_resource_directory + "/./" + resource_repository, file_name, expanded_local_resource_directory, "R") != 0)
        {
          RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::CheckAndGetFile() >>> could not rsync file <%s> from server <%s> at <%s> ... skipping\n", file_name.c_str(), server.c_str(), (server_resource_directory + resource_repository).c_str());
          return false;
        }
        full_local_file_name = (expanded_local_resource_directory + resource_repository + file_name);
      }
      else
      {
        RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::CheckAndGetFile() >>> could neither load <%s> locally nor from resource server ... skipping\n", file_name.c_str());
        return false;
      }
    }
  }

  //! ------------------------------- final check just to be sure that requested file is available --------------------
  ifstream try_3(full_local_file_name.c_str());
  if (!try_3)
  {
    RRLIB_LOG_PRINTF(ERROR, "sFileIOUtils::CheckAndGetFile() >>> final check failed: could not load <%s> ... skipping\n", full_local_file_name.c_str());
    return false;
  }
  else
  {
    try_3.close();
  }
  sFileIOUtils::resource_cache[ resource_repository + file_name ] = full_local_file_name;
  return true;
} // CheckAndGetFile()


//----------------------------------------------------------------------
// class sFileIOUtils::ClearCaches()
//----------------------------------------------------------------------
void sFileIOUtils::ClearCaches()
{
  sFileIOUtils::cached_local_host = "";
  sFileIOUtils::host_name_to_ip_cache.clear();
} // ClearCaches()


//----------------------------------------------------------------------
// class sFileIOUtils::ClearResourceCache()
//----------------------------------------------------------------------
void sFileIOUtils::ClearResourceCache()
{
  sFileIOUtils::resource_cache.clear();
} // ClearResourceCache()

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
