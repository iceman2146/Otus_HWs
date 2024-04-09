#pragma once
#include "mask.h"
#include <memory>
#include <string>
#include <vector>

#include <list>
#include <set>
#include <unordered_map>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

class DirectorieFilter_base {
public:
  virtual std::shared_ptr<DirectorieFilter_base> &
  point_next(const std::shared_ptr<DirectorieFilter_base>&) = 0;
  virtual bool
  valid(const std::pair<boost::filesystem::path, std::size_t>&) = 0;
};


class FileFilter_base {
public:
  virtual std::shared_ptr<FileFilter_base> &
  point_next(const std::shared_ptr<FileFilter_base>&) = 0;
  virtual bool valid(const boost::filesystem::path&) = 0;
};

//--------------------------------------------------------------------//





class DirectorieFilter : public DirectorieFilter_base {

private:
  std::shared_ptr<DirectorieFilter_base> m_next_directorie_filter;

public:
  DirectorieFilter() {}

  std::shared_ptr<DirectorieFilter_base> &
  point_next(const std::shared_ptr<DirectorieFilter_base> &a_next_directorie_filter) override {
    this->m_next_directorie_filter = a_next_directorie_filter;
    return m_next_directorie_filter;
  }

  bool valid(
      const std::pair<boost::filesystem::path, std::size_t> &a_path) override {
    if (m_next_directorie_filter) {
      return m_next_directorie_filter->valid(a_path);
    }

    return true;
  }
};

//--------------------------------------------------------------------//

class FileFilter : public FileFilter_base {

private:
  std::shared_ptr<FileFilter_base> m_next_file_filter;

public:
  FileFilter() {}

  std::shared_ptr<FileFilter_base> &
  point_next(const std::shared_ptr<FileFilter_base> &a_next_file_filter) override {
    this->m_next_file_filter = a_next_file_filter;
    return m_next_file_filter;
  }

  bool valid(const boost::filesystem::path &a_path) override {
    if (m_next_file_filter) {
      return m_next_file_filter->valid(a_path);
    }
    return true;
  }
};