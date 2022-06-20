#pragma once
#ifndef MY_HELPER
#define MY_HELPER
#include <SFML/Graphics.hpp>
#include <sstream>
#include <random>

typedef bool (lambdaFunction)(double&, double&);

//Class used as a storege for miscellaneous functions (mathematical or conversion mainly)
class MyHelper {

public:

		//Function computing distance between two points
		static double getDistance(sf::Vector2f _point1, sf::Vector2f _point2);

		//Function searching for item that could be specified by lambda function (eg. min, max)
		static int getIndexOfSpecifiedItemInVector(std::vector<double>& _vector, lambdaFunction _lambda);

		//Function converting int into string
		static std::string convertIntToString(int _intValue);

		static int getRandomInt(int _lowerInterval, int _upperInterval);
};
#endif