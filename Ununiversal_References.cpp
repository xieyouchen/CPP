#include <bits/stdc++.h>

using namespace std;

void func(int&& num) {
    cout << num << "_rv" << endl;
}
void func(int& num) {
    cout << num << "_lv" << endl;
}

template<typename T>
void Print(T&& t) {
    func(forward<T>(t));
}

template<typename T, typename... Args>
void Print(T t, Args&&... args) {
    cout << t << " " << endl;
    Print(forward<Args>(args)...);
}

int main() {
    int a = 234;
    Print("hello"s, a);

    return 0;
}