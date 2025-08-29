#include <bits/stdc++.h>
using namespace std;

class Observer {
public:
    Observer(const char* name): m_Name(name) {}
    void Update(const char* message) {
        cout << "Observer" << m_Name << " get message: " << message << endl; 
    }
private:
    string m_Name;
};

class Subject {
public:
    void Subscribe(Observer* observer) {
        m_Observers.push_back(observer);
    }

    void Notify(const char* message) {
        for(const auto& o: m_Observers) {
            o->Update(message);
        }
    }

    bool Unsubscribe(Observer* observer) {
        auto it = find(m_Observers.begin(), m_Observers.end(), observer);
        if(it == m_Observers.end()) return false;

        m_Observers.erase(it);
        return true;
    }

private:
    vector<Observer*> m_Observers;
};

int main() {
    Observer o1("O1");
    Observer o2("O2");

    Subject subject;
    subject.Subscribe(&o1);
    subject.Subscribe(&o2);

    subject.Notify("Hello.");

    subject.Unsubscribe(&o1);
    subject.Notify("Hello.");


    return 0;
}