#pragma once


#include <boost/crc.hpp>
#include <memory>
#include <string>

#include <list>
#include <set>
#include <unordered_map>
#include <vector>

#include <fstream>
#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
//--------------------------------------------------------------------//
class ScannerDuplicate {
private:
  std::size_t m_block_size;
  boost::function<std::size_t(char *, std::size_t)> m_hash;

  std::unordered_map<std::string, std::pair<std::fstream, std::size_t>>
  scan_all_path_dupl(const std::set<boost::filesystem::path> &a_paths);
  std::list<std::vector<boost::filesystem::path>> path_dupl_files(
      std::unordered_map<std::string, std::pair<std::fstream, std::size_t>>
          &a_paths);

  static boost::function<std::size_t(char *, std::size_t)>
  create_hash(boost::optional<std::string> &a_alg_name);

  template <typename T>
  static boost::function<std::size_t(char *, std::size_t)> hash_func();
//--------------------------------------------------------------------//
public:
  ScannerDuplicate(boost::optional<std::size_t> &a_block_size,
                   boost::optional<std::string> &a_alg_name);

  std::list<std::vector<boost::filesystem::path>>
  scan(std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
           a_g_path);
};
//--------------------------------------------------------------------//