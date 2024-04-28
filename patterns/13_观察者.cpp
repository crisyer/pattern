#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*
使用观察者模式有很多好处，比如说观察者模式将主题和观察者之间的关系解耦，
主题只需要关注自己的状态变化，而观察者只需要关注在主题状态变化时需要执行的操作，
两者互不干扰，并且由于观察者和主题是相互独立的，可以轻松的增加和删除观察者，
这样实现的系统更容易扩展和维护。

主题Subject， 一般会定义成一个接口，提供方法用于注册、删除和通知观察者，通常也包含一个状态，当状态发生改变时，通知所有的观察者。
观察者Observer: 观察者也需要实现一个接口，包含一个更新方法，在接收主题通知时执行对应的操作。
具体主题ConcreteSubject: 主题的具体实现, 维护一个观察者列表，包含了观察者的注册、删除和通知方法。
具体观察者ConcreteObserver: 观察者接口的具体实现，每个具体观察者都注册到具体主题中，当主题状态变化并通知到具体观察者，具体观察者进行处理。
*/
class publish
{
    virtual void publishVedio(string name) = 0;
};

class viewer
{
public:
    void reciver(string s)
    {
        cout << "接收到新的视频" + s << endl;
    };
};

class up : publish
{
private:
    vector<viewer *> viewers;
    string _name;

public:
    up(string name) : _name(name){};

    void NewSubscribe(viewer *viewer)
    {
        viewers.push_back(viewer);
    };

    void cancelSubscribe(viewer *viewer)
    {
        for (int i = 0; i < viewers.size(); i++)
        {
            if (viewers[i] == viewer)
            {
                viewers.erase(viewers.begin() + i);
                cout << "viewer取消订阅" << endl;
            }
        }
    }

    void sendMessage(string s)
    {
        for (int i = 0; i < viewers.size(); i++)
        {
            viewers[i]->reciver(s);
        }
    }
    void publishVedio(string name) override
    {
        sendMessage("发布视频" + name);
    }
};

int main()
{
    up jikewan("极客湾");
    viewer *viewer1 = new viewer();
    viewer *viewer4 = new viewer();
    viewer *viewer2 = new viewer();
    viewer *viewer3 = new viewer();
    jikewan.NewSubscribe(viewer1);
    jikewan.NewSubscribe(viewer2);
    jikewan.NewSubscribe(viewer3);
    jikewan.NewSubscribe(viewer4);
    jikewan.publishVedio("888翻车");
    jikewan.cancelSubscribe(viewer4);
    return 0;
}