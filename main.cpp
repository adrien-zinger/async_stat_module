#include <iostream>
#include "main.hpp"

std::string getHello() {
    return "Hello world";
}

int main(int, char**) {
    std::cout << getHello() << std::endl;
}
