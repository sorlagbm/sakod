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
    student(const student& obj){
        this->surname = obj.surname;
        this->groupNumber = obj.groupNumber;
        this->isInGroup = obj.isInGroup;
        this->wasCount = obj.wasCount;
    }
    int readFromFile(const std::string& FileName);
    int writeToFile(const std::string& FileName);
    bool operator==(student item){
        return this->surname == item.surname;
    }
    bool operator<(student item){
        return this->surname < item.surname;
    }

public:
    std::string surname;
    bool isInGroup;
    int groupNumber;
    int wasCount = 0;
};

#endif // STUDENT_H
