// PathGeneration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
int makePath(float resolution, float startX, float startY, float endX, float endY);

int main()
{

	int path;
	path = makePath(0.1,0.0,0.0, 1.0, 0.0);






    return 0;


}


int makePath(float resolution, float startX, float startY, float endX, float endY)
{
	// mata in en väg som är definerad som funktion(er?) 

	// find distance between end and start.
	float distX = endX - startX;
	float distY = endY - startY;

	int noStepsX = distX / resolution;
	int noStepsY = distY / resolution;

	// mata in slut och start punkt 
	// titta på vilken upplösning kartan har 
	std::vector<float> stepsX = {};
	if (noStepsX > 0) {
		
		int i = 0;
		// loop and create the path in x direction
		for (int i = 0; i <= noStepsX; i++) {
			float step = startX + resolution*distX*i;
			stepsX.push_back(step);
		}
	}
	std::vector<float> stepsY = {};
	if (noStepsY > 0) {
		
		// loop and create the path in y direction
		for (int i = 0; i <= noStepsY; i++) {
			float step = startY + resolution*distY*i;
			stepsY.push_back(step);
		}
	}
	// dela upp vägen i avsnitt som matchar upplösningen på kartan

	// 
	
	return 1;

}
