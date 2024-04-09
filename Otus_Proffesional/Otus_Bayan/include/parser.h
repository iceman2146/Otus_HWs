#pragma once

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <vector>

#include <iostream>
#include <exception>

struct CmdArguments {
  std::vector<boost::filesystem::path> includePaths;
  std::vector<boost::filesystem::path> excludePaths;
  boost::optional<std::size_t> levelScannig;
  boost::optional<std::size_t> minFileSize;
  std::vector<std::string> masks;
  boost::optional<std::size_t> blockSize;
  boost::optional<std::string> hash;
};

class ArgumentParser {
private:
  boost::program_options::options_description m_opt_descriptor;
  boost::program_options::variables_map m_var_map;

public:
  ArgumentParser();

  

  boost::optional<CmdArguments> setup_cmd_line_argumrnts(int argc, char **argv);
};
