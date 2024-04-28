#include <iostream>
#include <vector>
#include <string>
using namespace std;
/**
 * 责任链模式是一种行为型设计模式，它允许你构建一个对象链，让请求从链的一端进入，然后沿着链上的对象依次处理，直到链上的某个对象能够处理该请求为止。
 *
 */

class HolidayHandler
{
public:
    virtual void handle(int days) = 0;
};

class Low : public HolidayHandler
{
private:
    int maxDaysLeave = 2;
    HolidayHandler *_next;

public:
    Low(HolidayHandler *next) : _next(next){};
    void handle(int days) override
    {
        if (days <= maxDaysLeave)
        {
            cout << "low handle this vacation. prove!" << endl;
        }
        else if (_next != nullptr)
        {
            _next->handle(days);
        }
        else
        {
            cout << "low can't handle this vacation. and no highlevel man can handle this" << endl;
        }
    };
};

class Middle : public HolidayHandler
{
private:
    int maxDaysLeave = 10;
    HolidayHandler *_next;

public:
    Middle(HolidayHandler *next) : _next(next){};
    void handle(int days) override
    {
        if (days <= maxDaysLeave)
        {
            cout << "Middle handle this vacation. prove!" << endl;
        }
        else if (_next != nullptr)
        {
            _next->handle(days);
        }
        else
        {
            cout << "Middle can't handle this vacation. and no highlevel man can handle this" << endl;
        }
    };
};

class High : public HolidayHandler
{
private:
    int maxDaysLeave = 30;

public:
    High(){};
    void handle(int days) override
    {
        if (days <= maxDaysLeave)
        {
            cout << "High handle this vacation. prove!" << endl;
        }
        else
        {
            cout << "High can't handle this vacation. and no highlevel man can handle this" << endl;
        }
    };
};

int main()
{
    HolidayHandler *director = new High();
    HolidayHandler *manager = new Middle(director);
    HolidayHandler *supervisor = new Low(manager);
    supervisor->handle(11);
    return 0;
}