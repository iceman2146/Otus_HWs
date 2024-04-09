#include "files.h"


ScannerFile::ScannerFile(const std::vector<boost::filesystem::path> &a_excluded,
                         boost::optional<std::size_t> &a_depth,
                         std::vector<std::string> a_masks,
                         boost::optional<std::size_t> &a_size) {
  m_directorie_filter_ptr = create_filter_directorie(a_depth, a_excluded);
  m_file_filter_ptr = create_filter_file(a_size, a_masks);
}

std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
ScannerFile::scan(const std::vector<boost::filesystem::path> &a_include_paths) {
  std::unordered_map<std::size_t, std::set<boost::filesystem::path>> g_path =
      find_path(a_include_paths);
  delete_unique_path(g_path);

  return g_path;
}

std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
ScannerFile::find_path(const std::vector<boost::filesystem::path> &a_include_paths) {
  std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
      resultPaths;

  try {
    for (auto &a_include_path : a_include_paths) {
      if (boost::filesystem::exists(a_include_path) &&
          boost::filesystem::is_directory(a_include_path)) {
        boost::filesystem::recursive_directory_iterator iter(a_include_path), end;
        while (iter != end) {
          std::pair<boost::filesystem::path, std::size_t> scanPath =
              std::make_pair(iter->path(), iter.depth());
          if (boost::filesystem::is_directory(iter->path()) &&
              !m_directorie_filter_ptr->valid(scanPath)) {
            iter.disable_recursion_pending();
          } else {
            if (boost::filesystem::is_regular_file(iter->path())) {
              boost::filesystem::path path = iter->path();
              auto status = boost::filesystem::symlink_status(iter->path());
              if (status.type() == boost::filesystem::file_type::symlink_file) {
                auto current_path = boost::filesystem::read_symlink(iter->path());
                auto parent_path = iter->path().parent_path();
                path = boost::filesystem::canonical(current_path, parent_path);
              }

              if (m_file_filter_ptr->valid(path)) {
                std::size_t szSize = boost::filesystem::file_size(path);
                auto &uniquepaths = resultPaths[szSize];
                uniquepaths.insert(path);
              }
            }
          }

          boost::system::error_code ec;
          iter.increment(ec);
          if (ec) {
            std::cerr << "Error while accessing: " << iter->path().string()
                      << " :: " << ec.message() << '\n';
          }
        }
      }
    }
  } catch (const std::system_error &ex) {
    std::cerr << "Error: " << ex.what();
  }

  return resultPaths;
}

void ScannerFile::delete_unique_path(
    std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
        &a_g_path) {
  auto it = a_g_path.begin();

  while (it != a_g_path.end()) {
    if (it->second.size() < 2) {
      it = a_g_path.erase(it);
    } else {
      ++it;
    }
  }
}

std::unique_ptr<DirectorieFilter_base> ScannerFile::create_filter_directorie(
    boost::optional<std::size_t> &a_depth,
    const std::vector<boost::filesystem::path> &a_excluded) {
  std::size_t depth = 0;
  if (a_depth) {
    depth = a_depth.get();
  }
  auto filter_depth = std::make_unique<DirectorieFilterByDepth>(depth);
  auto filter_exclude = std::make_shared<DirectorieFilterExcluded>(a_excluded);
  filter_depth->point_next(filter_exclude);
  return filter_depth;
}

std::unique_ptr<FileFilter_base>
ScannerFile::create_filter_file(boost::optional<std::size_t> &a_size,
                              const std::vector<std::string> &a_alg_name) {
  std::size_t size = 1;
  if (a_size) {
    size = a_size.get();
  }
  auto filter_file_size = std::make_unique<FileFilterBySize>(size);
  auto filter_mask = std::make_shared<FileFilterByMask>(a_alg_name);
  filter_file_size->point_next(filter_mask);
  return filter_file_size;
}
