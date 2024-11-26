#include <iostream>
#include <vector>
#include <string>
#include <memory>

// MenuItem class represents a single menu item
class MenuItem {
public:
    std::string name;
    std::vector<std::shared_ptr<MenuItem>> subMenuItems;

    MenuItem(const std::string &name) : name(name) {}

    void addSubMenu(const std::shared_ptr<MenuItem>& subMenuItem) {
        subMenuItems.push_back(subMenuItem);
    }

    void displayMenu(int level) const {
        // Display the menu item with indentation based on level
        for (int i = 0; i < level; ++i) {
            std::cout << "  "; // Indentation for submenus
        }
        std::cout << name << std::endl;

        // Recursively display submenus
        for (const auto& subItem : subMenuItems) {
            subItem->displayMenu(level + 1);
        }
    }
};

// MenuNavigator handles navigation through the menu
class MenuNavigator {
private:
    std::shared_ptr<MenuItem> currentMenu;
    std::shared_ptr<MenuItem> rootMenu;

public:
    MenuNavigator(const std::shared_ptr<MenuItem>& root) : rootMenu(root), currentMenu(root) {}

    void displayCurrentMenu() const {
        currentMenu->displayMenu(0);
    }

    void navigateDown(int option) {
        if (option >= 0 && option < currentMenu->subMenuItems.size()) {
            currentMenu = currentMenu->subMenuItems[option];
        } else {
            std::cout << "Invalid option!" << std::endl;
        }
    }

    void navigateUp() {
        // Find the parent menu of the current menu
        if (currentMenu == rootMenu) {
            std::cout << "Already at the root menu!" << std::endl;
            return;
        }

        // Search for the parent menu
        for (const auto& item : rootMenu->subMenuItems) {
            searchParent(item, currentMenu);
        }
    }

    void backToRoot() {
        currentMenu = rootMenu;
    }

    void searchParent(const std::shared_ptr<MenuItem>& parent, const std::shared_ptr<MenuItem>& target) {
        for (const auto& subItem : parent->subMenuItems) {
            if (subItem == target) {
                currentMenu = parent;
                return;
            }
            searchParent(subItem, target);
        }
    }

    bool navigateEnter() {
        // If the current menu has submenus, we can navigate down
        if (!currentMenu->subMenuItems.empty()) {
            return true;
        }
        return false;
    }
};

int main() {
    // Build the menu structure
    auto mainMenu = std::make_shared<MenuItem>("Main Menu");
    auto settingsMenu = std::make_shared<MenuItem>("Settings");
    auto displaySettings = std::make_shared<MenuItem>("Display Settings");
    auto audioSettings = std::make_shared<MenuItem>("Audio Settings");
    auto mediaMenu = std::make_shared<MenuItem>("Media");
    auto radioMenu = std::make_shared<MenuItem>("Radio");
    auto bluetoothAudio = std::make_shared<MenuItem>("Bluetooth Audio");

    // Build the tree (hierarchy)
    settingsMenu->addSubMenu(displaySettings);
    settingsMenu->addSubMenu(audioSettings);
    mediaMenu->addSubMenu(radioMenu);
    mediaMenu->addSubMenu(bluetoothAudio);
    mainMenu->addSubMenu(settingsMenu);
    mainMenu->addSubMenu(mediaMenu);

    // Create the menu navigator with the root menu (mainMenu)
    MenuNavigator navigator(mainMenu);

    int choice = 0;
    while (true) {
        std::cout << "\nCurrent Menu: \n";
        navigator.displayCurrentMenu();

        std::cout << "\nEnter your choice:\n";
        std::cout << "1. Navigate Down\n";
        std::cout << "2. Navigate Up\n";
        std::cout << "3. Enter (Go Deeper into Submenu)\n";
        std::cout << "4. Back to Root\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int subMenuChoice;
            std::cout << "Enter submenu option number: ";
            std::cin >> subMenuChoice;
            navigator.navigateDown(subMenuChoice);
        } else if (choice == 2) {
            navigator.navigateUp();
        } else if (choice == 3) {
            if (navigator.navigateEnter()) {
                std::cout << "Entering submenu...\n";
            } else {
                std::cout << "No submenus available!\n";
            }
        } else if (choice == 4) {
            navigator.backToRoot();
        } else if (choice == 0) {
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
