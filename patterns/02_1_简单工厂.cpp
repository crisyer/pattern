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
* 简单工厂的意义:
    一个方法或者一个工厂干所有的事情,不同的产品进来,仅靠if else来区分然后有不同的逻辑
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
    Factory(string s)
    {
        if (s == "Bike") // 这里可以预见的是,如果要造新能源/滑板等等,我们不仅要准备新的物品类,还要在这里的if else要增加逻辑.
                         // 这就违背了 开闭原则
        {
            Bike bike("紫色", "山地车");
            bike.show();
        }
        else if (s == "car")
        {
            Car car("蓝色", "SUV");
            car.show();
        }
    }
    ~Factory() {}
};

int main()
{
    string s;
    cin >> s;        // 下方的Factory.输入需求,生产对应的物品.
    Factory factory(s);
    return 0;
}