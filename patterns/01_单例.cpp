#include <map>
#include <string>
#include <iostream>
#include <atomic>
#include <thread>
#include <random>
using namespace std;

/*
* 单例的意义:
    1. 一个类只能有一个实例
    2. 只有一个全局访问点可以访问到该实例.
*/
class MartManager
{
private:
    MartManager(){};

    static atomic<int> counter; // 线程安全的计数器 想想问什么单例问题有的时候会引入线程安全的问题?
    // static int count;
    static MartManager *martManager;
    // 局部静态变量：在C++11及以后的版本中，局部静态变量（也称作局部静态成员变量或线程安全的局部静态）在第一次使用时会被自动初始化，
    // 并且这种初始化是线程安全的。这是因为编译器会确保在多线程环境中，只有一个线程能够执行初始化代码.
public:
    // tip1: 这里不能直接返回一个新的instance,而是返回唯一instance的指针.因为是取同一个实例,所以将唯一instance的地址传出去.
    // tip2: 因为需要全局都能找到这个经理,所以该get方法是 static的.
    static MartManager *getInstance()
    {
        int count = counter.fetch_add(1, std::memory_order_relaxed);
        count++;
        cout << "今天已经处理了" << count << "个问题" << endl;
        if (martManager == nullptr)
        {
            martManager = new MartManager();
        }
        return martManager;
    }
};
// 初始化静态成员变量
std::atomic<int> MartManager::counter(0);
MartManager *MartManager::martManager = nullptr;
// int MartManager::count = 0;

void threadFunction()
{
    // 多线程:
    // 创建一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 6); // 随机数范围从1ms到100ms
    int sleepTime = distrib(gen); // 睡眠随机时间
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime * 1000));
    MartManager::getInstance();
    // 这里可以进行其他操作...
}

int main()
{
    // 单线程:
    MartManager *MartManager = MartManager::getInstance();
    MartManager::getInstance();
    MartManager::getInstance();
    MartManager::getInstance();

    // 创建多个线程来模拟多线程环境
    for (int i = 0; i < 100; i++)
    {
        std::thread t(threadFunction);
        // 生成随机数作为睡眠时间（毫秒）
        t.detach();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}