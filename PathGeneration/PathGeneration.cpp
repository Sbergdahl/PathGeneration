// PathGeneration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>  
int makePath(float resolution, float startX, float startY, float endX, float endY);

int main()
{

	int path;
	float resolution=1;
	float startX = 0;
	float startY = 0;
	float endX = 10;
	float endY = 5;



	path = makePath(resolution,startX,startY,endX, endY);






    return 0;


}

//only works for staight lines in either x/y direction or diagonal
int makePath(float resolution, float startX, float startY, float endX, float endY)
{
	// mata in en väg som är definerad som funktion(er?) 

	// find distance between end and start.
	float distX = endX - startX;
	float distY = endY - startY;


	
	int noGrids;
	if (distX > distY)
	{
		noGrids = distX / resolution;
	}
	else
	{
		noGrids = distY / resolution;
	}

	std::vector<float> stepsY2 = {};
	std::vector<float> stepsX2 = {};


	if (distY > distX) {
		for (int i = 1; i <= noGrids; i++)
		{
			float step = resolution*round((endX - startX) / (endY - startY)*i);
			stepsX2.push_back(step);

			step = resolution*i;
			stepsY2.push_back(step);
		}
	}
		if (distY < distX) {
			for (int i = 1; i <= noGrids; i++)
			{
				float step = resolution*round((endY - startY) / (endX - startX)*i);
				stepsY2.push_back(step);

				step = resolution*i;
				stepsX2.push_back(step);
			}
		}

	return 1;

}
