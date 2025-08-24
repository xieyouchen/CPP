#include <bits/stdc++.h>

using namespace std;

class Event {
public:
    virtual ~Event() = default;
};

class KeyEvent: public Event {
public:
};

class EventDispatcher {
public:
    EventDispatcher(Event& e): m_Event(e){}

    template<typename T>
    bool Subscribe(function<bool(T&)> callback) {
        return callback(static_cast<T&>(m_Event));
    }
private:
    Event m_Event;
};

int main() {
    KeyEvent e;
    EventDispatcher dispatcher(e);
    dispatcher.Subscribe<KeyEvent>([](KeyEvent& e){
        cout << "dispatched.\n";
        return true;
    });

    return 0;
}