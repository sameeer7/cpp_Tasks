#include <iostream>
#include <map>
#include <string>

// Theme class to represent a display theme/skin
class Theme {
public:
    // Constructor to initialize the theme's attributes
    Theme(std::string backgroundColor, std::string fontColor, int fontSize, std::string iconStyle)
        : backgroundColor(backgroundColor), fontColor(fontColor), fontSize(fontSize), iconStyle(iconStyle) {}

    // Method to display the theme details (preview)
    void display() const {
        std::cout << "Background Color: " << backgroundColor << std::endl;
        std::cout << "Font Color: " << fontColor << std::endl;
        std::cout << "Font Size: " << fontSize << std::endl;
        std::cout << "Icon Style: " << iconStyle << std::endl;
    }

    // Method to apply the theme (in this case, just display its details)
    void apply() const {
        std::cout << "\nApplying Theme..." << std::endl;
        display();  // Show the details of the selected theme
    }

private:
    std::string backgroundColor;
    std::string fontColor;
    int fontSize;
    std::string iconStyle;
};

// Function to display available themes to the user
void showAvailableThemes(const std::map<std::string, Theme>& themes) {
    std::cout << "\nAvailable Themes:" << std::endl;
    for (const auto& theme : themes) {
        std::cout << "- " << theme.first << std::endl;  // Display theme names
    }
}

// Function to switch themes based on user input
void switchTheme(std::map<std::string, Theme>& themes) {
    std::string selectedTheme;
    std::cout << "Enter the theme name to apply: ";
    std::cin >> selectedTheme;

    // Check if the selected theme exists in the map
    auto it = themes.find(selectedTheme);
    if (it != themes.end()) {
        std::cout << "\nYou selected the " << selectedTheme << " Theme!" << std::endl;
        it->second.apply();  // Apply and display the selected theme
    } else {
        std::cout << "\nInvalid theme name. Please try again." << std::endl;
    }
}

int main() {
    // Create a map to store multiple themes
    std::map<std::string, Theme> themes;

    // Adding themes to the map
    themes["Classic"] = Theme("White", "Black", 12, "Simple Icons");
    themes["Sport"] = Theme("Red", "White", 14, "Bold Icons");
    themes["Eco"] = Theme("Green", "Dark Green", 10, "Nature Icons");

    // Display available themes
    showAvailableThemes(themes);

    // Allow the user to switch themes
    switchTheme(themes);

    return 0;
}

