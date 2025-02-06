#include <iostream>

#ifndef TIME_H
#define TIME_H
class Time
{
private:
    int minutes;
    int seconds;

public:
    // Constructor
    Time(int m = 0, int s = 0) : minutes(m), seconds(s) {}

    // Display time
    void displayTime() const
    {
        if (minutes < 10 && seconds >= 10)
        {
            cout << 0 << minutes << ":" << seconds << setw(30) << left;
        }
        else if (minutes >= 10 && seconds < 10)
        {
            cout << minutes << ":" << 0 << seconds << setw(30) << left;
        }
        else if (minutes < 10 && seconds < 10)
        {
            cout << 0 << minutes << ":" << 0 << seconds << setw(30) << left;
        }
        else
        {
            cout << minutes << ":" << seconds << setw(30) << left;
        }
    }

    // Setters

    void setMinutes(int m)
    {
        minutes = m;
    }

    void setSeconds(int s)
    {
        seconds = s;
    }

    // Getters

    int getMinutes() const
    {
        return minutes;
    }

    int getSeconds() const
    {
        return seconds;
    }
};

#endif
