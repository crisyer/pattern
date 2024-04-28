#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*
定义享元模式（Flyweight Pattern）是一种结构型设计模式，
它旨在减少对象的数量，从而降低内存和性能消耗。
享元模式的核心思想是共享相同状态的多个对象，而不是为每个对象都分配独立的内存。
角色 享元模式包括以下几个关键角色：
    享元工厂（Flyweight Factory）：享元工厂是一个类，它负责创建和管理享元对象。
    它通常包括一个池（或缓存），用于存储已创建的享元对象，以便在需要时共享它们。

    享元（Flyweight）：享元是一个接口或抽象类，它定义了享元对象的接口。
    享元对象通常包括内部状态和外部状态，其中内部状态是可以共享的，而外部状态是不可共享的。

    具体享元（Concrete Flyweight）：具体享元是实现享元接口的具体类，它包含了内部状态，
    并根据外部状态进行相应的操作。

    客户端（Client）：客户端是使用享元模式的应用程序的一部分。
    客户端通常负责维护外部状态，并在需要时从享元工厂获取共享的享元对象。

    单例只能创建一个类对象，而享元一个类可以创建多个对象，每个对象被多处代码引用共享。
    而享元有点类似单例的变体，多例
    享元是为了复用减少对象的创建，而缓存为了提高访问效率


    享元模式确实可以存储和使用外部状态，但这些外部状态通常是瞬时的、与特定用例相关的，
    并且不是存储在享元对象内部的。在享元模式中，外部状态通常是通过方法参数传递给享元对象的，
    而不是存储为对象的持久状态。这是因为外部状态是与具体场景相关的，
    并且可能随时间变化或由不同的客户端代码设置。
*/
class object
{
    virtual void draw() = 0;
};

class Shape : object
{
private:
    string _name;

public:
    Shape(string name) : _name(name){};
    void draw()
    {
        cout << _name << endl;
    }

    void addColor(string name)
    {
        draw();
        cout << _name << endl;
    }
};

class factory
{
private:
    map<string, Shape *> cache;

public:
    Shape *putShape(string shape)
    {
        if (cache.count(shape) == 0)
        {
            Shape *s = new Shape(shape);
            cache[shape] = s;
            return s;
        }
        return cache[shape];
    }
};

int main()
{
    factory *f = new factory();
    Shape *s1 = f->putShape("circle");
    Shape *s2 = f->putShape("rectangle");
    Shape *s3 = f->putShape("circle");

    s1->addColor("red");
    s2->addColor("black");
    s3->addColor("blue");

    if (s1 == s3)
    {
        cout<<"flyweight works"<<endl;
    }
    
    return 0;
}