#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*
备忘录模式包括以下几个重要角色：
发起人Originator： 需要还原状态的那个对象，负责创建一个【备忘录】，并使用备忘录记录当前时刻的内部状态。
备忘录Memento: 存储发起人对象的内部状态，它可以包含发起人的部分或全部状态信息，但是对外部是不可见的，只有发起人能够访问备忘录对象的状态。
备忘录有两个接口，发起人能够通过宽接口访问数据，管理者只能看到窄接口，并将备忘录传递给其他对象。
管理者Caretaker: 负责存储备忘录对象，但并不了解其内部结构，管理者可以存储多个备忘录对象。
客户端：在需要恢复状态时，客户端可以从管理者那里获取备忘录对象，并将其传递给发起人进行状态的恢复。
*/

class Memo
{
private:
    int _state;

public:
    Memo(int state) : _state(state){};
    int getState()
    {
        return _state;
    };
};

class Originer
{
private:
    int _state;

public:
    Originer(int state) : _state(state){};
    void setState(Memo *memo)
    {
        _state = memo->getState();
    };

    void setState(int state)
    {
        _state = state;
    };
    Memo *createMemo()
    {
        return new Memo(_state);
    };

    void showState()
    {
        cout<< _state << endl;
    };
};

class StateKeeper
{
private:
    vector<Memo *> memos;

public:
    void setMemo(Memo *m)
    {
        memos.push_back(m);
    };
    Memo *getMemo(int index)
    {
        return memos[index];
    }
};

// 客户端代码
int main()
{
    Originer originer(1);
    StateKeeper stateKeeper;
    stateKeeper.setMemo(originer.createMemo());
    originer.setState(2);
    stateKeeper.setMemo(originer.createMemo());
    originer.setState(3);
    stateKeeper.setMemo(originer.createMemo());
    originer.showState();
    originer.setState(stateKeeper.getMemo(0));
    originer.showState();
    return 0;
}