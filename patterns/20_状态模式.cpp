#include <iostream>
#include <vector>
#include <string>
using namespace std;
// 状态接口
class State {
public:
    virtual std::string handle() = 0;  // 处理状态的方法
};
 
// 具体状态类
class OnState : public State {
public:
    std::string handle() override {
        return "Light is ON";
    }
};
 
class OffState : public State {
public:
    std::string handle() override {
        return "Light is OFF";
    }
};
 
class BlinkState : public State {
public:
    std::string handle() override {
        return "Light is Blinking";
    }
};
 
// 上下文类
class Light {
private:
    State* state;  // 当前状态
 
public:
    Light() : state(new OffState()) {}  // 初始状态为关闭
 
    void setState(State* newState) {  // 设置新的状态
        delete state;  // 释放之前的状态对象
        state = newState;
    }
 
    std::string performOperation() {  // 执行当前状态的操作
        return state->handle();
    }
 
    ~Light() {
        delete state;  // 释放内存
    }
};

int main()
{
    Light light;
    cout << light.performOperation() << endl;
    light.setState(new BlinkState());
    cout << light.performOperation() << endl;
    return 0;
}