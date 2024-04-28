#include <map>
#include <string>
#include <iostream>
using namespace std;

// 为了一个工厂生产一组东西
class Sofa
{
public:
    virtual void showSofa() = 0;
};

class Chair
{
public:
    virtual void showChair() = 0;
};

class ModernSofa : public Sofa
{
    void showSofa() override
    {
        cout << "modern sofa";
    };
};

class ClassicSofa : public Sofa
{
    void showSofa() override
    {
        cout << "classic sofa";
    };
};

class ModernChair : public Chair
{
    void showChair() override
    {
        cout << "modern chair";
    };
};

class ClassicChair : public Chair
{
    void showChair() override
    {
        cout << "classic chair";
    };
};

class Factory
{
    virtual Chair *createChair() = 0;
    virtual Sofa *createSofa() = 0;
};

class ModernFactory : public Factory
{
public:
    Chair *createChair() override
    {
        return new ModernChair();
    }

    Sofa *createSofa() override
    {
        return new ModernSofa();
    }
};

class ClassicFactory : public Factory
{
public:
    Chair *createChair() override
    {
        return new ClassicChair();
    }

    Sofa *createSofa() override
    {
        return new ClassicSofa();
    }
};

int main()
{
    ModernFactory *factory = new ModernFactory();
    Chair *chair = factory->createChair();
    Sofa *sofa = factory->createSofa();

    chair->showChair();
    cout << endl;
    sofa->showSofa();
    cout << endl;

    // 可以预见的是,如果要生产 轮船等等,只要实现 轮船类,和实现轮船工厂,并不需要修改到当前任何代码.
    return 0;
}