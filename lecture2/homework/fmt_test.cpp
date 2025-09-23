//作业：试用fmt的print和format函数
#include <fmt/format.h>
#include <iostream>

int main() 
{
    int age = 20;
    double pi = 3.14159;
    char level = 'A';
    bool is_student = true;

    fmt::print("Age: {}\n", age);
    fmt::print("Pi: {:.5f}\n", pi);
    fmt::print("Level: {}\n", level);
    fmt::print("Is student: {}\n", is_student);

    std::string sentence = fmt::format("Student Info - Age: {}, Level: {}, Is Student: {}", age, level, is_student);
    std::cout << sentence << std::endl;
    return 0;
}