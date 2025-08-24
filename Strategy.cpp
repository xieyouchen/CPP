#include <bits/stdc++.h>

using namespace std;


class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;

    virtual void Move() = 0;
};

class Run: public MoveStrategy {
public:
    virtual void Move() override {
        cout << "Run.\n";
    }
};

class Walk: public MoveStrategy {
public:
    virtual void Move() override {
        cout << "Walk.\n";
    }
};

class Player {
public:
    Player(MoveStrategy* move = new Walk()): m_Move(move) {}

    void SetStrategy(MoveStrategy* move) {
        m_Move = move;
    }

    void Move() {
        m_Move->Move();
    }
private:
    MoveStrategy* m_Move;
};

int main() {
    Player player;
    player.Move();

    player.SetStrategy(new Run());
    player.Move();

    return 0;
}