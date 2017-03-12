#ifndef SHOVESTER_CALCULATEANGLETOOTHER_H   
#define SHOVESTER_CALCULATEANGLETOOTHER_H   


#include <cmath>

/// @brief Returns the SDL angle for distance towards other
double calculateAngleToOther(
    double x1, double y1,
    double x2, double y2
) {
   double rad = std::atan((y2 - y1) / (x2 - x1));
   double deg = (rad*180)/3.14;

   if(deg > 90) deg -= 180;
   if(deg < -90) deg += 180;

   return deg;
}


#endif // SHOVESTER_CALCULATEANGLETOOTHER_H   
