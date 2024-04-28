
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
// 外观模式Facade Pattern, 也被称为“门面模式”，是一种结构型设计模式，外观模式定义了一个高层接口，
// 这个接口使得子系统更容易使用，同时也隐藏了子系统的复杂性。
// 门面模式可以将子系统关在“门里”隐藏起来，客户端只需要通过外观接口与外观对象进行交互，
// 而不需要直接和多个子系统交互，无论子系统多么复杂，对于外部来说是隐藏的，这样可以降低系统的耦合度。
class partA
{
public:
	void partAFunction()
	{
		cout << "part A running" <<endl;
	};
};

class partB
{
public:
	void partBFunction()
	{
		cout << "part B running"<<endl;
	};
};

class facade
{
private:
	partA *_partA;
	partB *_partB;

public:
	facade(partA *partA, partB *partB) : _partA(partA), _partB(partB){};
	void function()
	{
		_partA->partAFunction();
		_partB->partBFunction();
	};
};

int main()
{
	partA partA;
	partB partB;
	facade facade(&partA,&partB);
	facade.function();
	return 0;
}