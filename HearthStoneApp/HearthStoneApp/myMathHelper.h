#pragma once
#ifndef MY_MATH_HELPER
#define MY_MATH_HELPER
#include <SFML/Graphics.hpp>

typedef bool (lambdaFunction)(double&, double&);

class MyMathHelper {

public:

	static double getDistance(sf::Vector2f _point1, sf::Vector2f _point2);

	static int getIndexOfSpecifiedItemInVector(std::vector<double>& _vector, lambdaFunction _lambda);

};
#endif