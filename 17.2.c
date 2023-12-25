#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

typedef struct geoCoord {
	double lats;
	double lons;
};

void userInputWayPoints(int*);
void clearBuffer();
void userInputCoordinates(struct geoCoord* , int);
double overallDistance(struct geoCoord*, int);
double distanceKm(double, double, double, double);
double radianConversion(double);

int main()
{
	
	int* wayPoints = malloc(sizeof(int));
	userInputWayPoints(wayPoints);
	struct geoCoord* cordinates = malloc(sizeof(struct geoCoord) * (*wayPoints));
	struct geoCoord *ptrCordinates = cordinates;
	userInputCoordinates(ptrCordinates, *wayPoints);
	double distance = overallDistance(ptrCordinates, *wayPoints);
	printf("By taking this route you will travel %.2lf km.", distance);
	free(cordinates);
	free(wayPoints);
	return 0;
}

void userInputWayPoints(int* wayPoints)
{
	printf("Enter Number of waypoints In Number: ");
	if (scanf("%d", wayPoints) != 1)
	{
		clearBuffer();
		printf("\nInvalid Input.Try Again\n");
		userInputWayPoints(wayPoints);
	}


}
void userInputCoordinates(struct geoCoord* coordinates, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		printf("Waypoint %d: ", i + 1);
		if (scanf("%lf  %lf", &(coordinates[i].lats), &(coordinates[i].lons)) != 2)
		{
			printf("Invalid Input.Try again\n");
			clearBuffer();
			i--; // index stays at same place
		}
	}

}
double overallDistance(struct geoCoord* coordinates, int arrsize)
{
	double distance = 0.0;

	for (int i = 0; i < arrsize - 1; i++)
	{
		distance = distance + distanceKm(coordinates[i].lats, coordinates[i+1].lats, coordinates[i].lons, coordinates[i+1].lons);
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