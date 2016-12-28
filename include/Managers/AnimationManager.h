#pragma once

#include "Entities\EntityState.h"
#include "Sprite\Animation.h"
#include "SharedContext.h"
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>

class AnimationManager
{
public:
	AnimationManager(const SharedContext& sharedContext);

	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;

	inline void flipTile(const bool i) { m_tileFlipped = i; }
	void setAnimationType(const EntityState state, const Direction dir);
	void print();
	void loadInAnimations(const std::string& fileName);

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	std::unordered_map<EntityState, Animation> m_animations;
	Animation* m_currentAnimation;
	SharedContext m_sharedContext;
	sf::Sprite m_sprite;
	bool m_tileFlipped; //For when needs to be flipped for bi-directional movement
};