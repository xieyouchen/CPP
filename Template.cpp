#include <bits/stdc++.h>

using namespace std;

template<typename T>
void Print(T t) {
    cout << t << endl;
}

template<typename T, typename... Args> 
void Print(T t, Args... args) {
    cout << t << " ";
    Print((args)...);
}

int main() {
    float a = 324.123;
    Print(123, "hello", a);
    
    return 0;
}