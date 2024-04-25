#include <iostream>
#include <string>
#include <vector>
using namespace std;

class prototype
{
public:
    virtual prototype *clone() const = 0;
    virtual ~prototype(){};
    virtual string getDetails() const = 0;
    virtual bool operator==(prototype* p){
        return this == p;
    };
};

class car : public prototype
{
private:
    string color;

public:
    car(string c) : color(c){};
    prototype *clone() const override
    {
        return new car(*this);
    };
    string getDetails() const
    {
        return color;
    };
};

int main()
{
    car car("blue");
    prototype* cloneCar = car.clone();
    cout<< cloneCar->getDetails()<< endl;
    string s = car == cloneCar ?"true" : "false";
    cout<< s << endl;
    return 0;
}