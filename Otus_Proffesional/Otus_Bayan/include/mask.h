#pragma once

#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <string>

class Mask {
private:
  boost::regex m_regex;
  boost::smatch m_what;

  void EscapeRegex(std::string &m_strRegex) {
    boost::replace_all(m_strRegex, ".", "\\.");
    boost::replace_all(m_strRegex, "*", "\\*");
    boost::replace_all(m_strRegex, "?", "\\?");
    boost::replace_all(m_strRegex, "\\?", ".");
    boost::replace_all(m_strRegex, "\\*", ".*");
  }
//--------------------------------------------------------------------//
public:
  explicit Mask(const std::string &a_strMask) {
    auto strMask = a_strMask;
    EscapeRegex(strMask);
    m_regex = boost::regex(strMask, boost::regex::icase);
  }

  bool Valid(const std::string &a_strValue) {
    return boost::regex_match(a_strValue, m_what, m_regex);
  }
};
