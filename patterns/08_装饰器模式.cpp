#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
class coffee
{
public:
    virtual void brew() = 0;
};

class blackCofee : public coffee
{
public:
    void brew() override
    {
        cout << "brew black coffee" << endl;
    }
};

class lattee : public coffee
{
public:
    void brew() override
    {
        cout << "brew lattee coffee" << endl;
    }
};

class Decorate : public coffee
{
private:
    std::unique_ptr<coffee> _coffee;
public:
    Decorate(std::unique_ptr<coffee> coffee) : _coffee(std::move(coffee)){};
    void brew() override
    {
        _coffee->brew();
    }
};
class milkDecorate : public coffee
{
private:
    std::unique_ptr<coffee> _coffee;
public:
    milkDecorate(std::unique_ptr<coffee> coffee) : _coffee(std::move(coffee)){};
    void brew() override
    {
        _coffee->brew();
        cout << "brew lattee coffee" << endl;
    }
};
int main(){
    std::unique_ptr<coffee> coffee;
    coffee = std::make_unique<blackCofee>();
    coffee = std::make_unique<milkDecorate>(std::move(coffee));
    coffee->brew();
    return 0;
}