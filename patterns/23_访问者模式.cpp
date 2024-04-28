
/**
 * 基本概念
基本概念
访问者模式（Visitor Pattern）是一种行为型设计模式，可以在不改变对象结构的前提下，对对象中的元素进行新的操作。

举个例子，假设有一个动物园，里面有不同种类的动物，
比如狮子、大象、猴子等。每个动物都会被医生检查身体，被管理员投喂，被游客观看，医生，游客，管理员都属于访问者。

基本结构：
访问者模式包括以下几个基本角色：

抽象访问者（Visitor）： 声明了访问者可以访问哪些元素，以及如何访问它们的方法visit。

具体访问者（ConcreteVisitor）： 实现了抽象访问者定义的方法，不同的元素类型可能有不同的访问行为。医生、管理员、游客都属于具体的访问者，
它们的访问行为不同。

抽象元素（Element）： 定义了一个accept方法，用于接受访问者的访问。

具体元素（ConcreteElement）： 实现了accept方法，是访问者访问的目标。

对象结构（Object Structure）： 包含元素的集合，可以是一个列表、一个集合或者其他数据结构。负责遍历元素，并调用元素的接受方法。
*/

#include <iostream>
#include <cmath>
#include <vector>

// 访问者接口
class Visitor
{
public:
    virtual void visit(class Circle &circle) = 0;
    virtual void visit(class Rectangle &rectangle) = 0;
};

// 元素接口
class Shape
{
public:
    virtual ~Shape() {} // 添加虚析构函数
    virtual void accept(Visitor &visitor) = 0;
};

// 具体元素类
class Circle : public Shape
{
private:
    int radius;

public:
    Circle(int radius) : radius(radius) {}

    int getRadius() const
    {
        return radius;
    }

    void accept(Visitor &visitor) override;
};

// 具体元素类
class Rectangle : public Shape
{
private:
    int width;
    int height;

public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    void accept(Visitor &visitor) override;
};

// 具体访问者类
class AreaCalculator : public Visitor
{
public:
    void visit(Circle &circle) override;
    void visit(Rectangle &rectangle) override;
};

// 对象结构类
class Shapes
{
private:
    std::vector<Shape *> shapes;

public:
    Shapes(const std::vector<Shape *> &shapes) : shapes(shapes) {}

    void accept(Visitor &visitor)
    {
        for (Shape *shape : shapes)
        {
            shape->accept(visitor);
        }
    }
};

// 实现 accept 函数
void Circle::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void Rectangle::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

// 实现 visit 函数
void AreaCalculator::visit(Circle &circle)
{
    double area = 3.14 * std::pow(circle.getRadius(), 2);
    std::cout << area << std::endl;
}

void AreaCalculator::visit(Rectangle &rectangle)
{
    int area = rectangle.getWidth() * rectangle.getHeight();
    std::cout << area << std::endl;
}

int main()
{
    std::vector<Shape *> shapes;
    shapes.push_back(new Circle(4));
    shapes.push_back(new Rectangle(2, 3));

    Shapes ss(shapes);
    AreaCalculator areaCalculator;
    ss.accept(areaCalculator);

    // 释放动态分配的内存
    for (Shape *shape : shapes)
    {
        delete shape;
    }
    return 0;
}