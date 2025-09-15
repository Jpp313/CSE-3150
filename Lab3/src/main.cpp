#include <iostream>
#include <string>
#include "logger.h"
using std::cout; using std::cin; using std::endl;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./logger <capacity>" << endl;
        return 1;
    }
    const int capacity = std::stoi(argv[1]);
    if (capacity <= 0) { cout << "Capacity must be > 0\n"; return 1; }

    std::string* labels = new std::string[capacity];
    double* values = new double[capacity];
    int size = 0;

    bool running = true;
    while (running) {
        cout << "\n1) add  2) update  3) print  4) compute  5) exit\n> ";
        int choice; if (!(cin >> choice)) return 0;
        try {
            switch (choice) {
                case 1: {
                    std::string L; double V;
                    cout << "label value: ";
                    cin >> L >> V;
                    addReading(L, V, labels, values, size, capacity);
                    break;
                }
                case 2: {
                    int idx; double nv;
                    cout << "index new_value: ";
                    cin >> idx >> nv;
                    if (idx < 0 || idx >= size) throw std::string("Bad index");
                    updateValue(&values[idx], nv);
                    break;
                }
                case 3: {
                    for (int i = 0; i < size; ++i)
                        printReading(labels[i], values[i]);
                    break;
                }
                case 4: {
                    cout << "1=avg 2=min 3=max: ";
                    int m; cin >> m;
                    double ans = 0.0;
                    if (m == 1) ans = average(values, size);
                    else if (m == 2) ans = minValue(values, size);
                    else if (m == 3) ans = maxValue(values, size);
                    else { cout << "Unknown op\n"; break; }
                    cout << "result=" << ans
                         << " rounded=" << static_cast<int>(ans) << endl;
                    break;
                }
                case 5: running = false; break;
                default: cout << "Unknown choice\n"; break;
            }
        } catch (const std::string& msg) {
            cout << "Error: " << msg << endl;
        }
    }
    delete[] labels;
    delete[] values;
    
    // TODO: Free memory!
    return 0;
}
