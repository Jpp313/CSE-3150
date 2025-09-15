#include "logger.h"
#include <string>
#include <iostream>
// ======================= TODOs =======================

using std::string;

void addReading(const std::string& label, double value,
                std::string labels[], double values[],
                int& size, int capacity) {
    // throw "Full" if size == capacity, else insert and ++size
    if (size == capacity) {
        throw string("Full");
    } else {
        labels[size] = label;
        values[size] = value;
        size++;
    }
}

void updateValue(double* valuePtr, double newValue) {
    // write through pointer
    if (valuePtr != nullptr) {
        *valuePtr = newValue;
    }
}

void printReading(const std::string& label, const double& value) {
    // pretty-print one reading as "<label>: <value>"
    std::cout << label << ": " << value << std::endl;
}

double average(const double values[], int size) {
    // throw "Empty" if size==0, else compute average
    if (size == 0) {
        throw string("Empty");
    }
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += values[i];
    }
    return sum / size;
}

double minValue(const double values[], int size) {
    // throw "Empty" if size==0, else compute min
    if (size == 0) {
        throw string("Empty");
    }
    double min = values[0];
    for (int i = 1; i < size; i++) {
        if (min > values[i]) {
            min = values[i];
        }
    }
    return min;
}

double maxValue(const double values[], int size) {
    // throw "Empty" if size==0, else compute max
    if (size == 0) {
        throw string("Empty");
    }
    double max = values[0];
    for (int i = 1; i < size; i++) {
        if (max < values[i]) {
            max = values[i];
        }
    }
    return max;
}
