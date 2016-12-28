#pragma once

#include "Entities\Character.h"

class Player : public Character
{
public:
	Player(const SharedContext& sharedContext, const std::string = "Player");

	void update(const float deltaTime) override;

private:

};