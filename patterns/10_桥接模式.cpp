#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
// 抽象（Abstraction）：定义了客户端使用接口，并通过一个指向实现类的引用来存储行为。
// 扩展抽象（Refined Abstraction）：扩展了抽象类，添加了与实现类相关的行为。
// 实现（Implementor）：定义了实现类的接口，这个接口不一定要与抽象类在同一个维度上。
// 具体实现（Concrete Implementor）：实现了实现类的接口，并定义了实现类的具体行为。

class TV
{
public:
    virtual ~TV() {}
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void tuneChannel(int channel) = 0;
};
class LGTV : public TV
{
public:
    void on() override
    {
        std::cout << "LG TV is on." << std::endl;
    }
    void off() override
    {
        std::cout << "LG TV is off." << std::endl;
    }
    void tuneChannel(int channel) override
    {
        std::cout << "Tuning LG TV to channel " << channel << std::endl;
    }
};
class RemoteController
{
protected:
    TV *tv;

public:
    RemoteController(TV *t) : tv(t) {}
    virtual ~RemoteController() {}
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void tuneChannel(int channel) = 0;
};
class LGRemote : public RemoteController
{
public:
    LGRemote(TV *t) : RemoteController(t) {}

    void turnOn() override
    {
        tv->on();
    }

    void turnOff() override
    {
        tv->off();
    }

    void tuneChannel(int channel) override
    {
        tv->tuneChannel(channel);
    }
};
int main()
{
    TV *tv = new LGTV();
    RemoteController *remote = new LGRemote(tv);

    remote->turnOn();       // 使用遥控器打开电视
    remote->tuneChannel(5); // 调到第5频道
    remote->turnOff();      // 关闭电视

    delete remote;
    delete tv;

    return 0;
}