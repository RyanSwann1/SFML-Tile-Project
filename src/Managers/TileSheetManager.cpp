#include "Managers\TileSheetManager.h"

TileSheet * const TileSheetManager::getTileSheet(const std::string name)
{
	auto cIter = m_tileSheets.find(name);
	if (cIter != m_tileSheets.cend())
	{
		return &cIter->second;
	}

	return nullptr;
}

void TileSheetManager::addTileSheet(TextureManager & textureManager, const TileSheetDetails tileSheetDetails)
{
	if (m_tileSheets.find(tileSheetDetails.m_name) != m_tileSheets.cend())
	{
		m_tileSheets.emplace(std::make_pair(tileSheetDetails.m_name, TileSheet(textureManager, tileSheetDetails)));
	}
}
