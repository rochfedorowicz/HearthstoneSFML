#pragma once
#ifndef ROUNDS_HANLDER
#define ROUNDS_HANDLER
#include <SFML/Graphics.hpp>
#include "../timer.h"

/** Enum indicating all possible turn owners. */
enum class Turn {PLAYERS_TURN, OPPONENTS_TURN};

/** Class resposible for round handling. */
class RoundsHandler {

	/** TImer used for time measurement. */
	Timer roundsTimer;

	/** Logic value indicating if round is finished. */
	bool roundFinished;

	/** Indicates whose round it is. */
	Turn turn;

public:

	/** Main cosntructor. */
	RoundsHandler(int _roundsSeconds);

	/** Function starting a round. */
	void startRound();

	/** Function restarting a round. */
	void restartRound();

	/** Function getting max number of secoinds in round. */
	int getMaxSecondsInRound();

	/** Function getting current number of seconds in round. */
	int getCurrentSecondsInRound();

	/** Function checking if round has finished. */
	bool hasRoundFinished();

	/** Function changing turn's owner. */
	void changeTurn();

	/** Function getting current turn's state. */
	Turn getTurnOrder();

};
#endif