#include "..\..\include\Sprite\Animation.h"

Animation::Animation(TextureManager& textureManager, const std::string& tileSetName, const int startFrame, const int endFrame, const int column, const int frameTime, const int repeatable, const sf::Vector2i frameSize, const int tileSize)
	: m_startRow(startFrame),
	m_endRow(endFrame),
	m_column(column),
	m_frameTime(frameTime),
	m_repeatable(static_cast<bool>(repeatable)),
	m_frameSize(frameSize),
	m_frame(sf::Vector2i(0, 0), sf::Vector2i(frameSize.x, frameSize.y)),
	m_tileSize(tileSize),
	m_textureManager(textureManager),
	m_tileSetName(tileSetName)
{
	m_sprite.setTexture(*textureManager.getResource(m_tileSetName));
}

Animation::~Animation()
{
	m_textureManager.releaseResource(m_tileSetName);
}

void Animation::stop()
{
	m_currentRow = m_startRow;
	changeDrawLocation(sf::Vector2i(m_currentRow, m_column));
	m_elaspedTime = 0;
}

void Animation::update(const float deltaTime)
{
	m_elaspedTime += deltaTime;
	if (m_elaspedTime >= m_frameTime)
	{
		m_elaspedTime = 0;
	
		if (m_currentRow < m_endRow)
		{
			++m_currentRow;
			changeDrawLocation(sf::Vector2i(m_currentRow, m_column));
		}
		else
		{
			if (m_repeatable)
			{
				stop();
			}
		}
	}
}

void Animation::draw(sf::RenderWindow & window)
{
	setDrawLocation();
	m_sprite.setTextureRect(m_frame);
	window.draw(m_sprite);
}

void Animation::setDrawLocation()
{
	m_frame.left = m_currentRow * m_tileSize;
	m_frame.top = m_column * m_tileSize;
	m_frame.width = m_tileSize * m_frameSize.x;
	m_frame.height = m_tileSize * m_frameSize.y;
}

void Animation::changeDrawLocation(const sf::Vector2i newPos)
{
	m_frame.left = newPos.x;
	m_frame.top = newPos.y;
}
