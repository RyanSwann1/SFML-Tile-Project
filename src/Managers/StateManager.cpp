#include "Managers\StateManager.h"
#include "States\StateBase.h"
#include "States\StateGame.h"
#include "States\StateMainMenu.h"
#include <assert.h>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <assert.h>

class StateManager::StateFactory
{
public:
	StateFactory(StateManager* stateManager)
	{
		registerState<StateGame>(StateType::Game, stateManager);
		registerState<StateMainMenu>(StateType::MainMenu, stateManager);
	}

	StateBase* createState(const StateType stateType) const
	{
		auto cIter = m_stateFactory.find(stateType);
		if (cIter != m_stateFactory.cend())
		{
			return cIter->second();
		}
		return nullptr;
	}

	template <class T>
	void registerState(const StateType stateType, StateManager* stateManager) 
	{
		if (m_stateFactory.find(stateType) == m_stateFactory.cend())
		{
			m_stateFactory.emplace(std::make_pair(stateType, [stateType, stateManager]() -> StateBase*
			{
				return new T(*stateManager, stateType);
			}));
		}
	}

private:
	std::unordered_map<StateType, std::function<StateBase*()>> m_stateFactory;
};

StateManager::StateManager(SharedContext & sharedContext)
	: m_currentState(nullptr),
	m_stateFactory(new StateFactory(this)),
	m_sharedContext(&sharedContext)
{
}

StateManager::~StateManager()
{
	purgeStates();
	delete m_stateFactory;
}

void StateManager::switchTo(const StateType stateType)
{
	if (m_currentState)
	{
		m_currentState->onExit();
	}

	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == stateType)
		{
			m_currentState = iter->second;
			m_currentState->onEnter();
			return;
		}
	}

	//If state not found to switch to, create one and switch to it
	assert(createState(stateType));
}

void StateManager::removeState(const StateType stateType)
{
	if (std::find(m_removals.cbegin(), m_removals.cend(), stateType) == m_removals.cend())
	{
		m_removals.push_back(stateType);
	}
}

void StateManager::update(const float deltaTime)
{
	auto statesCopy = m_states;
	for (auto &i : statesCopy)
	{
		i.second->update(deltaTime);
	}

	processRemovals();
}

void StateManager::draw(sf::RenderWindow& window)
{
	for (const auto &i : m_states)
	{
		i.second->draw(window);
	}
}

const bool StateManager::createState(const StateType stateType)
{
	StateBase* state = m_stateFactory->createState(stateType);
	if (state)
	{
		m_states.emplace_back(std::make_pair(stateType, state));
		state->onEnter();
		m_currentState = state;
		return true;
	}
	return false;
}

void StateManager::processRemovals()
{
	for (auto iter = m_removals.begin(); iter != m_removals.end();)
	{
		if (removedActiveState(*iter))
		{
			iter = m_removals.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

const bool StateManager::removedActiveState(const StateType stateType)
{
	auto iter = std::find_if(m_states.begin(), m_states.end(), [stateType](const std::pair<StateType, StateBase*>& state) {return state.first == stateType; });
	if (iter != m_states.cend())
	{
		delete iter->second;
		iter->second = nullptr;
		m_states.erase(iter);
		return true;
	}
	return false;
}

void StateManager::purgeStates()
{
	for (auto &i : m_states)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_states.clear();
}