#ifndef SHOVESTER_CALCULATEANGLETOOTHER_H   
#define SHOVESTER_CALCULATEANGLETOOTHER_H   


#include <cmath>

/// @brief Returns the SDL angle for distance towards other
double calculateAngleToOther(
    double x1, double y1,
    double x2, double y2
) {
   if(x1 > 180) x1 -= 180;
   if(x2 > 180) x2 -= 180;
   if(y1 > 180) y1 -= 180;
   if(y2 > 180) y2 -= 180;

   double rad = std::atan((y2 - y1) / (x2 - x1));
   return ((rad*180)/3.14);
}


#endif // SHOVESTER_CALCULATEANGLETOOTHER_H   
