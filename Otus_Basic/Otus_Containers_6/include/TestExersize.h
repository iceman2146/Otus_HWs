#include <iostream>
template <typename T>
void print_seq(T &container)
{

  std::cout<<"\n========Print=========\n";
  std::cout << "array: "<<termcolor::magenta;
  for (size_t i = 0; i < container.size(); ++i)
  {
    std::cout << container[i] << ' ';
  }

  std::cout<<termcolor::white<< std::endl << "Size: " 
                                << container.size() << std::endl;
}

template <typename T>
void test_seq(T &container, size_t razmer)
{
  std::cout<<"\n*******Test*********\n";
  std::cout << "1. Creating container\n";
  if (!container.is_empty())
  {
    for (auto iter = container.begin(); iter != container.end();
         ++iter)
    {
      std::cout << iter.get() << ' ';
    }
  }

  for (int i = 0; i < razmer; i++)
  {
    container.push_back(i);
  }
  std::cout << "2. push to container from 0 to 9\n";
  print_seq(container);

  container.erase(7);
  container.erase(5);
  container.erase(3);
  std::cout << "3. erasing 3, 5 i 7 element" << std::endl;
  print_seq(container);

  container.insert(0, 10);
  std::cout << "4. pushing 10 to head" << std::endl;

  print_seq(container);

  std::cout << "5. pushing 20 to middle" << std::endl;
  container.insert(container.size() / 2, 20);

  print_seq(container);

  container.push_back(30);

  for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
  {
    std::cout << *iterator << ' ';
  }
  std::cout<<"\n*****Test_end*****\n";
  print_seq(container);
  
}