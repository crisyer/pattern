#include <iostream>
#include <string>
#include <vector>
using namespace std;

class EUSocket
{
public:
    virtual void provideElectric() = 0;
};

class USPlugin
{
public:
    void providePower()
    {
        // 实现美国标准的电力供应
        std::cout << "Providing power through American plug." << std::endl;
    }
};

// 适配器类：使得美国插头能够适配欧洲插座
class AmericanToEuropeanAdapter : public EUSocket
{
private:
    USPlugin adaptee; // 包含一个美国插头对象

public:
    AmericanToEuropeanAdapter(USPlugin p) : adaptee(p){};
    // 重写目标接口的函数，通过适配者类的功能实现
    void provideElectric() override
    {
        adaptee.providePower(); // 调用美国插头的供电方法
    }
};

// 客户端代码：客户端只认识欧洲插座
class Client
{
public:
    void useDevice(EUSocket &socket)
    {
        socket.provideElectric(); // 使用电力供应
    }
};

int main()
{
    USPlugin USPlugin;
    AmericanToEuropeanAdapter adapet(USPlugin);
    Client Client;
    Client.useDevice(adapet);
    return 0;
}