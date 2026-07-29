#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <ctime>

using namespace std;

enum class Light { RED, YELLOW, GREEN };

struct TrafficState {
    atomic<Light> northSouth{Light::GREEN};
    atomic<Light> eastWest{Light::RED};
};

atomic<bool> stop(false);
const int GREEN_TIME = 5;
const int YELLOW_TIME = 2;
const char* toString(Light l){
    switch(l){
        case Light::RED: return "RED";
        case Light::YELLOW: return "YELLOW";
        case Light::GREEN: return "GREEN";
    }
    return "";
}
void logMessage(const std::string& message) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    cout << "["
         << localTime->tm_hour << ":"
         << localTime->tm_min << ":"
         << localTime->tm_sec << "] "
         << message << endl;
}

void controller(TrafficState &state){
    while(!stop){
// North-South GREEN
state.northSouth = Light::GREEN;
state.eastWest = Light::RED;
logMessage("Controller: North-South GREEN");

for(int i = GREEN_TIME; i > 0 && !stop; --i)
    this_thread::sleep_for(chrono::seconds(1));

// North-South YELLOW
state.northSouth = Light::YELLOW;
logMessage("Controller: North-South YELLOW");

for(int i = YELLOW_TIME; i > 0 && !stop; --i)
    this_thread::sleep_for(chrono::seconds(1));

// East-West GREEN
state.northSouth = Light::RED;
state.eastWest = Light::GREEN;
logMessage("Controller: East-West GREEN");

for(int i = GREEN_TIME; i > 0 && !stop; --i)
    this_thread::sleep_for(chrono::seconds(1));

// East-West YELLOW
state.eastWest = Light::YELLOW;
logMessage("Controller: East-West YELLOW");

for(int i = YELLOW_TIME; i > 0 && !stop; --i)
    this_thread::sleep_for(chrono::seconds(1));

state.eastWest = Light::RED;
    }
}
void monitor(TrafficState &state)
{
    while(!stop)
    {
        Light ns = state.northSouth.load();
        Light ew = state.eastWest.load();

        logMessage(
            "Monitor -> North-South: " +
            string(toString(ns)) +
            " | East-West: " +
            string(toString(ew))
        );

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(){
    TrafficState state;
    thread t1(controller, ref(state));
    thread t2(monitor, ref(state));

    cout<<"Press Enter to stop...\n";
    cin.get();

    stop = true;
    t1.join();
    t2.join();
    
    cout << "Program exited safely hehe :)\n";
    return 0;
}
