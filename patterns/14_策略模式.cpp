#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*
那什么时候可以考虑使用策略模式呢？
当一个系统根据业务场景需要动态地在几种算法中选择一种时，可以使用策略模式。
如，根据用户的行为选择不同的计费策略。
当代码中存在大量条件判断，条件判断的区别仅仅在于行为，也可以通过策略模式来消除这些条件语句。
*/
class strategy
{
public:
    virtual int discount(int price) = 0;
};

class percentStrategy : public strategy
{
public:
    percentStrategy(){};
    int discount(int price) override
    {
        return price * 0.9;
    }
};

class manjianStrategy :public strategy
{
private:
    int prices[4] = {100, 50, 30, 20};
    int discounts[4] = {10, 5, 3, 1};

public:
    int discount(int price) override
    {
        for (int i = sizeof(prices) / sizeof(int) - 1; i >= 0; i--)
        {
            if (price > prices[i])
            {
                price -= discounts[i];
                return price;
            }
        }
        return price;
    }
};

class DiscountContext
{
private:
    strategy *discountStrategy;

public:
    DiscountContext(strategy *discountStrategy)
    {
        this->discountStrategy = discountStrategy;
    }

    int applyDiscount(int originalPrice)
    {
        return discountStrategy->discount(originalPrice);
    }
};

int main()
{
    strategy *discount;
    discount = new percentStrategy();
    DiscountContext* context=new DiscountContext(discount);
    cout<< context->applyDiscount(100);
    return 0;
}