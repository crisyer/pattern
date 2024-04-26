#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
class BrewCoffee
{
public:
    virtual void brew() = 0;
};

class BrewBlackBeanCoffee : public BrewCoffee
{
public:
    void brew() override
    {
        cout << "brew black bean coffee" << endl;
    }
};

class BrewPowderCoffee : public BrewCoffee
{
public:
    void brew() override
    {
        cout << "brew powder coffee" << endl;
    }
};

class Decorate : public BrewCoffee
{
protected:
    unique_ptr<BrewCoffee> _brew;

public:
    Decorate(unique_ptr<BrewCoffee> brew) : _brew(std::move(brew)){};
    void brew() override
    {
        if (_brew)
        {
            _brew->brew();
        }
    }
};

class MilkDecorator : public Decorate
{
public:
    MilkDecorator(std::unique_ptr<BrewCoffee> coffee) : Decorate(std::move(coffee)) {}
    void brew() override
    {
        Decorate::brew();
        std::cout << "Adding Milk" << std::endl;
    }
};

int main()
{
    std::unique_ptr<BrewCoffee> coffee;
    coffee = std::make_unique<BrewBlackBeanCoffee>();
    coffee = std::make_unique<MilkDecorator>(std::move(coffee));
    coffee->brew();
    return 0;
}