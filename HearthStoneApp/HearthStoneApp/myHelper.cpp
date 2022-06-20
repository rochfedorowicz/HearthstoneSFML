#include "myHelper.h"

double MyHelper::getDistance(sf::Vector2f _point1, sf::Vector2f _point2) {
	return sqrt(pow(_point1.x - _point2.x, 2) + pow(_point1.y - _point2.y, 2));
}

int MyHelper::getIndexOfSpecifiedItemInVector(std::vector<double>& _vector, lambdaFunction _lambda) {
	int index = 0;
	for (int i = 1; i < _vector.size(); ++i) {
		if (_lambda(_vector.at(index), _vector.at(i))) index = i;
	}
	return index;
}

std::string MyHelper::convertIntToString(int _intValue) {
	std::stringstream s;
	s << _intValue;
	std::string s2 = "";
	std::getline(s, s2);
	return s2;
}

int MyHelper::getRandomInt(int _lowerInterval, int _upperInterval) {
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(_lowerInterval, _upperInterval);
	return distribution(rng);
}