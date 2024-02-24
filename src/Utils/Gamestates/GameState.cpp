#include "GameState.h"

#include "../../Math.h"

namespace RLGSC {
	void GameState::UpdateFromArena(Arena* arena) {

		ballState = arena->ball->GetState();
		ball = PhysObj(ballState);
		ballInv = ball.Invert();

		players.resize(arena->_cars.size());
		
		auto carItr = arena->_cars.begin();
		for (int i = 0; i < players.size(); i++) {
			auto& player = players[i];
			player.UpdateFromCar(*carItr, arena->tickCount);
			if (player.ballTouched)
				lastTouchCarID = player.carId;

			carItr++;
		}

		// TODO: Update boost pads in the correct order, opposite Y for inverted
		for (int i = 0; i < CommonValues::BOOST_LOCATIONS_AMOUNT; i++) {
			boostPads[i] = arena->_boostPads[i]->GetState().isActive;
			boostPadsInv[i] = arena->_boostPads[CommonValues::BOOST_LOCATIONS_AMOUNT - i - 1]->GetState().isActive;
		}

		// Update goal scoring
		// If you don't have a GoalScoreCondition then that's not my problem lmao
		if (Math::IsBallScored(ball.pos))
			scoreLine[(int)RS_TEAM_FROM_Y(ball.pos.y)]++;
	}
}