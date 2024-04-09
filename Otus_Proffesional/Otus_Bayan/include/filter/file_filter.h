#pragma once
#include "filters_base.h"
//--------------------------------------------------------------------//
class FileFilterBySize : public FileFilter {
  private:
  std::size_t m_size;
public:
  FileFilterBySize(std::size_t a_size) : FileFilter(), m_size(a_size) {}

  bool valid(const boost::filesystem::path &a_path) override {
    if (boost::filesystem::file_size(a_path) < m_size) {
      ;
      return false;
    }
    return FileFilter::valid(a_path);
  }


};
//--------------------------------------------------------------------//
class FileFilterByMask : public FileFilter {
private:
  std::vector<Mask> m_masks;

public:
  FileFilterByMask(const std::vector<std::string> &a_parsed_masks)
      : FileFilter() {
    for (auto &mask : a_parsed_masks) {
      m_masks.emplace_back(Mask(mask));
    }
  }

  bool valid(const boost::filesystem::path &a_path) override {
    if (!m_masks.empty()) {
      auto filename = a_path.filename().string();
      return std::any_of(
          m_masks.begin(), m_masks.end(),
          [filename](Mask &mask) { return mask.Valid(filename); });
    }
    return FileFilter::valid(a_path);
  }
};
//--------------------------------------------------------------------//