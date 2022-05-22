#pragma once
#ifndef ROUNDS_HANLDER
#define ROUNDS_HANDLER
#include <SFML/Graphics.hpp>
#include "timer.h"

enum class Turn {PLAYERS_TURN, OPPONENTS_TURN};

class RoundsHandler {

	Timer roundsTimer;

	bool roundFinished;

	Turn turn;

public:

	RoundsHandler(int _roundsSeconds);

	void startRound();

	int getMaxSecondsInRound();

	int getCurrentSecondsInRound();

	bool hasRoundFinished();

	void changeTurn();

	Turn getTurnOrder();

};
#endif