#include "parser.h"



class InvalidOption: public std::logic_error 
{
public:
  explicit InvalidOption(const std::string &input)
    : std::logic_error(input) 
  { }
};

ArgumentParser::ArgumentParser()
  : m_opt_descriptor("CmdArguments")
{
  m_opt_descriptor.add_options()
    ("include,i",     boost::program_options::value<std::vector<boost::filesystem::path>>(),   "Include paths for scaning")
    ("exclude,e",     boost::program_options::value<std::vector<boost::filesystem::path>>(),   "Exclude paths from scaning")
    ("level,l",       boost::program_options::value<long>(),                     "scan nesting level, 0 - without nested")
    ("min-size,s",    boost::program_options::value<long>(),                     "Minimum file size in bytes for scaning")
    ("masks,m",       boost::program_options::value<std::vector<std::string>>(), "Masks for file names allowed for comparison")
    ("block-size,b",  boost::program_options::value<long>(),                     "Block size in bytes for reading file")
    ("algorithm,a",   boost::program_options::value<std::string>(),              "Hash algorithm: crc16 or crc32")
    ("help,h",        "Show help")  
  ;
}

boost::optional<CmdArguments> ArgumentParser::setup_cmd_line_argumrnts(int argc, char **argv) {
  try {
    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, m_opt_descriptor),
        m_var_map);
    boost::program_options::notify(m_var_map);

    if (m_var_map.count("help")) {
      std::cout << m_opt_descriptor << "\n";
      return boost::optional<CmdArguments>();
    }

    CmdArguments options;

    if (m_var_map.count("include")) {
      options.includePaths =
          m_var_map["include"].as<std::vector<boost::filesystem::path>>();
      for (auto &path : options.includePaths) {
        if (path.is_relative()) {
          path = boost::filesystem::canonical(path);
        }
      }
    } else {
      throw InvalidOption("Include scan paths not defined");
    }

    if (m_var_map.count("exclude")) {
      options.excludePaths =
          m_var_map["exclude"].as<std::vector<boost::filesystem::path>>();
      for (auto &path : options.excludePaths) {
        if (path.is_relative()) {
          path = boost::filesystem::canonical(path);
        }
      }
    }

    if (m_var_map.count("level")) {
      long nLevel = m_var_map["level"].as<long>();
      if (nLevel < 0) {
        throw InvalidOption("Level scaning must be integer");
      }
      options.levelScannig = static_cast<std::size_t>(nLevel);
    }

    if (m_var_map.count("min-size")) {
      long nMinSize = m_var_map["min-size"].as<long>();
      if (nMinSize < 1) {
        throw InvalidOption("Minimum file size must be greater then 1");
      }
      options.minFileSize = static_cast<std::size_t>(nMinSize);
    }

    if (m_var_map.count("masks")) {
      options.masks = m_var_map["masks"].as<std::vector<std::string>>();
    }

    if (m_var_map.count("block-size")) {
      long nBlockSize = m_var_map["block-size"].as<long>();
      if (nBlockSize < 1) {
        throw InvalidOption("Minimum file size must be greater then 1");
      }
      options.blockSize = static_cast<std::size_t>(nBlockSize);
    }

    if (m_var_map.count("algorithm")) {
      std::string strHash = m_var_map["algorithm"].as<std::string>();
      if (strHash != "crc32" && strHash != "crc16") {
        throw InvalidOption("The hash algorithm '" + strHash +
                            "' not supported");
      }
      options.hash = strHash;
    }

    return options;
  } catch (std::exception &ex) {
    std::cout << "Error: " << ex.what() << std::endl << std::endl;
    std::cout << m_opt_descriptor << std::endl;
    return boost::optional<CmdArguments>();
  }
}
