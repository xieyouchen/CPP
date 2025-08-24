#include<bits/stdc++.h>
using namespace std;

struct Timer {
    float timeLeft;
    float delay;
    bool repeat;
    function<bool()> callback;
};

class TimerManager {
public:
    TimerManager(): nextid(0) {}

    void addTimer(float deltaTime, bool repeat, function<bool()> callback) {
        m_Timers[nextid++] = {deltaTime, deltaTime, repeat, callback};
    }

    void OnUpdate(float time) {
        vector<int> toRemove;
        for(auto& [id, timer]: m_Timers) {
            timer.timeLeft -= time;
            if(timer.timeLeft <= 0) {
                timer.callback();

                if(timer.repeat) {
                    timer.timeLeft += timer.delay;
                }
                else {
                    toRemove.push_back(id);
                }
            }
        }

        for(const auto& id: toRemove) {
            m_Timers.erase(id);
        }
    }

private:
    unordered_map<int, Timer> m_Timers;
    int nextid;
};

int main() {
    TimerManager tm;
    tm.addTimer(1.0f, true, [](){
        cout << "Timer 1 fired (once after 1 sec)\n";
        return true;
    });

    tm.addTimer(0.5f, true, [](){
        cout << "Timer 2 fired (once after 0.5 sec)\n";
        return true;
    });

    float time = 0.0f;
    while(time < 2.0f) {
        tm.OnUpdate(0.1f);
        time += 0.1f;
    }

    return 0;
}