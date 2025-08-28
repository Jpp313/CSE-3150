#include "advancedmath.h"
#include "mathutils.h"
#include <iostream>

int main(){
    int a = 3;
    int b = 4;
    

    std::cout << "a" << " + " << "b" << " = " << MathUtils::add(a,b) << std::endl;
    std::cout << "a" << " * " << "b" << " = " << MathUtils::multiply(a,b) << std::endl;
    std::cout << "square(a)" << " = " << AdvancedMath::square(a) << std::endl;

    return 0;
}