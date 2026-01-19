#pragma once
#include <cmath>
#include <numbers>

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
		return (2.0 / std::numbers::pi) * std::asin(std::sin(x));
	}
};

class SawtoothWave : public Wave 
{
	double Calculate(float x) override 
	{
		return (2.0 / std::numbers::pi) * (x - std::numbers::pi * std::floor(x / std::numbers::pi + 0.5));
	}
};

class NoiseWave : public Wave 
{
	double Calculate(float x) override 
	{
		return ((double)rand() / RAND_MAX) * 2.0 - 1.0; // Random value between -1 and 1
	}
};