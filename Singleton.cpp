#include <bits/stdc++.h>

using namespace std;

class Singleton {
private:
    static Singleton* m_Instance;
    int m_Count;
    Singleton(){
        cout << "Singleton is created.\n";
    }

public:
    inline static Singleton* GetInstance() {
        if(!m_Instance) 
            m_Instance = new Singleton();

        return m_Instance;
    }

    void Print() {
        cout << m_Count++ << endl;
    }

};

Singleton* Singleton::m_Instance;


int main() {

    Singleton* singleton = Singleton::GetInstance();
    singleton->Print();

    Singleton* singleton2 = Singleton::GetInstance();
    singleton2->Print();

    cout << (singleton2 == singleton) << endl;

    return 0;
}