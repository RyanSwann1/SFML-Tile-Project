#pragma once

#include "SharedContext.h"
#include "XML\tinyxml.h"

#include <vector>
#include <string>

struct TileSetDetails;
struct MapDetails;
class Level;
class EntityLayer;
class TileLayer;

struct LevelDetails
{
	LevelDetails(const int tileSize, const int width, const int height)
		: m_tileSize(tileSize),
		m_width(width),
		m_height(height)
	{}

	const int m_tileSize;
	const int m_height;
	const int m_width;
};

class LevelParser
{
public:
	LevelParser(const SharedContext& sharedContext);

	void parseLevel(const std::string& levelName);

private:
	SharedContext m_sharedContext;

	void parseTextures(const TiXmlElement& root);
	void parseTileSet(const TiXmlElement& root);
	void parseTileMap(const TiXmlElement& root, const LevelDetails& levelDetails);
	void parseObjects(const TiXmlElement& root);
	void parseTileLayer(const TiXmlElement& root, const LevelDetails& levelDetails, const std::string tileSheetName, const std::string& name);
	void parseCollidableLayer(const TiXmlElement& root, const LevelDetails& levelDetails);
	const LevelDetails parseLevelDetails(const TiXmlElement& root) const;

	const TiXmlElement* findNode(const TiXmlElement& root, const std::string& name) const;
	const std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement& tileLayerElement, const LevelDetails& levelDetails) const;
	const int getNumberOfTileLayers(const TiXmlElement& root) const;
	const int getNumberOfTileSets(const TiXmlElement& root) const;
};