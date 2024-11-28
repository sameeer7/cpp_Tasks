#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Singleton: HMI System class
class HMISystem {
private:
    static HMISystem* instance;
    std::string currentMode;
    std::vector<ModeObserver*> observers;

    // Private constructor to prevent direct instantiation
    HMISystem() : currentMode("Day") {}

public:
    // Method to get the single instance of HMISystem
    static HMISystem* getInstance() {
        if (instance == nullptr) {
            instance = new HMISystem();
        }
        return instance;
    }

    // Get the current mode
    std::string getCurrentMode() {
        return currentMode;
    }

    // Add an observer (widget)
    void addObserver(ModeObserver* observer) {
        observers.push_back(observer);
    }

    // Change mode and notify observers
    void changeMode(const std::string& mode) {
        currentMode = mode;
        std::cout << "Mode changed to: " << mode << std::endl;
        notifyObservers();
    }

    void notifyObservers() {
        for (ModeObserver* observer : observers) {
            observer->update(currentMode);
        }
    }

    // Destructor to clean up if needed
    ~HMISystem() {
        delete instance;
    }
};

// Initialize the static instance pointer
HMISystem* HMISystem::instance = nullptr;

// Observer Interface: ModeObserver
class ModeObserver {
public:
    virtual void update(const std::string& mode) = 0;
    virtual ~ModeObserver() {}
};

// Concrete Observers: Button and Slider
class Button : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Button: Adjusting for Night mode" << std::endl;
        } else {
            std::cout << "Button: Adjusting for Day mode" << std::endl;
        }
    }
};

class Slider : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Slider: Adjusting for Night mode" << std::endl;
        } else {
            std::cout << "Slider: Adjusting for Day mode" << std::endl;
        }
    }
};

// Abstract Product: Control
class Control {
public:
    virtual void render() = 0;
    virtual ~Control() {}
};

// Concrete Products: Button and Slider
class ButtonControl : public Control {
public:
    void render() override {
        std::cout << "Rendering Button" << std::endl;
    }
};

class SliderControl : public Control {
public:
    void render() override {
        std::cout << "Rendering Slider" << std::endl;
    }
};

// Factory Class: ControlFactory
class ControlFactory {
public:
    static std::unique_ptr<Control> createControl(const std::string& type) {
        if (type == "Button") {
            return std::make_unique<ButtonControl>();
        } else if (type == "Slider") {
            return std::make_unique<SliderControl>();
        } else {
            return nullptr;
        }
    }
};

// Strategy Interface: RenderStrategy
class RenderStrategy {
public:
    virtual void render() = 0;
    virtual ~RenderStrategy() {}
};

// Concrete Strategy 1: 2D Rendering
class Render2D : public RenderStrategy {
public:
    void render() override {
        std::cout << "Rendering in 2D" << std::endl;
    }
};

// Concrete Strategy 2: 3D Rendering
class Render3D : public RenderStrategy {
public:
    void render() override {
        std::cout << "Rendering in 3D" << std::endl;
    }
};

// Context: WidgetRenderer
class WidgetRenderer {
private:
    std::unique_ptr<RenderStrategy> renderStrategy;

public:
    WidgetRenderer(std::unique_ptr<RenderStrategy> strategy) : renderStrategy(std::move(strategy)) {}

    void setRenderStrategy(std::unique_ptr<RenderStrategy> strategy) {
        renderStrategy = std::move(strategy);
    }

    void renderWidget() {
        renderStrategy->render();
    }
};

// Main Function to demonstrate the usage of patterns
int main() {
    // Singleton Pattern
    HMISystem* system = HMISystem::getInstance();
    std::cout << "Current Mode: " << system->getCurrentMode() << std::endl;

    // Factory Pattern
    auto button = ControlFactory::createControl("Button");
    button->render();

    auto slider = ControlFactory::createControl("Slider");
    slider->render();

    // Observer Pattern
    Button buttonWidget;
    Slider sliderWidget;

    system->addObserver(&buttonWidget);
    system->addObserver(&sliderWidget);

    // Change the mode and notify observers
    system->changeMode("Night");
    system->changeMode("Day");

    // Strategy Pattern
    WidgetRenderer renderer(std::make_unique<Render2D>());
    renderer.renderWidget();  // Using 2D rendering

    renderer.setRenderStrategy(std::make_unique<Render3D>());
    renderer.renderWidget();  // Switching to 3D rendering

    return 0;
}
