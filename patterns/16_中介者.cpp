#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;
/*

中介者模式（Mediator Pattern）是一种行为型设计模式，它定义了一个中介对象，用以封装一系列对象之间的交互。
中介者模式的目的是减少对象之间的耦合，使得对象之间不必相互了解细节，而是通过中介者对象来进行通信。
*/

// 1. Mediator 接口
class ChatRoomMediator {
public:
    virtual ~ChatRoomMediator() {}
    virtual void sendMessage(const std::string& user, const std::string& message) = 0;
};

// 2. ConcreteMediator 具体中介者
class ChatRoom : public ChatRoomMediator {
private:
    std::vector<std::string> users;

public:
    void addUser(const std::string& user) {
        users.push_back(user);
    }

    void sendMessage(const std::string& user, const std::string& message) override {
        for (const auto& receiver : users) {
            if (receiver != user) {
                notify(receiver, user, message);
            }
        }
    }

private:
    void notify(const std::string& receiver, const std::string& sender, const std::string& message) {
        std::cout << sender << " says to " << receiver << ": " << message << std::endl;
    }
};

// 3. Colleague 同事类
class User {
private:
    std::string name;
    ChatRoomMediator& mediator;

public:
    User(const std::string& name, ChatRoomMediator& mediator) : name(name), mediator(mediator) {}

    void sendMessage(const std::string& receiver, const std::string& message) {
        mediator.sendMessage(name, message);
    }
};

// 客户端代码
int main() {
    ChatRoom chatRoom;
    User alice("Alice", chatRoom);
    User bob("Bob", chatRoom);

    chatRoom.addUser("Alice");
    chatRoom.addUser("Bob");

    alice.sendMessage("Bob", "Hi, Bob!");
    bob.sendMessage("Alice", "Hello, Alice!");

    return 0;
}