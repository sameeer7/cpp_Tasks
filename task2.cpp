#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

// VehicleData class to store vehicle parameters
class VehicleData {
public:
    // Constructor to initialize the vehicle data
    VehicleData() : speed(0), fuel(100), temperature(70) {}

    // Random number generator to simulate real-time data
    void updateData() {
        // Speed between 0 and 200 km/h
        speed = randGen(0, 200);
        // Fuel level between 0 and 100%
        fuel = randGen(0, 100);
        // Temperature between 60 and 120°C
        temperature = randGen(60, 120);
    }

    // Getter methods for vehicle data
    int getSpeed() const { return speed; }
    int getFuel() const { return fuel; }
    int getTemperature() const { return temperature; }

private:
    // Random number generator for data simulation
    int randGen(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    int speed;
    int fuel;
    int temperature;
    std::default_random_engine rng{std::random_device{}()};  // Random engine
};

// Display class to show the vehicle data on console
class Display {
public:
    Display(VehicleData& vehicleData) : vehicleData(vehicleData) {}

    // Method to display the data
    void showData() {
        // Clear screen for better visualization in the console
        std::cout << "\033[2J\033[1;1H";  // ANSI escape code for clearing the console

        // Display speed, fuel, and temperature
        std::cout << "Speed: " << vehicleData.getSpeed() << " km/h\n";
        std::cout << "Fuel: " << vehicleData.getFuel() << "%\n";
        std::cout << "Temperature: " << vehicleData.getTemperature() << "°C\n";

        // Display warnings
        if (vehicleData.getFuel() < 10) {
            std::cout << "Warning: Fuel level is below 10%!\n";
        }
        if (vehicleData.getTemperature() > 100) {
            std::cout << "Warning: Engine temperature exceeds 100°C!\n";
        }

        std::cout << "\n";
    }

private:
    VehicleData& vehicleData;
};

// Function to update vehicle data every second in a separate thread
void updateDataThread(VehicleData& vehicleData) {
    while (true) {
        vehicleData.updateData();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Function to display data every second in a separate thread
void displayDataThread(Display& display) {
    while (true) {
        display.showData();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // Create a VehicleData object
    VehicleData vehicleData;
    // Create a Display object passing vehicleData
    Display display(vehicleData);

    // Start the update data and display threads
    std::thread updateThread(updateDataThread, std::ref(vehicleData));
    std::thread displayThread(displayDataThread, std::ref(display));

    // Join the threads to the main thread so the program doesn't exit immediately
    updateThread.join();
    displayThread.join();

    return 0;
}
