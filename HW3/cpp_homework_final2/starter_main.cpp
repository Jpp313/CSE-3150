

#include <iostream>
#include <cstring>
#include <limits>



void addStudent(const char* name, double gpa, char** names, double gpas[], int& size, int capacity) {
    if (size >= capacity) throw "List full";
    size_t len = std::strlen(name);
    char* copy = new char[len + 1];
    std::strcpy(copy, name);
    names[size] = copy;
    gpas[size] = gpa;
    ++size;
}

void updateGPA(double gpas[], int size, int idx, double newGpa) {
    if (idx < 0 || idx >= size) throw "Invalid index";
    gpas[idx] = newGpa;
}

void printStudent(const char* name, double gpa) {
    std::cout << "Name: " << name << "\n";
    std::cout << "GPA: " << gpa << "\n";
}

double averageGPA(const double gpas[], int size) {
    if (size == 0) throw "No students";
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += gpas[i];
    return sum / size;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <capacity>\n";
        return 1;
    }

    int capacity = std::stoi(argv[1]);
    if (capacity <= 0) capacity = 10;

    // dynamic arrays
    char** names = new char*[capacity];
    double* gpas = new double[capacity];
    int size = 0;

    int choice = 0;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                char buffer[256];
                double gpa;
                std::cout << "Enter name: ";
                std::cin.getline(buffer, sizeof(buffer));
                if (std::strlen(buffer) == 0) {
                    std::cout << "Name cannot be empty\n";
                    break;
                }
                std::cout << "Enter GPA: ";
                if (!(std::cin >> gpa)) {
                    std::cout << "Invalid GPA\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                try {
                    addStudent(buffer, gpa, names, gpas, size, capacity);
                } catch (const char* msg) {
                    std::cout << msg << "\n";
                }
                break;
            }
            case 2: {
                int idx;
                double newGpa;
                std::cout << "Enter student index: ";
                if (!(std::cin >> idx)) {
                    std::cout << "Invalid index\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Enter new GPA: ";
                if (!(std::cin >> newGpa)) {
                    std::cout << "Invalid GPA\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                try {
                    updateGPA(gpas, size, idx, newGpa);
                } catch (const char* msg) {
                    std::cout << msg << "\n";
                }
                break;
            }
            case 3: {
                for (int i = 0; i < size; ++i) {
                    std::cout << i << ": ";
                    printStudent(names[i], gpas[i]);
                }
                break;
            }
            case 4: {
                try {
                    double avg = averageGPA(gpas, size);
                    std::cout << "Average GPA = " << avg << "\n";
                } catch (const char* msg) {
                    std::cout << msg << "\n";
                }
                break;
            }
            case 5: {
                std::cout << "Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice\n";
            }
        }
    } while (choice != 5);

   
    for (int i = 0; i < size; ++i) delete[] names[i];
    delete[] names;
    delete[] gpas;

    return 0;
}
