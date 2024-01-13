#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

void userInputWayPoints(int*);
void clearBuffer();
void userInputCoordinates(double*, double*, int);
double overallDistance(double*, double*, int);
double distanceKm(double, double, double, double);
double radianConversion(double);

int main()
{
	int* wayPoints = malloc(sizeof(int));
	userInputWayPoints(wayPoints);
	double* lats = malloc(sizeof(double) * (*wayPoints));
	double* lons = malloc(sizeof(double) * (*wayPoints));
	userInputCoordinates(lats, lons, *wayPoints);
	double distance = overallDistance(lats, lons, *wayPoints);
	printf("By taking this route you will travel %.2lf km.", distance);
	free(lats);
	free(lons);
	free(wayPoints);
	return 0;
}
void userInputWayPoints(int* wayPoints)
{
	float input;
	printf("Enter the waypoints:");
	
	if (scanf("%f", &input)==1 && input > 0 && (int)input == (int)ceil(input))
	{
		*wayPoints = (int)input;
		clearBuffer();
	}
	else
	{
		printf("Invalid Input. Try again\n");
		clearBuffer();
		userInputWayPoints(wayPoints);
	}
}
void userInputCoordinates(double* lats, double* lons, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		printf("Waypoint %d: ", i + 1);
		if (scanf("%lf  %lf", &lats[i], &lons[i]) != 2 || lats[i] < -90 || lats[i]>90 || lons[i] < -180 || lons[i]>180)
		{
			printf("Invalid Input.Try again.\n");
			clearBuffer();
			i--; // index stays at same place
		}
	}
}
double overallDistance(double* lats, double* lons, int arrsize)
{
	double distance = 0.0;

	for (int i = 0; i < arrsize - 1; i++)
	{
		distance = distance + distanceKm(lats[i], lats[i + 1], lons[i], lons[i + 1]);

	}
	return distance;
}
double distanceKm(double lat1, double lat2, double lon1, double lon2)
{
	//reusing from last lab
	lat1 = radianConversion(lat1);
	lon1 = radianConversion(lon1);
	lat2 = radianConversion(lat2);
	lon2 = radianConversion(lon2);

	return 6378.388 * acos(sin((lat1)) * sin(lat2) + cos(lat1) * cos(lat2) * cos((lon2 - lon1)));
}

double radianConversion(double value)
{
	//reusing from last lab
	return value * (M_PI / 180.0);
}
void clearBuffer()
{
	while (getchar() != '\n');
}
