#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Define the Control struct
struct Control {
    int id;             // Unique ID
    std::string type;   // "button" or "slider"
    std::string state;  // "visible", "invisible", or "disabled"
};

int main() {
    // Initialize a vector of controls with sample data
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "button", "invisible"},
        {3, "slider", "visible"},
        {4, "slider", "disabled"},
        {5, "button", "disabled"},
        {6, "slider", "visible"},
        {7, "button", "invisible"},
        {8, "slider", "disabled"},
        {9, "button", "visible"},
        {10, "slider", "visible"}
    };

    // 1. std::for_each: Iterate through all controls and print their details
    std::cout << "Control Details:\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) {
        std::cout << "ID: " << ctrl.id << ", Type: " << ctrl.type << ", State: " << ctrl.state << "\n";
    });

    // 2. std::find: Find a control with a specific ID (e.g., ID = 3)
    auto foundControl = std::find_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.id == 3;
    });
    if (foundControl != controls.end()) {
        std::cout << "\nFound Control with ID 3: Type: " << foundControl->type << ", State: " << foundControl->state << "\n";
    }

    // 3. std::find_if: Find the first control with the state "invisible"
    auto invisibleControl = std::find_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    });
    if (invisibleControl != controls.end()) {
        std::cout << "\nFirst Invisible Control: ID: " << invisibleControl->id << ", Type: " << invisibleControl->type << "\n";
    }

    // 4. std::adjacent_find: Check for consecutive controls with the same state
    auto adjacentControl = std::adjacent_find(controls.begin(), controls.end(), [](const Control& a, const Control& b) {
        return a.state == b.state;
    });
    if (adjacentControl != controls.end()) {
        std::cout << "\nAdjacent controls with the same state found. ID1: " << adjacentControl->id
                  << ", State: " << adjacentControl->state << "\n";
    }

    // 5. std::count: Count the number of visible controls
    int visibleCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });
    std::cout << "\nNumber of visible controls: " << visibleCount << "\n";

    // 6. std::count_if: Count sliders that are disabled
    int disabledSlidersCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.type == "slider" && ctrl.state == "disabled";
    });
    std::cout << "\nNumber of disabled sliders: " << disabledSlidersCount << "\n";

    // 7. std::equal: Compare two subranges of controls to check if they are identical
    std::vector<Control> controlsSubset = {controls[0], controls[1], controls[2]};
    bool areEqual = std::equal(controls.begin(), controls.begin() + 3, controlsSubset.begin());
    std::cout << "\nAre the first three controls equal to the subset? " << (areEqual ? "Yes" : "No") << "\n";

    return 0;
}
