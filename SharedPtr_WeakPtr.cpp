#include <iostream>

template<typename T>
struct ControlBlock {
    int shared_count = 1;   // 一开始1个shared_ptr
    int weak_count = 0;     // 没有weak_ptr
    T* ptr = nullptr;       // 指向资源（A或B）

    ControlBlock(T* p) : ptr(p) {}
};

template<typename T>
struct MySharedPtr {
    ControlBlock<T>* ctrl = nullptr;

    MySharedPtr() = default;
    MySharedPtr(T* p) {
        ctrl = new ControlBlock<T>(p);
    }

    MySharedPtr(const MySharedPtr& other) : ctrl(other.ctrl) {
        if (ctrl) ++ctrl->shared_count;
        std::cout << "SharedPtr Constructor\n";
    }
    MySharedPtr& operator=(const MySharedPtr& other) {
        ctrl = other.ctrl;
        std::cout << "assignment.\n";
        return *this;
    }

    ~MySharedPtr() {
        if (ctrl && --ctrl->shared_count == 0) {
            delete ctrl->ptr; // 资源释放（A或B）
            if (ctrl->weak_count == 0)
                delete ctrl; // 控制块也释放
        }
    }

    T* operator->() const { return ctrl->ptr; }
};

template<typename T>
struct MyWeakPtr {
    ControlBlock<T>* ctrl = nullptr;

    MyWeakPtr() {}

    MyWeakPtr(const MySharedPtr<T>& sp) : ctrl(sp.ctrl) {
        if (ctrl) ++ctrl->weak_count;
    }

    ~MyWeakPtr() {
        if (ctrl && --ctrl->weak_count == 0 && ctrl->shared_count == 0) {
            delete ctrl;
        }
    }

    MySharedPtr<T> lock() const {
        if (ctrl && ctrl->shared_count > 0) {
            MySharedPtr<T> sp;
            sp.ctrl = ctrl;
            if(ctrl) {
                ++ctrl->shared_count;
            }
            return sp;
            // return MySharedPtr<T>(*this); // 升级为shared_ptr
        }
        return MySharedPtr<T>(nullptr); // 返回空指针
    }
};

struct B; // 前向声明

struct A {
    MySharedPtr<B> bptr; // A 拥有 B

    ~A() { std::cout << "A析构\n"; }
    void hello() { std::cout << "Hello from A\n"; }
};

struct B {
    MyWeakPtr<A> aptr; // B 弱引用 A

    ~B() { std::cout << "B析构\n"; }

    void tryCallA() {
        auto sa = aptr.lock();
        if (sa.ctrl && sa.ctrl->ptr) {
            sa->hello();
        } else {
            std::cout << "A已经被释放\n";
        }
    }
};

int main() {
    MySharedPtr<A> a(new A());
    MySharedPtr<B> b(new B());

    a->bptr = b;      // A持有B
    b->aptr = a;      // B弱引用A

    b->tryCallA();    // 正常调用

    a = MySharedPtr<A>(nullptr); // A销毁
    b->tryCallA();    // 无法调用A
}
