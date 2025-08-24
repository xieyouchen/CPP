#include <bits/stdc++.h>

using namespace std;

class Base {
public:
    virtual void speak() {
        cout << "Base speak.\n";
    }
};

class Derived: public Base {
public:
    virtual void speak() {
        cout << "Derived speak.\n";
    }

    void Derived_speak() {
        cout << "Derived another speak.\n";
    }
};


int main() {
    Base* derived = new Derived();
    derived->speak();
    static_cast<Derived*>(derived)->Derived_speak();

    return 0;
}