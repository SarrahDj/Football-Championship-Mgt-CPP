#include <iostream>

using namespace std;
#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date(int day = 0, int month = 0, int year = 0) : day(day), month(month), year(year) {}

    void displayDate() const
    {
        cout << day << '-' << month << '-' << year << endl;
    }

    int getYear() { return year; }

private:
    int day, month, year;
};
#endif
