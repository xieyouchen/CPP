#include <bits/stdc++.h>

using namespace std;

enum class EventType {
    None,
    Key,
    Mouse
};

class Event {
public:
    virtual ~Event() = default;
    virtual EventType GetType() = 0;
};

#define CLASS_TYPE(T) \
    static EventType GetStaticType() { \
        return EventType::T; \
    } \
    virtual EventType GetType() override { \
        return GetStaticType(); \
    }

class KeyEvent: public Event {
public:
    KeyEvent(int key): m_Key(key) {}
    int m_Key;

    CLASS_TYPE(Key)
};

class MouseEvent: public Event {
public:
    MouseEvent(int x, int y): m_X(x), m_Y(y) {}
    
    CLASS_TYPE(Mouse)

private:
    int m_X, m_Y;
};

class EventDispatcher {
public:
    template<typename T>
    bool Subscribe(function<bool(T&)> callback) {
        auto type = T::GetStaticType();
        m_Observers[type] = [callback](Event& e){
            return callback(static_cast<T&>(e));
        };
        return true;
    }

    void Dispatch(Event& e) {
        auto type = e.GetType();
        if(m_Observers.find(type) != m_Observers.end()) {
            m_Observers[type](e);
        }
    }

private:
    unordered_map<EventType, function<bool(Event&)>> m_Observers;
};  

int main() {
    KeyEvent e(1);
    MouseEvent m(1, 2);
    EventDispatcher dispatcher;

    dispatcher.Subscribe<KeyEvent>([](KeyEvent& e){
        cout << "key event dispatched.\n";
        return true;
    });
    dispatcher.Subscribe<MouseEvent>([](MouseEvent& e){
        cout << "mouse event dispatched.\n";
        return true;
    });

    dispatcher.Dispatch(e);
    dispatcher.Dispatch(m);

    return 0;
}