
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
// 抽象（Abstraction）：定义了客户端使用接口，并通过一个指向实现类的引用来存储行为。
// 扩展抽象（Refined Abstraction）：扩展了抽象类，添加了与实现类相关的行为。
// 实现（Implementor）：定义了实现类的接口，这个接口不一定要与抽象类在同一个维度上。
// 具体实现（Concrete Implementor）：实现了实现类的接口，并定义了实现类的具体行为。

// 组合模式是一种行为型设计模式，它将对象组合成树形结构以表示部分 - 整体的层次结构。
//这种模式使得用户对单个对象和组合对象的使用具有一致性
class component
{
public:
    virtual void display() = 0;
};
class employee : component
{
private:
    string _name;
    vector<employee *> group;

public:
    employee(string name) : _name(name){};
    string getName()
    {
        return _name;
    };

    vector<employee *> getGroup()
    {
        return group;
    };

    void addMember(employee *m)
    {
        group.push_back(m);
    };

    void display() override
    {
        cout << _name + "\t";
        for (int i = 0; i < group.size(); i++)
        {
            if (group[i]->getGroup().size() != 0)
            {
                group[i]->display();
            }
        }
    }
    ~employee(){};
};

class company : component
{
private:
    employee *root;
    string _name;

public:
    company(string name, employee *component) : _name(name), root(component){};
    void display() override
    {
        root->display();
    };
};

int main()
{
    employee *root = new employee("CEO");
    employee *partALeader = new employee("partALeader");
    employee *partBLeader = new employee("partBLeader");
    root->addMember(partALeader);
    root->addMember(partBLeader);
    partALeader->addMember(new employee("engineer1"));
    partALeader->addMember(new employee("engineer2"));
    company *comp = new company("A", root);
    comp->display();
    return 0;
}