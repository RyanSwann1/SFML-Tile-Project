#include "Map\TileLayer.h"
#include "Map\WorldMap.h"
#include "Sprite\TileSheet.h"
#include <assert.h>
#include <iostream>

TileLayer::TileLayer(const TileSheetManager& tileSetManager, const TileMapData tileMapData, const sf::Vector2i mapSize, const std::string name, const std::string tileSheetName)
	: m_name(name),
	m_tileMap(loadTileMap(tileSetManager, tileMapData, mapSize, tileSheetName))
{
}

const std::vector<std::pair<int, Tile>> TileLayer::loadTileMap(const TileSheetManager & tileSetManager, const TileMapData tileMapData, const sf::Vector2i mapSize, const std::string tileSheetName) const
{
	std::vector<std::pair<int, Tile>> tileMap;
	tileMap.reserve(static_cast<size_t>(mapSize.x * mapSize.y));

	//m_tileMap.reserve(static_cast<size_t>(m_mapSize.x * m_mapSize.y));

	int row = 0, col = 0;

	for (int col = 0; col < mapSize.y; ++col)
	{
		for (int row = 0; row < mapSize.x; ++row)
		{
			//Hacky bit of code - selects for appropriate tile for drawing
			int tileID = (tileMapData[col][row]); //Get ID for tile#
			if (tileID > 0)
			{
				--tileID; //Not sure why I have to do this. Reading in the TILEID as an extra +1
				if (m_name == "Tile Layer 1")
				{
					std::cout << tileID << "\n";
				}
				//std::cout << "Tile ID: " << tileID << " ";
				const sf::Vector2i tilePosition(row, col); //Tile Position
				//const sf::IntRect drawLocation = getTileDrawLocation(tileID);

				tileMap.emplace_back(std::make_pair(convertCoords(row, col, mapSize), Tile(TileInfo(tileSetManager, tileSheetName, tileID, tilePosition))));

				//Change collision value of tile if neccessary
				//m_tileMap.emplace_back(std::make_pair(convertCoords(row, col), Tile(TileInfo(m_sharedContext.m_textureManager, m_tileSetDetails, tileID, tilePosition, drawLocation))));
			}
		}
	}
}

void TileLayer::draw(sf::RenderWindow & window)
{
	for (auto &i : m_tileMap)
	{
		window.draw(i.second.m_tileInfo.m_sprite);
	}
}

//void TileLayer::loadTileMap(const SharedContext& sharedContext, const TileMapData tileMapData, const sf::Vector2i mapSize, const std::string tileSheetName)
//{
//	std::vector<std::pair<int, Tile>> tileMap;
//	tileMap.reserve(static_cast<size_t>(mapSize.x * mapSize.y));
//
//	//m_tileMap.reserve(static_cast<size_t>(m_mapSize.x * m_mapSize.y));
//	
//	for (int col = 0; col < m_mapSize.y; ++col)
//	{
//		for (int row = 0; row < m_mapSize.x; ++row)
//		{
//			//Hacky bit of code - selects for appropriate tile for drawing
//			int tileID = (tileMapData[col][row]); //Get ID for tile#
//			if (tileID > 0)
//			{
//				--tileID; //Not sure why I have to do this. Reading in the TILEID as an extra +1
//				if (m_name == "Tile Layer 1")
//				{
//					std::cout << tileID << "\n";
//				}
//				//std::cout << "Tile ID: " << tileID << " ";
//				const sf::Vector2i tilePosition(row, col); //Tile Position
//				//const sf::IntRect drawLocation = getTileDrawLocation(tileID);
//
//				tileMap.emplace_back(std::make_pair(convertCoords(row, col), Tile(TileInfo(m_sharedContext.m_tileSheetManager, ))
//
//				//Change collision value of tile if neccessary
//				m_tileMap.emplace_back(std::make_pair(convertCoords(row, col), Tile(TileInfo(m_sharedContext.m_textureManager, m_tileSetDetails, tileID, tilePosition, drawLocation))));
//				
//			/*	if (m_tileSetDetails.m_name == "blocks1" && tileID > 0)
//				{
//					std::cout << "Tile ID: " << tileID << "\n";
//					std::cout << "Draw Location x: " << drawLocation.left << "\n";
//					std::cout << "Draw Location y: " << drawLocation.top << "\n";
//				}*/
//			//if (m_tileSetDetails.m_name == "blocks2" && tileID > 0)
//				//{
//				//	std::cout << "Tile ID: " << tileID << "\n";
//				//	std::cout << "Draw Location x: " << drawLocation.left << "\n";
//				//	std::cout << "Draw Location y: " << drawLocation.top << "\n";
//				//}
//			}
//		}
//	}
//}

//const sf::IntRect TileLayer::getTileDrawLocation(const int ID) const
//{
//	Scan through every tile on tilesheet to find appropriate tile by ID
//	int col = 0, row = 1;
//	const int firstTileID = 0;
//	const int endTileID = (m_tileSetDetails.m_numbOfRows) * (m_tileSetDetails.m_numbOfColumns);
//
//	for (int i = firstTileID; i < endTileID; ++i)
//	{
//		Appropriate tile has been found
//		if (i == ID)
//		{
//			break;
//		}
//
//		If tile not found, move onto the next tile in the row
//		++row;
//		
//		If reaching end of row, move onto the next
//		if (row == m_tileSetDetails.m_numbOfRows)
//		{
//			row = 0;
//			++col;
//		}
//	}
//
//	Get location on the tile sheet
//	const int tileSize = m_tileSetDetails.m_tileSize;
//	--row; //Not sure why I have to do this.
//	return sf::IntRect((m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + tileSize) * row)), 
//		(m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + tileSize) * col)), tileSize, tileSize); 
//
//	/*return
//	{
//		(m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + tileSize) * row),
//		(m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + tileSize) * col,
//		tileSize,
//		tileSize
//	};*/
//}