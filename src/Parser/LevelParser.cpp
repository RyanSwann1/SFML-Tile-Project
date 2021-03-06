#include "Parser\LevelParser.h"
#include "Map\TileLayer.h"
#include "Entities\Entity.h"
#include "zlib.h"
#include "XML\tinystr.h"
#include "Map\WorldMap.h"
#include "Base64.h"
#include "Managers\TextureManager.h"
#include "Map\MapDetails.h"
#include "Managers\EntityManager.h"
#include "Managers\TileSheetManager.h"
#include "Sprite\TileSheetDetails.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <algorithm>

LevelParser::LevelParser(const SharedContext & sharedContext)
	: m_sharedContext(sharedContext)
{}

void LevelParser::parseLevel(const std::string & levelName)
{
	//Load XML file
	TiXmlDocument levelDocument;
	assert(levelDocument.LoadFile(levelName.c_str()));

	//Get root node of the level object
	const TiXmlElement& rootNode = *levelDocument.RootElement();

	//make for loop
	//Count how many tile layers  there are on each map
	//Load each tile layer into the world map

	//Create level
	const LevelDetails levelDetails = parseLevelDetails(rootNode);
	parseTileMap(rootNode, levelDetails);
	parseCollidableLayer(rootNode, levelDetails);
	m_sharedContext.m_worldMap.loadTileLayerMaps(); //Load all maps that have been parsed
	m_sharedContext.m_worldMap.setMapSize((sf::Vector2f(levelDetails.m_width, levelDetails.m_height)));

	//Load in objects
	//parseObjects(rootNode);

	//Fix when multiple tile layers are being loaded into the program at once - Most probably the same ones 
}

//Use for parsing object textures - not possibly needed will have to see further into development
void LevelParser::parseTextures(const TiXmlElement & root)
{
	TextureManager& textureManager = m_sharedContext.m_textureManager;
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == "property")
		{
			textureManager.registerFilePath(e->Attribute("name"), e->Attribute("value"));
		}
	}
}

void LevelParser::parseObjects(const TiXmlElement & root)
{
	EntityManager& entityManager = m_sharedContext.m_entityManager;
	const TiXmlElement& objectRoot = *findNode(root, "objectgroup");
	for (const TiXmlElement* e = objectRoot.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		const std::string type(e->Attribute("name"));
		int xPos = 0, yPos = 0;
		e->Attribute("x", &xPos);
		e->Attribute("y", &yPos);

		std::cout << type << "\n";
		entityManager.addEntity(type, sf::Vector2f(xPos, yPos));
	}
}

void LevelParser::parseTileLayer(const TiXmlElement & tileLayerElement, const LevelDetails& levelDetails, const std::string tileSheetName, const std::string& name)
{
	
	const std::vector<std::vector<int>> tileData = decodeTileLayer(tileLayerElement, levelDetails);
	
	TileLayer tileLayer(m_sharedContext.m_tileSheetManager, tileData, sf::Vector2i(levelDetails.m_width, levelDetails.m_height), name, tileSheetName);
	//TileLayer tileLayer(m_sharedContext, tileData, sf::Vector2i(levelDetails.m_width, levelDetails.m_height), tileSetDetails, name);
	m_sharedContext.m_worldMap.assignTileLayer(tileLayer);
}

void LevelParser::parseCollidableLayer(const TiXmlElement & root, const LevelDetails& levelDetails)
{
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer") && e->Attribute("name") == std::string("Collidable"))
		{
			const std::string layerName = e->Attribute("name");
			const std::vector<std::vector<int>> tileData = decodeTileLayer(*e, levelDetails);

			m_sharedContext.m_worldMap.assignCollisionLayer(tileData);
		}
	}
}

const LevelDetails LevelParser::parseLevelDetails(const TiXmlElement & root) const
{
	int width = 0, height = 0, tileSize = 0;
	root.Attribute("width", &width);
	root.Attribute("height", &height);
	root.Attribute("tilewidth", &tileSize);

	return LevelDetails(tileSize, width, height);
}

const TiXmlElement * LevelParser::findNode(const TiXmlElement& root, const std::string & name) const
{
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == name)
		{
			return e;
		}
	}
	return nullptr;
}

const std::vector<std::vector<int>> LevelParser::decodeTileLayer(const TiXmlElement & tileLayerElement, const LevelDetails & levelDetails) const
{
	std::vector<std::vector<int>> tileData;

	std::string decodedIDs; //Base64 decoded information
	const TiXmlElement* dataNode = nullptr; //Store our node once we find it
	for (const TiXmlElement* e = tileLayerElement.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			dataNode = e;
		}
	}

	Base64 base64;
	//Get the text from within the node and use base64 to decode it
	for (const TiXmlNode* e = dataNode->FirstChild(); e != nullptr; e = e->NextSibling())
	{
		const TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64.base64_decode(t);
	}

	uLongf sizeOfIDs = levelDetails.m_width * levelDetails.m_height * sizeof(int);
	std::vector<int> ids(levelDetails.m_width * levelDetails.m_height);

	uncompress((Bytef*)&ids[0], &sizeOfIDs, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(levelDetails.m_width);
	for (int i = 0; i < levelDetails.m_height; ++i)
	{
		tileData.push_back(layerRow);
	}

	for (int rows = 0; rows < levelDetails.m_height; ++rows)
	{
		for (int cols = 0; cols < levelDetails.m_width; ++cols)
		{
			tileData[rows][cols] = ids[rows * levelDetails.m_width + cols];
		}
	}

	return tileData;
}

const int LevelParser::getNumberOfTileLayers(const TiXmlElement & root) const
{
	int tileLayerCount = 0;
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			++tileLayerCount;
		}
	}
	return tileLayerCount;
}

const int LevelParser::getNumberOfTileSets(const TiXmlElement & root) const
{
	int tileSetCount = 0;
	const TiXmlElement& tileSetNode = *findNode(root, "tileset");
	for (const TiXmlElement* e = &tileSetNode; e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset") && e->Attribute("name") != std::string("Collidable"))
		{
			++tileSetCount;
		}
	}
	return tileSetCount;
}

void LevelParser::parseTileSet(const TiXmlElement & root)
{
	bool continueSearching = true;
	const TiXmlElement* tileSetNode = findNode(root, "tileset");
	while (continueSearching)
	{
		if (tileSetNode->Value() == std::string("tileset") && tileSetNode->Attribute("name") != std::string("Collidable")) 
		{
			//Register the tile set texture
			const TiXmlElement* const imgRoot = tileSetNode->FirstChildElement("image");
			if (imgRoot)
			{
				const std::string tileSetFileName = tileSetNode->Attribute("name");
				const std::string tileSetSource = imgRoot->Attribute("source");
				TextureManager& textureManager = m_sharedContext.m_textureManager;
				textureManager.registerFilePath(tileSetFileName, imgRoot->Attribute("source"));
			}

			sf::Vector2i pos, tileSetSize;
			int spacing = 0, margin = 0, firstGridID = 0, tileSize = 0;
			//Load in values
			tileSetNode->FirstChildElement()->Attribute("width", &tileSetSize.x);
			tileSetNode->FirstChildElement()->Attribute("height", &tileSetSize.y);
			tileSetNode->Attribute("firstgid", &firstGridID);
			tileSetNode->Attribute("tilewidth", &tileSize);
			tileSetNode->Attribute("spacing", &spacing);
			tileSetNode->Attribute("margin", &margin);
			const std::string name = tileSetNode->Attribute("name");
			const int numbOfRows = tileSetSize.x / (tileSize + spacing);
			const int numbOfColumns = tileSetSize.y / (tileSize + spacing);

			const TileSheetDetails tileSheetDetails(name, tileSize, numbOfRows, numbOfColumns, margin, spacing);
			m_sharedContext.m_tileSheetManager.addTileSheet(m_sharedContext.m_textureManager, tileSheetDetails);
		}
		
		//Change to the next tileset
		if (tileSetNode->NextSiblingElement())
		{
			tileSetNode = tileSetNode->NextSiblingElement();
		}
		else
		{
			continueSearching = false;
		}
	}
}

void LevelParser::parseTileMap(const TiXmlElement & root, const LevelDetails & levelDetails)
{
	const int tileLayerCount = getNumberOfTileLayers(root);
	const TiXmlElement* tileLayerNode = findNode(root, "layer"); //Get the first layer node

	for (int i = 1; i <= tileLayerCount; ++i)
	{
		//If node in question is a layer 
		if (tileLayerNode->Value() == std::string("layer") &&
			tileLayerNode->Attribute("name") == std::string("Tile Layer " + std::to_string(i)))
		{
			const std::string tileLayerName = tileLayerNode->Attribute("name");

			if (tileLayerNode->FirstChildElement()->Value() == std::string("data") ||
				tileLayerNode->FirstChildElement()->NextSiblingElement() != 0 && tileLayerNode->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))
			{
				if (!m_sharedContext.m_worldMap.hasTileLayer(tileLayerName))
				{	
					//Find correct tilesheet that corresponds with this tile layer
					if (tileLayerNode->FirstChildElement()->Value() == std::string("properties"))
					{
						const TiXmlElement& tileLayerProperty = *tileLayerNode->FirstChildElement()->FirstChildElement();
						const std::string tileSheetName = tileLayerProperty.Attribute("value");
						const TileSheet* const tileSheet = m_sharedContext.m_tileSheetManager.getTileSheet(tileSheetName);
						if (tileSheet)
						{
							parseTileLayer(*tileLayerNode, levelDetails, tileSheet->getDetails().m_name, tileLayerName);
						}
						else
						{
							assert(tileSheet);
						}
					}

					////If only one tile set exists
					//if (tileSets.size() == static_cast<size_t>(1))
					//{
					//	std::cout << tileLayerName << "\n";
					//	parseTileLayer(*tileLayerNode, levelDetails, *tileSets.begin(), tileLayerName);
					//}
					////If more than one tile set exists
					//else
					//{
					//	if (tileLayerNode->FirstChildElement()->Value() == std::string("properties"))
					//	{
					//		const TiXmlElement& tileLayerProperty = *tileLayerNode->FirstChildElement()->FirstChildElement();
					//		const std::string tileSetName = tileLayerProperty.Attribute("value");
					//		auto cIter = std::find_if(tileSets.cbegin(), tileSets.cend(), [tileSetName](const TileSetDetails& tileSetDetails) {return tileSetDetails.m_name == tileSetName; });
					//		if (cIter != tileSets.cend())
					//		{
					//			std::cout << "Tile Layer " << i << "\n";
					//			parseTileLayer(*tileLayerNode, levelDetails, *cIter->, tileLayerName);
					//		}
					//	}
					//}
				}
			}
		}
		if (tileLayerNode->NextSiblingElement())
		{
			//Go to the next layer
			tileLayerNode = tileLayerNode->NextSiblingElement(); 
		}
		
	}
}