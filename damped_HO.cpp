#include <iostream>
#include <vector>
#include <fstream>

int main() {
    // defining the constants
    const float g{ 9.8f }; // accelaration due to gravity in m/s^2
    const double stepDifference{ 0.001 };

    // Input the properties of oscillator
    double mass{};
    std::cout << "Enter mass of the oscillator -->      ";  //in units of kg
    std::cin >> mass;
    
    double  springConstant{};
    std::cout << "Enter value of force constant -->     ";  // in units of N/m
    std::cin >> springConstant;

    double dampConstant{};
    std::cout << "Enter value of damping constant -->   "; //in units of kg/s^2
    std::cin >> dampConstant;

    double initPosition{};
    std::cout << "Enter initial position -->            ";
    std::cin >> initPosition;

    double initVelocity{};
    std::cout << "Enter initial velocity -->            ";
    std::cin >> initVelocity;

    // defining the time vector
    double initialTime{ 0 };
    double finalTime{ 10 };

    int num_elements = (finalTime - initialTime) / stepDifference; 
    std::vector<double> time{};
    
    for (int count{0}; count < num_elements; count++) {
        time.push_back( count * stepDifference );
    }

    /* Differential equation is x" + d/m x' + k/m x = 0
        h == stepDifference
        Put x' = v so that , x(i + 1) = x(i) + h * v(i)
        then , v' + d/m v + k/m x = 0
        So the second eqn becomes
        v(i + 1) = v(i) - h * ( d/m v(i) + k/m x(i)) 
    */

    // defining the position and velocity vectors
    std::vector<double> x{};
    std::vector<double> v{};

    x.push_back(initPosition);
    v.push_back(initVelocity);

    for (int count{0}; count < num_elements; count++) {
        v.push_back( v[count] - stepDifference * ( (v[count] * dampConstant/mass) + (springConstant * x[count] / mass) ) );
        x.push_back( x[count] + v[count] * stepDifference );
    }

    // writing to external file
    std::ofstream out("dampedHO.dat");
    out << "#Time\t\tDisplacement";

    for (int count{0}; count < num_elements; count++) {
        out << time[count] << "\t\t" << x[count] << '\n';
    }
    
    return 0;
}
