#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// Define the Control struct
struct Control {
    int id;             // Unique ID
    std::string type;   // "button" or "slider"
    std::string state;  // "visible", "invisible", or "disabled"

    // Define how to compare controls by ID
    bool operator<(const Control& other) const {
        return id < other.id;
    }
};

// Function to print the control list
void printControls(const std::vector<Control>& controls) {
    for (const auto& ctrl : controls) {
        std::cout << "ID: " << ctrl.id << ", Type: " << ctrl.type << ", State: " << ctrl.state << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Initialize two vectors of controls
    std::vector<Control> controls1 = {
        {1, "button", "visible"},
        {5, "slider", "disabled"},
        {3, "button", "invisible"},
        {2, "slider", "visible"},
        {4, "button", "disabled"}
    };

    std::vector<Control> controls2 = {
        {6, "slider", "visible"},
        {7, "button", "invisible"},
        {8, "slider", "disabled"},
        {9, "button", "visible"}
    };

    // Step 1: Sort controls by ID using std::sort
    std::sort(controls1.begin(), controls1.end());
    std::sort(controls2.begin(), controls2.end());

    std::cout << "Sorted controls1 by ID:\n";
    printControls(controls1);

    std::cout << "Sorted controls2 by ID:\n";
    printControls(controls2);

    // Step 2: Use std::stable_sort to maintain relative order for controls with equal IDs
    std::vector<Control> controls3 = {
        {1, "button", "visible"},
        {2, "slider", "invisible"},
        {1, "slider", "disabled"},
        {3, "button", "visible"}
    };

    std::stable_sort(controls3.begin(), controls3.end());
    std::cout << "Controls sorted with stable_sort (relative order maintained for equal IDs):\n";
    printControls(controls3);

    // Step 3: Binary search for a control by ID using std::lower_bound and std::upper_bound
    int searchID = 3;
    auto lower = std::lower_bound(controls1.begin(), controls1.end(), Control{searchID, "", ""});
    auto upper = std::upper_bound(controls1.begin(), controls1.end(), Control{searchID, "", ""});

    std::cout << "Searching for ID " << searchID << " using binary search:\n";
    if (lower != controls1.end() && lower->id == searchID) {
        std::cout << "Found control with ID " << searchID << ": " << lower->type << ", " << lower->state << "\n";
    } else {
        std::cout << "Control with ID " << searchID << " not found.\n";
    }

    // Step 4: Merge two sorted lists using std::merge
    std::vector<Control> mergedControls(controls1.size() + controls2.size());
    std::merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), mergedControls.begin());
    std::cout << "Merged sorted controls from controls1 and controls2:\n";
    printControls(mergedControls);

    // Step 5: Use std::inplace_merge to merge two segments in the same list
    // We first sort both parts of the list and then use std::inplace_merge
    std::vector<Control> controlsToMerge = controls1;
    controlsToMerge.insert(controlsToMerge.end(), controls2.begin(), controls2.end());
    std::sort(controlsToMerge.begin(), controlsToMerge.begin() + controls1.size());
    std::sort(controlsToMerge.begin() + controls1.size(), controlsToMerge.end());

    std::inplace_merge(controlsToMerge.begin(), controlsToMerge.begin() + controls1.size(), controlsToMerge.end());
    std::cout << "Merged controls using std::inplace_merge:\n";
    printControls(controlsToMerge);

    // Step 6: Set operations: std::set_union and std::set_intersection
    std::vector<Control> unionControls(controls1.size() + controls2.size());
    std::vector<Control> intersectionControls(std::min(controls1.size(), controls2.size()));

    auto unionEnd = std::set_union(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), unionControls.begin());
    unionControls.resize(unionEnd - unionControls.begin());
    std::cout << "Union of controls1 and controls2 (unique controls):\n";
    printControls(unionControls);

    auto intersectionEnd = std::set_intersection(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), intersectionControls.begin());
    intersectionControls.resize(intersectionEnd - intersectionControls.begin());
    std::cout << "Intersection of controls1 and controls2 (common controls):\n";
    printControls(intersectionControls);

    return 0;
}
