#include "Sector.h"
#include <cmath>

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
    int sum = pow(abs(x), 2) + pow(abs(y), 2) + pow(abs(z), 2);
    distance_from_earth = sqrt(sum);
    int distance = distance_from_earth;
    sector_code = std::to_string(distance);

    if(x>0){
        sector_code += "R";
    }else if(x<0){
        sector_code += "L";
    }else{
        sector_code += "S";
    }


    if(y>0){
        sector_code += "U";
    }else if(y<0){
        sector_code += "D";
    }else{
        sector_code += "S";
    }


    if(z>0){
        sector_code += "F";
    }else if(z<0){
        sector_code += "B";
    }else{
        sector_code += "S";
    }


    // TODO: Calculate the distance to the Earth, and generate the sector code
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}