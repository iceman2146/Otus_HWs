#include "duplicated.h"
#include "files.h"
#include "parser.h"

int main(int argc, char **argv) {
  ArgumentParser optionsParser;
  auto options = optionsParser.setup_cmd_line_argumrnts(argc, argv);
  if (!options) {
    return 0;
  }

  ScannerFile fileScanner(options.get().excludePaths,
                          options.get().levelScannig, options.get().masks,
                          options.get().minFileSize);
  auto g_path = fileScanner.scan(options.get().includePaths);

  ScannerDuplicate dupScanner(options.get().blockSize, options.get().hash);
  auto duplicates = dupScanner.scan(g_path);

  for (auto &dup : duplicates) {
    for (auto &path : dup) {
      std::cout << path << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}