#pragma once
#include "RewardFunction.h"

namespace RLGSC {

	// TODO: EventReward (ugh)

	// https://github.com/AechPro/rocket-league-gym-sim/blob/main/rlgym_sim/utils/reward_functions/common_rewards/misc_rewards.py
	class VelocityReward : public RewardFunction {
		bool isNegative;
		VelocityReward(bool isNegative = false) : isNegative(isNegative) {}
		virtual float GetReward(const PlayerData& player, const GameState& state, const Action& prevAction) {
			return player.phys.vel.Length() / CommonValues::CAR_MAX_SPEED * (1 - 2 * isNegative);
		}
	};

	// https://github.com/AechPro/rocket-league-gym-sim/blob/main/rlgym_sim/utils/reward_functions/common_rewards/misc_rewards.py
	class SaveBoostReward : public RewardFunction {
		float exponent;
		SaveBoostReward(float exponent = 0.5f) : exponent(exponent) {}

		virtual float GetReward(const PlayerData& player, const GameState& state, const Action& prevAction) {
			return RS_CLAMP(powf(player.boostFraction, exponent), 0, 1);
		}
	};

	// https://github.com/AechPro/rocket-league-gym-sim/blob/main/rlgym_sim/utils/reward_functions/common_rewards/player_ball_rewards.py
	class VelocityPlayerToBallReward : public RewardFunction {
		virtual float GetReward(const PlayerData& player, const GameState& state, const Action& prevAction) {
			Vec dirToBall = (state.ball.pos - player.phys.pos).Normalized();
			Vec normVel = player.phys.vel / CommonValues::CAR_MAX_SPEED;
			return dirToBall.Dot(normVel);
		}
	};

	// https://github.com/AechPro/rocket-league-gym-sim/blob/main/rlgym_sim/utils/reward_functions/common_rewards/player_ball_rewards.py
	class FaceBallReward : public RewardFunction {
		virtual float GetReward(const PlayerData& player, const GameState& state, const Action& prevAction) {
			Vec dirToBall = (state.ball.pos - player.phys.pos).Normalized();
			return player.carState.rotMat.forward.Dot(dirToBall);
		}
	};

	// https://github.com/AechPro/rocket-league-gym-sim/blob/main/rlgym_sim/utils/reward_functions/common_rewards/player_ball_rewards.py
	class TouchBallReward : public RewardFunction {
		float aerialWeight;
		TouchBallReward(float aerialWeight = 0) : aerialWeight(aerialWeight) {}

		virtual float GetReward(const PlayerData& player, const GameState& state, const Action& prevAction) {
			using namespace CommonValues;

			if (player.ballTouched) {
				return powf((state.ball.pos.z + BALL_RADIUS) / (BALL_RADIUS * 2), aerialWeight);
			} else {
				return 0;
			}
		}
	};
}