#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>

class VehicleData {
public:
    int speed;           // Speed in km/h
    int fuelLevel;       // Fuel level in percentage (0-100%)
    int engineTemperature;  // Temperature in °C

    // Constructor to initialize with default values
    VehicleData() : speed(0), fuelLevel(100), engineTemperature(90) {}

    // Function to update the data with random values
    void updateData() {
        // Random number generators
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> speedDist(0, 180); // Speed between 0-180 km/h
        std::uniform_int_distribution<> fuelDist(0, 100);  // Fuel level between 0-100%
        std::uniform_int_distribution<> tempDist(70, 120);  // Engine temperature between 70-120°C

        // Update data
        speed = speedDist(gen);
        fuelLevel = fuelDist(gen);
        engineTemperature = tempDist(gen);
    }

    // Function to check if any parameter exceeds threshold
    void checkThresholds() const {
        if (engineTemperature > 100) {
            std::cout << "[WARNING] Engine Temperature High! (" << engineTemperature << "°C)\n";
        }
        if (fuelLevel < 10) {
            std::cout << "[WARNING] Low Fuel! (" << fuelLevel << "%)\n";
        }
    }
};

class Display {
private:
    VehicleData& vehicleData;  // Reference to VehicleData object
    std::mutex displayMutex;   // Mutex for thread safety

public:
    Display(VehicleData& data) : vehicleData(data) {}

    // Function to display the current data on the console
    void displayData() {
        std::lock_guard<std::mutex> lock(displayMutex);  // Ensure thread safety while displaying

        // Display the current values
        std::cout << "\rSpeed: " << vehicleData.speed << " km/h\t"
                  << "Fuel: " << vehicleData.fuelLevel << "%\t"
                  << "Temperature: " << vehicleData.engineTemperature << "°C";
        std::cout.flush();
    }
};

// Function to simulate updating vehicle data every second
void updateVehicleData(VehicleData& vehicleData) {
    while (true) {
        vehicleData.updateData();         // Update the data with random values
        vehicleData.checkThresholds();    // Check if any parameter exceeds the threshold
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 1 second
    }
}

// Function to display vehicle data in real-time
void displayVehicleData(Display& display) {
    while (true) {
        display.displayData();    // Display the data
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 1 second
    }
}

int main() {
    // Create VehicleData object to hold the vehicle data
    VehicleData vehicleData;

    // Create Display object to show the data
    Display display(vehicleData);

    // Start two threads: one for updating data, one for displaying it
    std::thread updateThread(updateVehicleData, std::ref(vehicleData));
    std::thread displayThread(displayVehicleData, std::ref(display));

    // Join the threads to the main thread
    updateThread.join();
    displayThread.join();

    return 0;
}
