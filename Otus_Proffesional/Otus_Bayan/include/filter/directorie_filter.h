#pragma once
#include "filters_base.h"
//--------------------------------------------------------------------//
class DirectorieFilterByDepth : public DirectorieFilter {

private:
  std::size_t m_depth;

public:
  DirectorieFilterByDepth(std::size_t a_depth)
      : DirectorieFilter(), m_depth(a_depth) {}

  bool valid(
      const std::pair<boost::filesystem::path, std::size_t> &a_path) override {
    if (a_path.second >= m_depth) {
      ;
      return false;
    }
    return DirectorieFilter::valid(a_path);
  }
};
//--------------------------------------------------------------------//
class DirectorieFilterExcluded : public DirectorieFilter {
private:
  std::vector<boost::filesystem::path> m_excl_path;

public:
  DirectorieFilterExcluded(
      const std::vector<boost::filesystem::path> &a_excl_path)
      : DirectorieFilter(), m_excl_path(a_excl_path) {}

  bool valid(
      const std::pair<boost::filesystem::path, std::size_t> &a_path) override {
    if (!m_excl_path.empty()) {
      auto path = a_path.first;
      auto it =
          std::find_if(m_excl_path.begin(), m_excl_path.end(),
                       [path](const boost::filesystem::path &exclude_path) {
                         return path == exclude_path;
                       });

      if (it != m_excl_path.end()) {
        return false;
      }
    }

    return DirectorieFilter::valid(a_path);
  }
};
//--------------------------------------------------------------------//