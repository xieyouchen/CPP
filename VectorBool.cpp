#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<bool> v = {true, false, true, false};
    for(const auto& i: v) {
        cout << i << endl;
    }

    bool a = v[0];
    auto b = v[1];
    auto c = a;


    cout << "a, b 分别是" << a << " " << b << endl;

    a = 0;
    b = 1;

    cout << "a, b 分别是" << a << " " << b << endl;


    for(const auto& i: v) {
        cout << i << endl;
    }



    return 0;
}
