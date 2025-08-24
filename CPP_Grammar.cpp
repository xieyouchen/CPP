#include<bits/stdc++.h>
using namespace std;

void func(const string& s) {
    cout << s << endl;
}

template<typename T>
void func2(T&& t) {
    cout << t << endl;
}

int main() {
    string name = "hello";
    func2(move(name));
    func2(name);
    func(name);
    func(move(name));

    return 0;
}