#include "myMathHelper.h"
double MyMathHelper::getDistance(sf::Vector2f _point1, sf::Vector2f _point2) {
	return sqrt(pow(_point1.x - _point2.x, 2) + pow(_point1.y - _point2.y, 2));
}

int MyMathHelper::getIndexOfSpecifiedItemInVector(std::vector<double>& _vector, lambdaFunction _lambda) {
	int index = 0;
	for (int i = 1; i < _vector.size(); ++i) {
		if (_lambda(_vector.at(index), _vector.at(i))) index = i;
	}
	return index;
}