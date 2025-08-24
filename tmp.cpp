#include <bits/stdc++.h>

using namespace std;

class Observer {
public:
    Observer(const string& name): Name(name) {}

    bool Update(const string& message) {
        cout << Name << " get " << message << endl;
    }
private:
    string Name;
};

class Subject {
public:
    Subject() = default;

    bool Subscribe(Observer* observer) {
        m_Observers.emplace_back(observer);
    }

    void Notify(const string& message) {
        for(const auto& o: m_Observers) {
            o->Update(message);
        }
    }
private:
    vector<Observer*> m_Observers;
};

class Strategy {
public:
    virtual void Move() = 0;
};

class Run: public Strategy {
public:
    virtual void Move() override {
        cout << "Run.\n";
    }
};

class Walk: public Strategy {
public:
    virtual void Move() override {
        cout << "Walk.\n";
    }
};

class Player {
public:
    Player(): m_Strategy(new Walk()) {}

    void Move() {
        m_Strategy->Move();
    }

    bool SetStrategy(Strategy* strategy) {
        m_Strategy = strategy;
    }

private:
    Strategy* m_Strategy;
};

enum class AnimalType {
    None,
    Dog,
    Cat
};

class Animal {
public:
    virtual void speak() = 0;
};

class Dog: public Animal {
public:
    virtual void speak() override {
        cout << "Woof.\n";
    }
};

class Cat: public Animal {
public:
    virtual void speak() override {
        cout << "Mewo.\n";
    }
};

class Factory {
public:
    static Animal* Create(AnimalType type) {
        switch(type) {
            case AnimalType::Dog: {
                return new Dog();
            }
            case AnimalType::Cat: {
                return new Cat();
            }
        }
    }
};

int main() {
    Observer o1("O1"s);
    Observer o2("O2"s);

    Subject sub;
    sub.Subscribe(&o1);
    sub.Subscribe(&o2);

    sub.Notify("Hello"s);

    Player player;
    player.Move();

    player.SetStrategy(new Run());

    player.Move();

    Animal* dog = Factory::Create(AnimalType::Dog);
    Animal* cat = Factory::Create(AnimalType::Cat);
    dog->speak();
    cat->speak();

    return 0;
}