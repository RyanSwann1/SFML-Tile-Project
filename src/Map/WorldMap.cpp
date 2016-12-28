#include "Map\WorldMap.h"
#include <iostream>
#include <algorithm>

const int WorldMap::TILE_SIZE = 16;
const int WorldMap::TILE_SET_ROWS = 64;
const int WorldMap::TILE_SET_COLUMNS = 108;
const std::string WorldMap::SPRITESHEET_NAME = "Kenney_16x16";

WorldMap::WorldMap(SharedContext & sharedContext)
	: m_sharedContext(sharedContext),
	m_layerCount(0)
{
}

void WorldMap::assignTileLayer(const TileLayer & newTileLayer)
{
	if (!hasTileLayer(newTileLayer.getName()))
	{
		m_tileLayers.push_back(std::make_pair(m_layerCount, newTileLayer));
		++m_layerCount;
	}
}

void WorldMap::assignCollisionLayer(const std::vector<std::vector<int>>& tileCollisionLayer)
{
	if (m_tileLayers.empty())
	{
		return;
	}

	const TileLayer& tileLayer = m_tileLayers.begin()->second;
	const std::vector<sf::Vector2i> collidableTiles = getCollidableTiles(tileCollisionLayer);
	std::vector<std::pair<int, Tile>>& tileMap = tileLayer.m_tileMap;
	
	for (auto &tile : tileMap)
	{
		const sf::Vector2i& tilePos = tile.second.m_tileInfo.m_position;
		auto cIter = std::find_if(collidableTiles.cbegin(), collidableTiles.cend(), [tilePos](const sf::Vector2i& collidableTilePos) {return collidableTilePos == tilePos; });
		if (cIter != collidableTiles.cend())
		{
			tile.second.m_collidable = true;
		}
	}
}

void WorldMap::changeMap()
{
	
}

bool WorldMap::hasTileLayer(const std::string& tileLayerName)
{
	if (std::find_if(m_tileLayers.cbegin(), m_tileLayers.cend(), [tileLayerName](const std::pair<int, TileLayer>& tileLayer) {return tileLayer.second.getName() == tileLayerName; }) != m_tileLayers.cend())
	{
		return true;
	}
	return false;
}

void WorldMap::loadTileLayerMaps()
{
	for (auto &i : m_tileLayers)
	{
		i.second.loadTileMap();
	}
}

void WorldMap::update(const float deltaTime)
{

}

void WorldMap::draw(sf::RenderWindow & window)
{
	for (auto &i : m_tileLayers)
	{
		i.second.draw(window);
	}
} 

//
//void WorldMap::loadTileMap()
//{
//	m_tileMap.reserve(static_cast<size_t>(m_mapSize.x * m_mapSize.y));
//
//	for (int col = 0; col < m_mapSize.y; ++col)
//	{
//		for (int row = 0; row < m_mapSize.x; ++row)
//		{
//			const int tileID = m_tileMapData[col][row]; //Get ID for tile
//			if (tileID > 0)
//			{
//				const sf::Vector2i tilePosition(row, col); //Tile Position
//				const sf::IntRect drawLocation = getTileIDDrawLocation(tileID);
//
//				Tile tile(TileInfo(m_sharedContext.m_textureManager, m_tileSetDetails, tileID, tilePosition, drawLocation));
//				//Change collision value of tile if neccessary
//				m_tileMap.emplace_back(tile);
//			}
//		}
//	}
//
//	//for (int col = 0; col < m_tileSetDetails.m_numbOfColumns; ++col)
//	//{
//	//	for (int row = 0; row < m_tileSetDetails.m_numbOfRows; ++row)
//	//	{
//	//		
//	//		
//	//	}
//	//}
//	std::cout << "Hi\n";
//}

//const sf::IntRect WorldMap::getTileIDDrawLocation(const int ID) const
//{
//	////Tile ID is out of bounds
//	//if (ID < 0 || ID > (m_tileSetDetails.m_numbOfColumns * m_tileSetDetails.m_numbOfRows))
//	//{
//	//	return;
//	//}
//
//	//Scan through every tile on tilesheet to find appropriate tile by ID
//	int col = 0, row = 0, firstGridID = 1;
//	const int endTilePos = m_tileSetDetails.m_numbOfColumns * m_tileSetDetails.m_numbOfRows;
//	for (int i = firstGridID; i < endTilePos; ++i)
//	{
//		//Appropriate tile has been found
//		if (i == ID)
//		{
//			break;
//		}
//
//		++row;
//		if (row >= m_tileSetDetails.m_numbOfRows)
//		{
//			row = 0;
//			++col;
//		}
//	}
//
//	//Draw location
//	//return sf::IntRect((m_tileSetDetails.m_spacing + (row * m_tileSetDetails.m_tileSize)), //Draw location on X Axis
//	//	(m_tileSetDetails.m_spacing + (col * m_tileSetDetails.m_tileSize)), //Draw location on Y Axis
//	//	m_tileSetDetails.m_tileSize, m_tileSetDetails.m_tileSize); //Draw Location size
//
//	//Draw location on the tile sheet
//	return sf::IntRect((m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + m_tileSetDetails.m_tileSize) * row)), //Draw location on X Axis
//						(m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + m_tileSetDetails.m_tileSize) * col)), //Draw location on Y Axis
//						m_tileSetDetails.m_tileSize, m_tileSetDetails.m_tileSize); //Draw Location size
//}

void WorldMap::setCollidableTiles()
{
}

const std::vector<sf::Vector2i> WorldMap::getCollidableTiles(const std::vector<std::vector<int>>& tileData) const
{
	std::vector<sf::Vector2i> collidableTiles;

	for (int col = 0; col < m_mapSize.y; ++col)
	{
		for (int row = 0; row < m_mapSize.x; ++row)
		{
			//Note to self - hacky need to change
			if (tileData[col][row] == 199)
			{
				collidableTiles.push_back(sf::Vector2i(row, col));
			}
		}
	}

	return collidableTiles;
}