#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

int main() {
    // Step 1: Initialize containers
    std::vector<std::string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge", "Temperature"};
    std::set<std::string> staticWidgets = {"Logo", "WarningLights", "Clock"};

    // Step 2: Use iterators to print all dynamic widgets
    std::cout << "Dynamic Widgets:\n";
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) {
        std::cout << *it << "\n";
    }

    // Step 3: Use std::set::find to check if a specific widget is in the std::set
    std::cout << "\nChecking if 'WarningLights' exists in static widgets...\n";
    auto foundStatic = staticWidgets.find("WarningLights");
    if (foundStatic != staticWidgets.end()) {
        std::cout << "'WarningLights' found in static widgets.\n";
    } else {
        std::cout << "'WarningLights' NOT found in static widgets.\n";
    }

    // Step 4: Combine both containers into a new vector using std::copy
    std::vector<std::string> allWidgets;
    std::copy(dynamicWidgets.begin(), dynamicWidgets.end(), std::back_inserter(allWidgets));
    std::copy(staticWidgets.begin(), staticWidgets.end(), std::back_inserter(allWidgets));

    // Step 5: Use std::find to locate a specific widget in the combined container
    std::string widgetToFind = "Clock";
    std::cout << "\nSearching for '" << widgetToFind << "' in combined widgets...\n";
    auto foundWidget = std::find(allWidgets.begin(), allWidgets.end(), widgetToFind);
    if (foundWidget != allWidgets.end()) {
        std::cout << "'" << widgetToFind << "' found in combined widgets.\n";
    } else {
        std::cout << "'" << widgetToFind << "' NOT found in combined widgets.\n";
    }

    // Step 6: Output combined widget list
    std::cout << "\nAll Widgets (Combined):\n";
    for (const auto& widget : allWidgets) {
        std::cout << widget << "\n";
    }

    return 0;
}
