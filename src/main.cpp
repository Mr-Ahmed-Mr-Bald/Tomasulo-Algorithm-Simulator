#include "core/app.h"
#include <exception>
#include <iostream>

int main() {
    try {
        App app;
        app.run();
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
}
