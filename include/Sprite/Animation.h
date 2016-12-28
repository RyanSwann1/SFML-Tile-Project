#pragma once

#include "Direction.h"
#include "Managers\TextureManager.h"
#include <SFML\Graphics.hpp>
#include <string>

class Animation
{
public:
	Animation(TextureManager& textureManager, const std::string& tileSetName, const int startRow, const int endRow, 
		const int column, const int frameTime, const int repeatable, const sf::Vector2i frameSize, const int tileSize);
	~Animation();

	inline const bool isFinished() const { return m_startRow < m_endRow; }
	inline const bool isRepeatable() const { return m_repeatable; }

	void stop();
	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);
	void setDrawLocation();

private:
	float m_elaspedTime;
	int m_currentRow;
	
	const int m_startRow;
	const int m_endRow;
	const int m_column;
	const float m_frameTime;
	const bool m_repeatable;
	const sf::Vector2i m_frameSize;
	const int m_tileSize;
	const std::string m_tileSetName;
	sf::IntRect m_frame;
	sf::Sprite m_sprite;
	TextureManager& m_textureManager;

	void changeDrawLocation(const sf::Vector2i newPos);
};