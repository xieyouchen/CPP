#include<bits/stdc++.h>

using namespace std;

class A{
public:
    explicit A(int i){}
};

int main() {
    vector<A> v;
    v.emplace_back(2);
    // v.emplace_back({2}); // 报错

    return 0;
}