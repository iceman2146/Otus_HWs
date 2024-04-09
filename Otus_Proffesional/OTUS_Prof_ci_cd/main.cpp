#include "lib.h"
#include "dummy.h"

#include <iostream>

int main (int, char **) {
    std::cout << "Version: " << version() << std::endl;
    std::cout << "Hello, world!" << std::endl;
    dummyFunc();
    int i=0;
    std::cout<<i;
    return 0;
}
