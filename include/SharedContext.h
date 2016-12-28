#pragma once

class TextureManager;
class EntityManager;
class StateManager;
class WorldMap;
class Utilities;
class TileSheetManager;
struct SharedContext
{
	SharedContext(StateManager& stateManager, TextureManager& textureManager, WorldMap& worldMap, EntityManager& entityManager, const Utilities& utilities, TileSheetManager& tileSheetManager)
		: m_entityManager(entityManager),
		m_worldMap(worldMap),
		m_stateManager(stateManager),
		m_textureManager(textureManager),
		m_utilities(utilities),
		m_tileSheetManager(tileSheetManager)
	{ 
	}

	TextureManager& m_textureManager;
	EntityManager& m_entityManager;
	StateManager& m_stateManager;
	WorldMap& m_worldMap;
	const Utilities& m_utilities;
	TileSheetManager& m_tileSheetManager;
};