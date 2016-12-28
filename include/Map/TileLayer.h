#pragma once

#include "SharedContext.h"
#include "Tile.h"
#include "Sprite\TileSheetDetails.h"
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

using TileMapData = std::vector<std::vector<int>>;

class TileSheetManager;
class TileLayer
{
	friend class WorldMap;
public:
	TileLayer(const TileSheetManager& tileSetManager, const TileMapData tileMapData, 
		const sf::Vector2i mapSize, const std::string name, const std::string tileSheetName);

	const std::string& getName() const { return m_name; }
	const std::vector<std::pair<int, Tile>>& getTileMap() const { return m_tileMap; }
	const std::vector<std::pair<int, Tile>> loadTileMap(const TileSheetManager& tileSetManager, const TileMapData tileMapData, 
	const sf::Vector2i mapSize, const std::string tileSheetName) const;

	void draw(sf::RenderWindow& window);

private:
	//const std::vector<std::vector<int>> m_tileMapData;
	const std::vector<std::pair<int, Tile>> m_tileMap;
	const std::string m_name;
	inline const int convertCoords(const int x, const int y, const sf::Vector2i& mapSize ) const { return (x * mapSize.x) + y; }
};