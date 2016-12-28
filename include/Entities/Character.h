#pragma once

#include "Entities\Entity.h"
#include "Entities\EntityState.h"

class Character : public Entity
{
public:
	Character(const SharedContext& sharedContext, const std::string name);

protected:
	void update(const float deltaTime) override;

private:
	void determineAnimationType();
	EntityState m_state;
	void setState(const EntityState state);

	void loadInDetails(const std::string& fileName) override;
};