#pragma once
#include "roundsHandler.h"

RoundsHandler::RoundsHandler(int _roundsSeconds) {
	roundsTimer.setMaxSeconds(_roundsSeconds);
	roundFinished = false;
	turn = Turn::PLAYERS_TURN;
}

int RoundsHandler::getMaxSecondsInRound() {
	return roundsTimer.getMaxSeconds();
}

int RoundsHandler::getCurrentSecondsInRound() {
	return roundsTimer.getCurrentSeconds();
}

void RoundsHandler::startRound() {
	roundsTimer.start();
}

void RoundsHandler::restartRound() {
	roundsTimer.restart();
}

bool RoundsHandler::hasRoundFinished() {
	return roundsTimer.finished();
}

void RoundsHandler::changeTurn() {
	turn = turn == Turn::PLAYERS_TURN ? Turn::OPPONENTS_TURN : Turn::PLAYERS_TURN;
}

Turn RoundsHandler::getTurnOrder() {
	return turn;
}



