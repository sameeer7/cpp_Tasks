#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <random>

// Define the Control struct
struct Control {
    int id;             // Unique ID
    std::string type;   // "button" or "slider"
    std::string state;  // "visible", "invisible", or "disabled"
};

// Function to print control list
void printControls(const std::vector<Control>& controls) {
    for (const auto& ctrl : controls) {
        std::cout << "ID: " << ctrl.id << ", Type: " << ctrl.type << ", State: " << ctrl.state << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Initialize a vector of controls with sample data
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "slider", "invisible"},
        {3, "button", "disabled"},
        {4, "slider", "visible"},
        {5, "slider", "disabled"},
        {6, "button", "visible"},
        {7, "slider", "invisible"},
        {8, "slider", "disabled"},
        {9, "button", "visible"},
        {10, "slider", "visible"}
    };

    // Step 1: Create a backup of the control list
    std::vector<Control> backupControls = controls;
    std::cout << "Backup Controls:\n";
    printControls(backupControls);

    // Step 2: Set all states to "disabled" temporarily
    std::fill(controls.begin(), controls.end(), Control{0, "", "disabled"});
    std::cout << "All states set to 'disabled':\n";
    printControls(controls);

    // Step 3: Generate random states for testing
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 2);
    const std::vector<std::string> states = {"visible", "invisible", "disabled"};
    
    std::generate(controls.begin(), controls.end(), [&]() {
        int randomIndex = distrib(gen);
        return Control{0, "", states[randomIndex]};
    });
    std::cout << "Randomly generated states:\n";
    printControls(controls);

    // Step 4: Use std::transform to change the state of all sliders to "invisible"
    std::transform(controls.begin(), controls.end(), controls.begin(), [](Control& ctrl) {
        if (ctrl.type == "slider") {
            ctrl.state = "invisible";
        }
        return ctrl;
    });
    std::cout << "All sliders set to 'invisible':\n";
    printControls(controls);

    // Step 5: Use std::replace to replace "disabled" with "enabled"
    std::replace_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "disabled";
    }, Control{0, "", "enabled"});
    std::cout << "All 'disabled' states replaced with 'enabled':\n";
    printControls(controls);

    // Step 6: Use std::remove_if to filter out invisible controls
    auto newEnd = std::remove_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    });
    controls.erase(newEnd, controls.end());
    std::cout << "Invisible controls removed:\n";
    printControls(controls);

    // Step 7: Reverse the control list for debugging
    std::reverse(controls.begin(), controls.end());
    std::cout << "Reversed control order:\n";
    printControls(controls);

    // Step 8: Partition controls into visible and non-visible
    auto partitionPoint = std::partition(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });
    std::cout << "Controls partitioned into visible and non-visible:\n";
    printControls(controls);

    return 0;
}
