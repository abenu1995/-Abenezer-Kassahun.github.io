#include <iostream>
#include <string>

int main() {
    std::string length_input;
    std::string width_input;
    double length;
    double width;

    std::cout << "Enter the length of the rectangle: ";
    std::getline(std::cin, length_input);
    length = std::stod(length_input);

    std::cout << "Enter the width of the rectangle: ";
    std::getline(std::cin, width_input);
    width = std::stod(width_input);

    double area = length * width;
    double perimeter = 2 * (length + width);

    std::cout << "The area of the rectangle is " << area << std::endl;
    std::cout << "The perimeter of the rectangle is " << perimeter << std::endl;

    return 0;
}
