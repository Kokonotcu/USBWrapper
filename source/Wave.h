#pragma once
#include <math.h>
#include <cmath>
#include <numbers>

# define M_PI           3.14159265358979323846f

class Wave 
{
public:
	Wave() = default;
	virtual double Calculate(float x) = 0;
};

class SineWave : public Wave 
{
	double Calculate(float x) override {
		return std::sin(x);
	}
};

class SquareWave : public Wave 
{
	double Calculate(float x) override {
		return (std::sin(x) >= 0) ? 1.0 : -1.0;
	}
};

class TriangleWave : public Wave 
{
	double Calculate(float x) override 
	{
		return (2.0 / M_PI) * std::asin(std::sin(x));
	}
};

class SawtoothWave : public Wave 
{
	double Calculate(float x) override 
	{
		return (2.0 / M_PI) * (x - M_PI * std::floor(x / M_PI + 0.5));
	}
};

class NoiseWave : public Wave 
{
	double Calculate(float x) override 
	{
		return ((double)rand() / RAND_MAX) * 2.0 - 1.0; // Random value between -1 and 1
	}
};