#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 和适配器模式不同的是,一个是适配两边的不同地方, 一个是1. 确保访问的权限,以及2. 扩展 被代理对象的功能.
class House
{
private:
    int _area;
    int _locationGrade;

public:
    House(int area, int locationGrade) : _area(area), _locationGrade(locationGrade){};
    int getArae()
    {
        return _area;
    };
    int getLocationGrade()
    {
        return _locationGrade;
    }
};

class BuyHouse
{
public:
    virtual bool buyHouse(House house) = 0;
};

class HouseBuyer : public BuyHouse
{
public:
    bool buyHouse(House house)
    {
        cout << "购买成功" << endl;
        return true;
    }
};

class HighCostAgent : public BuyHouse
{
private:
    HouseBuyer houseBuyer;

public:
    HighCostAgent(HouseBuyer hb) : houseBuyer(hb){};
    bool buyHouse(House house)
    {
        if (house.getArae() > 100 && house.getLocationGrade() == 1)
        {
            houseBuyer.buyHouse(house);
            return true;
        }else{
            cout<< "不买了,不够高级"<<endl;
            return false;
        }
    }
};

class LowCostAgent : public BuyHouse
{
private:
    HouseBuyer houseBuyer;

public:
    LowCostAgent(HouseBuyer hb) : houseBuyer(hb){};
    bool buyHouse(House house)
    {
        if (house.getArae() <= 3)
        {
            houseBuyer.buyHouse(house);
            return true;
        }else{
            cout<<"太贵了 不买了" <<endl;
            return false;
        }
    }
};

int main()
{
    House expensivceHouse(120, 1);
    HouseBuyer rich;
    HighCostAgent hcAgent(rich);
    hcAgent.buyHouse(expensivceHouse);

    House cheapHouse(40, 9);
    HouseBuyer poor;
    LowCostAgent LCAgent(poor);
    LCAgent.buyHouse(expensivceHouse);
    return 0;
}