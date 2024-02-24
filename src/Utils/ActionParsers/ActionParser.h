#pragma once
#include "../Gamestates/GameState.h"
#include "../BasicTypes/Action.h"
#include "../BasicTypes/Lists.h"

// https://github.com/AechPro/rocket-league-gym-sim/blob/main/rlgym_sim/utils/obs_builders/obs_builder.py
namespace RLGSC {
	class ActionParser {
	public:
		typedef std::vector<int> Input;

		virtual ActionSet ParseActions(const Input& actionsData, const GameState& gameState) = 0;
		virtual int GetActionAmount() = 0;
	};
}