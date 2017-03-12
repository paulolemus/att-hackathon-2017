#ifndef SHOVESTER_CALCULATEANGLETOOTHER_H   
#define SHOVESTER_CALCULATEANGLETOOTHER_H   


#include <cmath>

/// @brief Returns the SDL angle for distance towards other
double calculateAngleToOther(
    double x1, double y1,
    double x2, double y2
) {
   return std::atan((y2 - y1) / (x2 - x1));
}


#endif // SHOVESTER_CALCULATEANGLETOOTHER_H   
