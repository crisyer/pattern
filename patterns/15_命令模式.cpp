#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*
命令模式（Command Pattern）是一种行为型设计模式，它将一个请求封装为一个对象，从而允许用户使用不同的请求、队列或日志请求来参数化其他对象。
命令模式也支持可撤销的操作。它通常用于解耦执行操作的对象与请求操作的对象。
命令模式的优点在于它将调用操作的对象与知道如何实现操作的对象解耦。这使得你可以通过编程方式动态地生成和修改命令队列，同时保持调用者和接收者的简单性。
此外，命令模式可以很容易地扩展以支持日志功能、事务处理、宏命令等功能。
*/
class Command
{
public:
    virtual void execute() = 0;
};

class Light
{
public:
    void turnOff()
    {
        cout << "关灯" << endl;
    };
    void turnON()
    {
        cout << "开灯" << endl;
    }
};

class TurnOn : public Command
{
private:
    Light &_light;

public:
    TurnOn(Light &light) : _light(light){};
    void execute() override
    {
        _light.turnON();
    }
};

class TurnOff : public Command
{
private:
    Light &_light;

public:
    TurnOff(Light &light) : _light(light){};
    void execute() override
    {
        _light.turnOff();
    }
};

class RemoteControl {
private:
    Command* command;

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void pressButton() {
        command->execute();
    }
};

int main()
{
    Command *command;
    Light light;
    command = new TurnOn(light);
    command->execute();
    command = new TurnOff(light);
    command->execute();
    return 0;
};