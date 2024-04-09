#include "read.h"
#include "execute.h"
#include "log.h"

#include <string>
#include <memory>
/**
 * @file main.cpp 
 * 
 */

/**
* @brief функция main
* Основная функция main
* @return возвращает код ошибки
*/

int main(int argc, const char **argv)
{
  if (argc < 2)
  {
    std::cerr << "bulk.exe <N>(N>2)(bulk.exe 4)" << std::endl;
    return 1;
  }
  std::size_t blocks{0};

  std::shared_ptr<Reader> read = Reader::create(blocks);
  std::shared_ptr<Executer> execute = Executer::create(read);
  std::shared_ptr<Logger> log = Logger::create(read);

  read->enter();

  return 0;
}