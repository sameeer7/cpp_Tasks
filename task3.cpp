#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>

// Event class to represent a touchscreen input event
class Event {
public:
    enum EventType { TAP, SWIPE };
    
    Event(EventType type, int x, int y, time_t timestamp) 
        : eventType(type), x(x), y(y), timestamp(timestamp) {}
    
    EventType eventType;
    int x, y;
    time_t timestamp;
};

// Function to display the event details
void handleEvent(const Event& event) {
    // Convert timestamp to readable format
    char buffer[80];
    struct tm* timeinfo;
    timeinfo = localtime(&event.timestamp);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Handle the event
    if (event.eventType == Event::TAP) {
        std::cout << "[" << buffer << "] TAP at position (" << event.x << ", " << event.y << ")\n";
    }
    else if (event.eventType == Event::SWIPE) {
        std::string direction;
        if (event.x > 0) {
            direction = "RIGHT";
        } else if (event.x < 0) {
            direction = "LEFT";
        } else if (event.y > 0) {
            direction = "UP";
        } else if (event.y < 0) {
            direction = "DOWN";
        }
        std::cout << "[" << buffer << "] SWIPE in direction: " << direction << "\n";
    }
}

// Function to simulate random event generation
void simulateEvents(std::queue<Event>& eventQueue, int numEvents) {
    srand(time(0)); // Seed for random number generation
    
    for (int i = 0; i < numEvents; ++i) {
        int x = rand() % 500 - 250; // Random x between -250 and 250
        int y = rand() % 500 - 250; // Random y between -250 and 250
        time_t timestamp = time(0); // Current time as timestamp
        Event::EventType type = (rand() % 2 == 0) ? Event::TAP : Event::SWIPE; // Randomly choose between TAP and SWIPE
        
        Event newEvent(type, x, y, timestamp);
        eventQueue.push(newEvent);
    }
}

int main() {
    std::queue<Event> eventQueue;

    // Simulate 10 random events
    simulateEvents(eventQueue, 10);
    
    // Process events in the queue
    while (!eventQueue.empty()) {
        Event currentEvent = eventQueue.front();
        eventQueue.pop();
        
        // Handle the current event
        handleEvent(currentEvent);
    }

    return 0;
}

