#include <bits/stdc++.h>

using namespace std;

enum class AnimalType {
    None,
    Dog,
    Cat
};

class Animal {
public:
    virtual void Speak() const = 0;
};

class Cat: public Animal {
public:
    virtual void Speak() const override {
        cout << "Meow.\n";
    }
};

class Dog: public Animal {
public:
    virtual void Speak() const override {
        cout << "Woof.\n";
    }
};

class AnimalFactory {
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
    Animal* dog = AnimalFactory::Create(AnimalType::Dog);
    Animal* cat = AnimalFactory::Create(AnimalType::Cat);

    dog->Speak();
    cat->Speak();

    delete dog;
    delete cat;

    return 0;
}