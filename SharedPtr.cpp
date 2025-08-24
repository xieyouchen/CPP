#include<bits/stdc++.h>

using namespace std;

template<typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr): Ptr(ptr), Count(new int(1)) {}
    SharedPtr(const SharedPtr& other) : Ptr(other.Ptr), Count(other.Count) {
        (*other.Count)++;
    }
    SharedPtr& operator=(const SharedPtr& other) {
        if(this == &other) return *this;

        if(Ptr && --(*Count) == 0) {
            delete Ptr;
            delete Count;
        }
        Ptr = other.Ptr;
        Count = other.Count;
        (*Count)++;
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) {
        if(this == &other) return *this;

        if(Ptr && --(*Count) == 0) {
            delete Ptr;
            delete Count;
        }
        Ptr = other.Ptr;
        Count = other.Count;
        other.Ptr = nullptr;
        other.Count = nullptr;

        return *this;
    }


    T& operator*() const {
        return *Ptr;
    }

    ~SharedPtr() {
        if(Ptr && --(*Count) == 0) {
            delete Ptr;
            Ptr = nullptr;
            delete Count;
            Count = nullptr;
        }
    }
    T* Ptr;
    int* Count;
};

int main() {
    SharedPtr<int> tmp(new int(10));
    cout << *tmp << endl;

    SharedPtr<int> tmp2 = tmp;
    cout << *(tmp2.Count) << endl;

    SharedPtr<int> tmp3(new int(20));
    tmp3 = move(tmp);
    cout << *(tmp3.Count) << " " << *tmp3.Ptr << endl;

    return 0;
}