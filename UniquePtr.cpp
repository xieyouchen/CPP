#include <bits/stdc++.h>

using namespace std;

class Obj {
public:
    explicit Obj(string name): Name(name) {}
private:
    string Name;
};

template<typename T>
class UniquePtr {
public:
    UniquePtr(T* ptr): Ptr(ptr) {
        cout << "constructed.\n";
    }
    UniquePtr(const UniquePtr& other)  = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other): Ptr(other.Ptr) {
        other.Ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) {
        if(this == &other) return *this;

        delete Ptr;
        Ptr = other.Ptr;
        other.Ptr = nullptr;
        
        return *this;
    }

    T* Release() {
        T* newPtr = Ptr;
        Ptr = nullptr;
        return newPtr;
    }

    void Reset(T* ptr = nullptr) {
        delete Ptr;
        Ptr = ptr;
    }

private:
    T* Ptr;
};

int main() {
    UniquePtr<Obj> ptr = new Obj("hello");
    UniquePtr<Obj> ptr_move = new Obj("no");
    ptr = move(ptr_move);
    
    return 0;
}