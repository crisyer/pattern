#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*
*/
class Steps
{
public:
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void step3() = 0;
};

class concreteSteps : public Steps
{
public:
    void step1() override
    {
        cout << "step1" << endl;
    };

    void step2() override
    {
        cout << "step2" << endl;
    };
    void step3() override
    {
        cout << "step3" << endl;
    };
};

// 客户端代码
int main()
{
    concreteSteps steps;
    steps.step1();
    steps.step2();
    steps.step3();
    return 0;
}