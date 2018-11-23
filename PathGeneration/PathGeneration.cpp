// PathGeneration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>  
int makePathDiagDiag(float resolution, float startX, float startY, float endX, float endY);
int makePathEllipse(float resolution, float startX, float startY, float endX, float endY);

int main()
{

	int path;
	float resolution=0.1;
	float startX = 0;
	float startY = 0;
	float endX = 1;
	float endY = 1;



	//path = makePath(resolution,startX,startY,endX, endY);
	path = makePathEllipse(resolution, startX, startY, endX, endY);





    return 0;


}

//only works for staight lines in either x/y direction or diagonal
int makePathDiag(float resolution, float startX, float startY, float endX, float endY)
{
	// mata in en väg som är definerad som funktion(er?) 

	// find distance between end and start.
	float distX = abs(endX - startX);
	float distY = abs(endY - startY);


	
	int noGrids;
	if (abs(distX) > abs(distY))
	{
		noGrids = abs(distX) / resolution;
	}
	else
	{
		noGrids = abs(distY) / resolution;
	}

	std::vector<float> stepsY2 = {};
	std::vector<float> stepsX2 = {};


	if (distY >= distX) {
		for (int i = 1; i <= noGrids; i++)
		{
			float step = resolution*round((endX - startX) / (endY - startY)*i);
			stepsX2.push_back(step);

			step = resolution*i;
			stepsY2.push_back(step);
		}
	}
		if (distY <= distX) {
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


//only works for staight lines in either x/y direction or diagonal
int makePathEllipse(float resolution, float startX, float startY, float endX, float endY)
{
	// mata in en väg som är definerad som funktion(er?) 

	// find distance between end and start.
	float distX = abs(endX - startX);
	float distY = abs(endY - startY);

	int noGrids;
	if (abs(distX) > abs(distY))
	{
		noGrids = abs(distX) / resolution;
	}
	else
	{
		noGrids = abs(distY) / resolution;
	}

	float xScale = endX * 10;
	float yScale = endY * 10;


	std::vector<float> stepsY2 = {};
	std::vector<float> stepsX2 = {};  

	//make path
	int i = 0;

	float step1 = yScale / xScale;
	float step2 = sqrt(abs(pow(xScale, 2) - pow(-(noGrids - i), 2)));

	float step = (yScale / xScale) * sqrt(abs(pow(xScale, 2) - pow(-(noGrids-i), 2)));
	//stepsY2.push_back(step);


	std::vector<float>::iterator it;
	for (i=0;i <= noGrids; i++)
	{

		//yp2(end+1)=b/a * sqrt(a^2-(x(i))^2)
		
		step1 = yScale / xScale;
		step2 = sqrt(abs(pow(xScale, 2) - pow(-(noGrids - i), 2)));
		step = (yScale / xScale) * sqrt(abs(pow(xScale, 2) - pow(-(noGrids - i), 2)));

		stepsY2.push_back(step);
		it = stepsY2.end();
	

		// fram hit verkar fungera. titta på detta imorgon. 
		//while (round(yp2(end)-yp2(end-1)) > 1)
		/*while ( i > 0 && round(stepsY2.back - stepsY2[0]) > resolution)
		{
			//it = stepsY2.begin();

			//yp2=[yp2(1:end-1) yp2(end-1)+1 yp2(end) ]
			it = stepsY2.end()-1;
			float insertedValue = stepsY2[0] + resolution;
			stepsY2.insert(it,insertedValue);
		}
		*/

		//yp3 = round(yp2)
		//xp = round(abs(a / b * sqrt(b. ^ 2 - yp2. ^ 2) - a))
	}
	return 1;

}
