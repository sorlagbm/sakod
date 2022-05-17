#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "task.h"
#define IS_STUDENT(n) n == 1 ? true : false;

class student
{
public:
    student(const std::string& Surname = "", const bool& IsInGroup = false, const int& GroupNumber = -1)
        : surname(Surname), isInGroup(IsInGroup), groupNumber(isInGroup ? GroupNumber : -1) {}
    int readFromFile(const std::string& FileName);
    int writeToFile(const std::string& FileName);

public:
    std::string surname;
    bool isInGroup;
    int groupNumber;
};

#endif // STUDENT_H
