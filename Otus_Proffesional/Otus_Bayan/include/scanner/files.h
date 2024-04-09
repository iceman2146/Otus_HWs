#pragma once

#include "directorie_filter.h"
#include "file_filter.h"
#include "mask.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

//--------------------------------------------------------------------//
class ScannerFile {

private:
  std::unique_ptr<DirectorieFilter_base> m_directorie_filter_ptr;
  std::unique_ptr<FileFilter_base> m_file_filter_ptr;

  static std::unique_ptr<DirectorieFilter_base>
  create_filter_directorie(boost::optional<std::size_t> &a_depth,
                  const std::vector<boost::filesystem::path> &a_excluded);
  static std::unique_ptr<FileFilter_base>
  create_filter_file(boost::optional<std::size_t> &a_size,
                   const std::vector<std::string> &a_alg_name);

  std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
  find_path(const std::vector<boost::filesystem::path> &a_include_paths);
  void delete_unique_path(
      std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
          &a_g_path);
//--------------------------------------------------------------------//
public:
  ScannerFile(const std::vector<boost::filesystem::path> &a_excluded,
              boost::optional<std::size_t> &a_depth,
              std::vector<std::string> a_masks,
              boost::optional<std::size_t> &a_size);
  ~ScannerFile() = default;

  std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
  scan(const std::vector<boost::filesystem::path> &a_include_paths);
};
//--------------------------------------------------------------------//