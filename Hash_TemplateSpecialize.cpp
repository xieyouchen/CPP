#include <bits/stdc++.h>
using namespace std;

class Obj {
public:
    explicit Obj(string s): Name(s) {}
    string Name;

    bool operator==(const Obj& other) const {
        return Name==other.Name;
    }

    inline friend ostream& operator<<(ostream& os, const Obj& obj) {
        return os << obj.Name;
    }
};

namespace std {
    template<>
    struct hash<Obj> {
        size_t operator()(const Obj& o) const {
            return hash<string>()(o.Name);
        }
    };
}

int main() {
    unordered_map<Obj, int> m;
    m.emplace("hello"s, 2);
    m.emplace("world"s, 12);
    for(const auto& [key, value]: m) {
        cout << key << " " << value << endl;
    }

    vector<Obj> v;
    v.emplace_back("vector yes"s);
    cout << v[0] << endl;

    // v.push_back("push no"s);
    // cout << v[1] << endl;

    return 0;
}