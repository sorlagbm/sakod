#ifndef CLASS_H
#define CLASS_H
#include <string>

struct Date {

    unsigned day;
    unsigned month;
    unsigned year;
    Date(unsigned Day = 0, unsigned Month = 0, unsigned Year = 0)
        : day(Day), month(Month), year(Year) {}

};

class Task
{
public:
    Task(Date _Date = Date(), std::string Name = "") : date(_Date), name(Name) {}
    Date date;
    std::string name;
    int readFromFile(const std::string& FileName);
    int writeToFile(const std::string& FileName);

};

#endif // CLASS_H
