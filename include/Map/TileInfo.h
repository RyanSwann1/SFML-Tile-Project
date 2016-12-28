#pragma once

#include "Managers\TextureManager.h"
#include "Map\TileSetDetails.h"
#include "Sprite\TileSheet.h"
#include "Managers\TileSheetManager.h"
#include "SharedContext.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <assert.h>

struct TileInfo
{
	//Constructor
	TileInfo(SharedContext& sharedContext, const std::string tileSheetName, const int tileID, const sf::Vector2i& position)
		: m_tileID(tileID),
		m_position(position),
		m_tileSheet(nullptr)
	{
		auto tileSheet = sharedContext.m_tileSheetManager.getTileSheet(tileSheetName);
		if (tileSheet)
		{
			m_tileSheet = tileSheet;
			m_sprite.setTexture(*tileSheet->getTexture());
			m_sprite.setTextureRect(tileSheet->getTileLocationByID(tileID));
		}
		else
		{
			assert(tileSheet);
		}

		m_sprite.setPosition(sf::Vector2f(position.x, position.y));
	}

	//Copy Constructor
	TileInfo(const TileInfo& orig)
		: m_position(orig.m_position),
		m_sprite(orig.m_sprite),
		m_tileID(orig.m_tileID)
	{	
		m_sprite.setTexture(*orig.m_tileSheet->getTexture());
	}

	//Destructor
	~TileInfo()
	{
		m_tileSheet->releaseTileSheet();
	}
	
	sf::Vector2i m_position;
	TileSheet* m_tileSheet;
	sf::Sprite m_sprite;
	const int m_tileID;
};