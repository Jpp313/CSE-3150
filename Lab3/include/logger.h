#ifndef LOGGER_H
#define LOGGER_H

#include <string>

void addReading(const std::string& label, double value,
                std::string labels[], double values[],
                int& size, int capacity);

void updateValue(double* valuePtr, double newValue);

void printReading(const std::string& label, const double& value);

double average(const double values[], int size);
double minValue(const double values[], int size);
double maxValue(const double values[], int size);

#endif // LOGGER_H
