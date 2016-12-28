#pragma once

#include "SharedContext.h"
#include "Managers\TextureManager.h"
#include "Entities\EntityState.h"
#include "Sprite\Animation.h"
#include "Sprite\TileSheetDetails.h"

#include <unordered_map>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

//Class to be used to interact with the spritesheet

class TileSheet
{
public:
	TileSheet(TextureManager& textureManager, const TileSheetDetails details);

	TileSheet(const TileSheet&) = delete;
	TileSheet& operator=(const TileSheet&) = delete;
	
	const sf::Texture* getTexture() const;
	const TileSheetDetails& getDetails() const { return m_details; }
	const sf::IntRect getTileLocationByID(const int ID) const;
	void releaseTileSheet(); //Maybe implement

private:
	TextureManager& m_textureManager;
	const TileSheetDetails m_details;
	//sf::Sprite m_tileSheet;
};