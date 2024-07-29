#include "RandomGen.h"

RandomGen::RandomGen()
{
	this->Cmax = 1.0;
	this->Cmin = 0.0;
    this->pMax = 4000.f;
    this->pMin = -4000.f;
}

double RandomGen::RandomizeColor()
{
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define the range [min, max]
    std::uniform_real_distribution<> dis(this->Cmin, this->Cmax);

    // Generate and return a random decimal number in the range [min, max]
    return dis(gen);
}

float RandomGen::RandomizeForce() {
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define the range [min, max]
    std::uniform_real_distribution<> dis(this->pMin, this->pMax);

    // Generate and return a random decimal number in the range [min, max]
    return dis(gen);
}

float RandomGen::RandomizeYForce()
{
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define the range [min, max]
    std::uniform_real_distribution<> dis(1500.f, 8000.f);

    return dis(gen);
}

int RandomGen::RandomizeScale()
{
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define the range [min, max]
    std::uniform_real_distribution<> dis(2, 10);

    return dis(gen);
}


