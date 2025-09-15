#include <iostream>

void updateTemperature(int* tempPtr, int newTemp) {
    if (tempPtr != nullptr) {
        *tempPtr = newTemp;
    }
}

void printTemperature(const int& temp) {
    std::cout << "Temperature: " << temp << std::endl;
}

double averageTemperature(const int temps[], int size) {
    if (size == 0) {
        throw "No temperatures recorded";
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += temps[i];
    }
    return static_cast<double>(sum) / size;
}

int main() {
    int temps[5];
    int size = 0;
    int choice;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add temperature\n";
        std::cout << "2. Update temperature\n";
        std::cout << "3. Print all temperatures\n";
        std::cout << "4. Compute average\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                if (size < 5) {
                    int temp;
                    std::cout << "Enter temperature: ";
                    std::cin >> temp;
                    temps[size++] = temp;
                } else {
                    std::cout << "List full" << std::endl;
                }
                break;
            }
            case 2: {
                int index, newTemp;
                std::cout << "Enter index: ";
                std::cin >> index;
                if (index >= 0 && index < size) {
                    std::cout << "Enter new temperature: ";
                    std::cin >> newTemp;
                    updateTemperature(&temps[index], newTemp);
                } else {
                    std::cout << "Invalid index" << std::endl;
                }
                break;
            }
            case 3: {
                for (int i = 0; i < size; i++) {
                    printTemperature(temps[i]);
                }
                break;
            }
            case 4: {
                try {
                    double avg = averageTemperature(temps, size);
                    std::cout << "Average = " << avg 
                              << " (int=" << static_cast<int>(avg) << ")" 
                              << std::endl;
                } catch (const char* msg) {
                    std::cout << msg << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    } while (choice != 5);

    return 0;
}
