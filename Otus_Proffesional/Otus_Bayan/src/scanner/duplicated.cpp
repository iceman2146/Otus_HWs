#include "duplicated.h"


ScannerDuplicate::ScannerDuplicate(boost::optional<size_t> &a_block_size,
                                   boost::optional<std::string> &a_alg_name) {
  m_block_size = 1024;
  if (a_block_size) {
    m_block_size = a_block_size.get();
  }

  m_hash = create_hash(a_alg_name);
}

std::list<std::vector<boost::filesystem::path>> ScannerDuplicate::scan(
    std::unordered_map<std::size_t, std::set<boost::filesystem::path>>
        a_g_path) {
  std::list<std::vector<boost::filesystem::path>> resultPaths;

  for (const auto &group : a_g_path) {
    auto findDuplicates = scan_all_path_dupl(group.second);
    auto pathGroupedByDup = path_dupl_files(findDuplicates);

    std::copy(pathGroupedByDup.begin(), pathGroupedByDup.end(),
              std::back_inserter(resultPaths));
  }

  return resultPaths;
}

std::unordered_map<std::string, std::pair<std::fstream, std::size_t>>
ScannerDuplicate::scan_all_path_dupl(
    const std::set<boost::filesystem::path> &a_paths) {
  std::unordered_map<std::string, std::pair<std::fstream, std::size_t>> hashes;

  for (const boost::filesystem::path &path : a_paths) {
    std::string strPath = path.string();
    std::fstream read_stream(strPath, std::fstream::in);
    hashes[strPath] = std::make_pair(std::move(read_stream), 0);
  }

  std::vector<char> buffer(m_block_size);

  bool endFiles = false;
  while (!hashes.empty() && !endFiles) {
    for (auto &elem : hashes) {
      memset(buffer.data(), 0, m_block_size);
      auto &value = elem.second;

      auto readBytes = value.first.readsome(buffer.data(), m_block_size);
      endFiles = static_cast<size_t>(readBytes) < m_block_size;
      value.second = m_hash(buffer.data(), buffer.size());
    }

    auto it = hashes.begin();
    while (it != hashes.end()) {
      size_t szCount = 0;
      size_t curHash = it->second.second;

      std::for_each(hashes.begin(), hashes.end(),
                    [curHash, &szCount](const auto &value) {
                      if (value.second.second == curHash) {
                        ++szCount;
                      }
                    });

      if (szCount == 1) {
        it = hashes.erase(it);
      } else {
        ++it;
      }
    }
  }

  return hashes;
}

std::list<std::vector<boost::filesystem::path>>
ScannerDuplicate::path_dupl_files(
    std::unordered_map<std::string, std::pair<std::fstream, std::size_t>>
        &a_paths) {
  std::list<std::vector<boost::filesystem::path>> result;

  while (!a_paths.empty()) {
    std::vector<boost::filesystem::path> paths;

    std::size_t curHash = a_paths.begin()->second.second;
    auto it = a_paths.begin();
    while (it != a_paths.end()) {
      if (it->second.second == curHash) {
        paths.emplace_back(it->first);
        it = a_paths.erase(it);
      } else {
        ++it;
      }
    }

    if (!paths.empty()) {
      result.emplace_back(paths);
    }
  }

  return result;
}

boost::function<std::size_t(char *, std::size_t)>
ScannerDuplicate::create_hash(boost::optional<std::string> &a_alg_name) {
  if (a_alg_name) {
    if (a_alg_name.get() == "crc16"||a_alg_name.get() == "CRC16") {
      return hash_func<boost::crc_16_type>();
    } else if (a_alg_name.get() == "crc32"||a_alg_name.get() == "CRC32") {
      return hash_func<boost::crc_32_type>();
    }
  }

  return hash_func<boost::crc_32_type>();
}

template <typename T>
boost::function<std::size_t(char *, std::size_t)>
ScannerDuplicate::hash_func() {
  return [](char *a_buffer, std::size_t a_szCountBytes) {
    T algorithm;
    algorithm.process_bytes(a_buffer, a_szCountBytes);
    return algorithm.checksum();
  };
}
