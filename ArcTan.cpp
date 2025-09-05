#include "stdafx.h"


double ArcTan(double X, double Y)
{
	//------------------------------------
	// ArcTan
	//		This function calculates the
	//	Arctangent of X/Y.  The resulting
	//	angle will be between 0 and 2*PI
	//
	//	parameters
	//		X.......X coordinate of vector
	//		Y.......Y coordinate of vector
	//	returns
	//		The angle whose tangent is X/Y
	//------------------------------------
	double Pi = atan(1.0) * 4.0;
     double Angle;
    //-------------------------------------------------------
    // Calculate the initial phase
    //-------------------------------------------------------
    if((X > 0) && (Y > 0)) Angle =atan2(Y,X);
    else if ((X > 0) && (Y < 0)) Angle = Pi - atan2(Y,-X);
    else if ((X < 0) && (Y > 0)) Angle = - atan2(-Y,X);
    else if ((X < 0) && (Y < 0)) Angle = -Pi + atan2(-Y,-X);
    else if((X == 0) && (Y < 0)) Angle = 3.0 * Pi/2.0;
    else if ((X ==0) && (Y > 0)) Angle = Pi/2.0;
    else if ((X < 0) && (Y == 0)) Angle = Pi;
    else if ((X>0)&& (Y == 0)) Angle = 0.0;
	else if ((X == 0) && (Y == 0)) Angle = 0.0;
    return Angle;
}

int CheckAngle(double Start, double End,double Angle)
{
	//-------------------------------------
	// CheckAngle
	//		Determines if an angle is between
	//	two other angles.
	//
	//	parameters:
	//		Start.......First angle to compare to
	//		End.........Second Angle to compare to
	//		Angle.......Is Angle between Start and End
	//	Returns:
	//		True is Angle is between Start and End
	//-------------------------------------
	int rV = 0;
	if(Start > End)
	{
		if((Angle > 0.0) && (Angle < End))
			rV = 1;
		else if(Angle > Start)
			rV = 1;
	}
	else
	{
		if((Angle > Start) && (Angle < End))
			rV = 1;
	}
	return rV;
}

//----------------------------------------
// File Save Utils
//----------------------------------------
void SavePoint(FILE* pOut, CPoint point);
void SaveColor(FILE* pOut, COLORREF color, int Token);

