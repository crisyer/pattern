#include <map>
#include <string>
#include <iostream>
using namespace std;

class item
{
public:
    virtual void show() = 0;
};

/*
* 工厂模式的意义
    简单工厂会导致一个工厂裹挟太多的逻辑
    工厂也设计成接口,这样,新增的生产任务,就不用修改代码,而是扩展代码.
    simple factory :
    1 -> muti
    factory:
    muti -> muti
*/
class Car : public item
{
private:
    string color;
    string type;

public:
    Car(string c, string t) : color(c), type(t) {}
    void show()
    {
        cout << "此汽车子颜色" << color << ", 型号为" << type << endl;
    }
    ~Car(){};
};

class Bike : public item
{
private:
    string type;
    string color;

public:
    Bike(string c, string t) : color(c), type(t){};
    void show()
    {
        cout << "此自行车颜色" << color << ", 型号为" << type << endl;
    }
    ~Bike() {}
};

class Factory
{
public:
    virtual item *createItem(string c, string t) = 0;
};

class CarFactory : public Factory
{
private:
public:
    item *createItem(string c, string t) override
    {
        return new Car(c, t);
    };
};

class BikeFactory : public Factory
{
private:
public:
    item *createItem(string c, string t) override
    {
        return new Bike(c, t);
    };
};

int main()
{
    BikeFactory bikeFactory;
    bikeFactory.createItem("red", "山地车");

    CarFactory carFactory;
    carFactory.createItem("blue", "suv");

    // 可以预见的是,如果要生产 轮船等等,只要实现 轮船类,和实现轮船工厂,并不需要修改到当前任何代码.
    return 0;
}