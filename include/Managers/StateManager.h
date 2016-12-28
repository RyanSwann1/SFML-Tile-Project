#pragma once

#include "States\StateType.h"
#include "SharedContext.h"
#include <vector>
#include <list>
#include <SFML\Graphics.hpp>

//struct SharedContext;
class StateBase;
class StateGame;
class StateManager
{
public:
	friend class StateParser;
	StateManager(SharedContext& sharedContext);
	~StateManager();

	SharedContext& getSharedContext() const { return *m_sharedContext; }

	void switchTo(const StateType stateType);
	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);
	void removeState(const StateType stateType);

private:
	class StateFactory;
	const StateFactory* const m_stateFactory;
	std::vector<std::pair<StateType, StateBase*>> m_states;
	std::list<StateType> m_removals;
	StateBase* m_currentState;
	SharedContext* m_sharedContext;

	const bool createState(const StateType stateType);
	void processRemovals();
	void purgeStates();
	
	const bool removedActiveState(const StateType stateType);
};
