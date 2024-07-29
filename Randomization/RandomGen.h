#pragma once
#include<random>
#include <iostream>

class RandomGen
{
	protected:
		double Cmin, Cmax;
		float pMin, pMax;
				
	public:
		RandomGen();

	public:
		double RandomizeColor();
		float RandomizeForce();
		float RandomizeYForce();
		int RandomizeScale();
};




