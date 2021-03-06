#pragma once

#include "StateType.h"
#include "Managers\StateManager.h"
#include <SFML\Graphics.hpp>

class StateBase
{
public:
	StateBase(StateManager& stateManager, const StateType type)
		: m_stateManager(stateManager),
		m_stateType(type)
	{}

	const StateType getStateType() const { return m_stateType; }
	const sf::View& getView() const { return m_view; }

	virtual void onEnter() {}
	virtual void onExit() {}

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	StateManager& getStateManager() { return m_stateManager; }

private:
	sf::View m_view;
	const StateType m_stateType;
	StateManager& m_stateManager;
};