#pragma once

#include "Sprite\TileSheet.h"
#include <string>
#include <unordered_map>

struct TileSheetDetails;
class TextureManager;
class TileSheetManager
{
public:

	TileSheet* const getTileSheet(const std::string name);

	void addTileSheet(TextureManager& textureManager, const TileSheetDetails tileSheetDetails);

private:
	std::unordered_map<std::string, TileSheet> m_tileSheets;
};