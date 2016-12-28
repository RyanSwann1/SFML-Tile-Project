#pragma once

#include "SharedContext.h"
#include "Map\TileLayer.h"
#include <vector>
#include <unordered_map>
#include <SFML\Graphics.hpp>



class WorldMap
{
public:
	WorldMap(SharedContext& sharedContext);

	void assignTileLayer(const TileLayer& newTileLayer);
	void assignCollisionLayer(const std::vector<std::vector<int>>& tileCollisionLayer);
	inline void setMapSize(const sf::Vector2f& mapSize) { m_mapSize = mapSize; }

	void changeMap();
	inline void purgeTileLayers() { m_tileLayers.clear(); }
	bool hasTileLayer(const std::string& tileLayerName);
	const sf::Vector2f& getMapSize() const { return m_mapSize; }
	void loadTileLayerMaps();

	inline static const std::string getSpriteSheetName() { return SPRITESHEET_NAME; } const
	inline static const int getTileSize() { return TILE_SIZE; }
	inline static const int getTileSetRows() { return TILE_SET_ROWS; }
	inline static const int getTileSetColumns() { return TILE_SET_COLUMNS; }
	//inline void setTileSetDetails(const TileSetDetails& tileSetDetails) { m_tileSetDetails = tileSetDetails; }
	//inline void setTileMapData(const std::vector<std::vector<int>>& tileMapdata) { m_tileMapData = tileMapdata; }
	//inline void setMapSize(const sf::Vector2i& mapSize) { m_mapSize = mapSize; }
	//void loadTileMap();

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	SharedContext& m_sharedContext;
	std::vector<std::pair<int, TileLayer>> m_tileLayers;
	std::vector<std::pair<int, TileInfo>> m_collidableTileLayer;
	int m_layerCount;
	sf::Vector2f m_mapSize;
	//std::unordered_map<int, TileInfo> m_tileSet;
	//std::vector<std::pair<int, sf::Vector2i>> m_tileSetPositions;
	//std::vector<std::vector<int>> m_tileMapData;
	//std::vector<std::pair<int, Tile>> m_tileMap;
	//std::vector<Tile> m_tileMap;
	//std::vector<std::pair<int, Tile>> m_tileMap;
	//MapDetails m_mapDetails;
	//TileSetDetails m_tileSetDetails;
	//sf::Vector2i m_mapSize;
	std::string m_name;
	static const int TILE_SIZE;
	static const int TILE_SET_ROWS;
	static const int TILE_SET_COLUMNS;
	static const std::string SPRITESHEET_NAME;
	void setCollidableTiles();
	const std::vector<sf::Vector2i> getCollidableTiles(const std::vector<std::vector<int>>& tileData) const;
};