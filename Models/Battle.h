#ifndef BATTLE_H
#define BATTLE_H

#pragma once

#include "..\Models\IBattleService.h"
#include "..\Models\IEntity.h"
#include "..\Models\Player.h"
#include "..\Models\Enum.h"

#include <iostream>
#include <vector>
#include <random>
using namespace std;

using namespace MT::Project::Models::Common;

namespace MT
{
	namespace Project
	{
		namespace Models
		{
			class Battle
				: public IBattleService
			{
			private:
				const static int factor = 10;

				static double GetRandom()
				{
					vector<double> range{ {	0.85, 1.2 } };
					auto RandNumber = mt19937();
					RandNumber.seed(random_device()());
					uniform_real_distribution<double> dist_(range.front(), range.back());
					return (dist_(RandNumber));
				}
			public:
				static int CalculateAttack(IEntity* o, IEntity* p)
				{
					auto AttackValue = o->Get(Attack) * factor * GetRandom() / p->Get(Defense);

					if (AttackValue <= 0)
					{
						AttackValue = 10 * GetRandom();
					}

					return static_cast<int>(AttackValue);
				}

				static int CalculateDefense(IEntity* o, IEntity* p)
				{
					auto DefenseValue = o->Get(Defense) * factor * GetRandom() / p->Get(Attack);

					if (DefenseValue <= 0)
					{
						DefenseValue = 10 * GetRandom();
					}

					return static_cast<int>(DefenseValue);
				}

				static bool CalculateSpeed(IEntity* o, IEntity* p)
				{
					return  o->Get(Speed) - p->Get(Speed) > 0;
				}

				static int CalculateReward(IEntity* o, IEntity* p)
				{
					auto RewardValue = (o->Get(Level) + p->Get(Level)) * factor * GetRandom();

					if (RewardValue <= 0)
					{
						RewardValue = 5 * factor * GetRandom();
					}

					return static_cast<int>(RewardValue);
				}
			};
		}
	}
}

#endif