#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;

    std::cout << "What is your name? ";
    std::getline(std::cin, name);

    std::cout << "How old are you? ";
    std::cin >> age;

    std::cout << "Your name is " << name << " and you are " << age << " years old." << std::endl;

    return 0;
}