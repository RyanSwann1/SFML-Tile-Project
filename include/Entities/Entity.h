#pragma once

#include "SharedContext.h"
#include "Sprite\SpriteSheet.h"
#include <SFML\Graphics.hpp>

class Entity
{
	friend class EntityManager;
public:
	Entity(const SharedContext& sharedContext, const std::string name = "");
	
	const int getID() const { return m_ID; }
	const std::string& getName() const { return m_name; }

	void draw(sf::RenderWindow& window);
	virtual void update(const float deltaTime);

protected:
	void moveDirection(const Direction newDir);
	inline void accelerate(const sf::Vector2f& acceleration) { m_acceleration += acceleration; }
	virtual void loadInDetails(const std::string& fileName);

	SpriteSheet& getSpriteSheet() { return m_spriteSheet; }
	const Direction getCurrentDirection() const { return m_currentDirection; }
	const sf::Vector2f& getVelocity() const { return m_velocity; }
private:
	SharedContext m_sharedContext;
	Direction m_currentDirection;
	SpriteSheet m_spriteSheet;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_speed;
	sf::Vector2f m_friction;
	sf::Vector2f m_oldPosition;
	sf::Vector2f m_position;
	const sf::Vector2f m_startPosition;
	const std::string m_name;
	void move(const float x, const float y);
	inline void applyGravity() { accelerate(sf::Vector2f(0, -m_gravity)); }
	void applyFriction();

	float m_gravity;
	

	int m_ID;

	void setPosition(const float x, const float y) { m_position = sf::Vector2f(x, y); }
	void setID(const int ID) { m_ID = ID; }
};