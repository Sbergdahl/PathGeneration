// PathGeneration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>


using namespace std;
vector< vector<float> > makePathDiag(float resolution, float startX, float startY, float endX, float endY);
vector< vector<float> > makePathEllipse(float resolution, float startX, float startY, float endX, float endY);
vector <vector<float> > setDirection(vector <vector<float> > pathVector, float startX, float startY, float endX, float endY);

int main()
{

	std::vector<vector<float> >path;
	std::vector<vector<float> >path2;
	/*float resolution = 0.1;
	float startX = 0;
	float startY = 0;
	float endX = 2;
	float endY = 1;
	string type;*/



	float resolution = 0.1;
	string startX;
	string startY;
	string endX;
	string endY;
	string type;

	// load a vector of waypoints and use that as input.


	string line;
	ifstream infile("input_data.txt");

	if (infile.is_open())
	{
		while (infile.good())
		{
			getline(infile, startX, ',');
			getline(infile, startY, ',');
			getline(infile, endX, ',');
			getline(infile, endY, ',');
			getline(infile, type, '\n');
			
			//change this to have the right things as function input
			if (type == "ellipse")
			{
				path2 = makePathEllipse(resolution, stof(startX), stof(startY), stof(endX), stof(endY));
				
			}
			else
			{
				path2 = makePathDiag(resolution, stof(startX), stof(startY), stof(endX), stof(endY));
			}
			//dito
			
			path.insert(path.end(), path2.begin(), path2.end());
		}

	}

	ofstream outfile; 
	outfile.open("coordinate_vector.txt");
	for (int i=0; i < path.size(); i++)
	{
		outfile << path[i][0] << "," << path[i][1] << endl;
	}
	outfile.close();



    return 0;


}

//only works for staight lines in either x/y direction or diagonal
vector< vector<float> > makePathDiag(float resolution, float startX, float startY, float endX, float endY)
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
	else if (distY < distX) {
		for (int i = 1; i <= noGrids; i++)
		{
			float step = resolution*round((endY - startY) / (endX - startX)*i);
			stepsY2.push_back(step);

			step = resolution*i;
			stepsX2.push_back(step);
		}
	}


	std::vector< vector<float> > pathVector;
	
	for (int i = 0; i < stepsY2.size(); i++)
	{
		std::vector<float> row;
		row.push_back(stepsX2[i]);
		row.push_back(stepsY2[i]);
		pathVector.push_back(row);
	}


	pathVector = setDirection(pathVector, startX, startY, endX, endY);
	return pathVector;
}


//works for ellipses in positive x-y direction. 
vector< vector<float> > makePathEllipse(float resolution, float startX, float startY, float endX, float endY)
{
	// mata in en väg som är definerad som funktion(er?) 

	// find distance between end and start.
	float distX = endX - startX;
	float distY = endY - startY;

	int noGrids;
	if (abs(distX) > abs(distY))
	{
		noGrids = abs(distX) / resolution;
	}
	else
	{
		noGrids = abs(distY) / resolution;
	}

	// set both distances to their absolute value, sign of this will be determined later. 
	float xScale = abs(distX * 1/resolution);
	float yScale = abs(distY * 1/resolution);


	std::vector<float> stepsY2 = {};
	std::vector<float> stepsX2 = {};  

	//make path
	int i = 0;


	float step = 0;
	for (i=0;step < yScale; i++)
	{

		//yp2(end+1)=b/a * sqrt(a^2-(x(i))^2)

		float step1 = yScale / xScale;
		float step2 = sqrt(abs(pow(xScale, 2) - pow(-(xScale - i), 2)));
		step = (yScale / xScale) * sqrt(abs(pow(xScale, 2) - pow(-(xScale - i), 2)));

		stepsY2.push_back(step);
	
		//std::cout << stepsY2.back();


		//while (round(yp2(end)-yp2(end-1)) > 1)
		while (i > 0 &&  round(stepsY2.back() -stepsY2.end()[-2]) > 1)
		{


			// pop and push from vector, ugly solution
			float tmp1 = 0;
			tmp1 = stepsY2.back();
			float insertedValue = 0;
			stepsY2.pop_back();

			//insert the inbetween values needed in order for the path to be uninterupted. 
			insertedValue = stepsY2.back()+ 1;
			stepsY2.push_back(insertedValue);
			stepsY2.push_back(tmp1);
		}
		

	}



	//create x-path from y-path
	for (int i = 0; i < stepsY2.size(); i++)
	{

		float s1 = xScale / yScale;
		float s2 = sqrt(pow(abs(yScale), 2) - pow(abs(stepsY2[i]), 2));
		float s3 = abs(s1*(s2 - yScale));
		stepsX2.push_back(resolution*round(s3));
	}

	for (int i = 0; i < stepsY2.size(); i++)
	{
		stepsY2[i] = resolution*round(stepsY2[i]);
	}

	// set the correct directions of the paths
	// change in here to fix so that we get the  right ofsets w.r.t. the starting points 



    //conbine the vectors
	std::vector< vector<float> > pathVector;
	for (int i = 0; i < stepsY2.size(); i++)
	{
		std::vector<float> row;
		row.push_back(stepsX2[i]);
		row.push_back(stepsY2[i]);
		pathVector.push_back(row);
	}

	pathVector = setDirection(pathVector, startX, startY, endX, endY);
	return pathVector;

}


vector <vector<float> > setDirection(vector <vector<float> > pathVector, float startX, float startY, float endX, float endY)
{

	float distX = endX - startX;
	float distY = endY - startY;

	//look at this possibly split it.
    if (distY >= 0)
	{
		if (distX < 0)
		{
			for (int i = 0; i < pathVector.size(); i++)
			{
				pathVector[i][0] = pathVector[i][0] + startX;
				pathVector[i][1] = pathVector[i][1] + startY;
			}
		}
		else
		{
			for (int i = 0; i < pathVector.size(); i++)
			{
				pathVector[i][0] = pathVector[i][0] + startX;
				pathVector[i][1] = pathVector[i][1] + startY;
			}
		}
	}
	
	else if (distY < 0)
	{

		if (distX < 0)
		{
			for (int i = 0; i < pathVector.size(); i++)
			{
				pathVector[i][0] = -pathVector[i][0] + startX;
				pathVector[i][1] = -pathVector[i][1] + startY;
			}
		}
		else
		{
			for (int i = 0; i < pathVector.size(); i++)
			{
				pathVector[i][0] = -pathVector[i][0] + startX;
				pathVector[i][1] = -pathVector[i][1] + startY;
			}
		}
	}


	return pathVector;
}