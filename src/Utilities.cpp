#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>

Utilities::Utilities() 
	: m_entityDetails(loadInDetails("Assets/EntityDetails.txt"))
{
}

const std::string & Utilities::getSpriteSheetDetails(const std::string & id) const
{
	auto cIter = m_spriteSheetDetails.find(id);
	if (cIter != m_spriteSheetDetails.cend())
	{
		return cIter->second;
	}
}

const std::string & Utilities::getEntityDetails(const std::string & id) const
{
	auto cIter = m_entityDetails.find(id);
	if (cIter != m_entityDetails.cend())
	{
		return cIter->second;
	}
}

void Utilities::registerSpriteSheetDetails(const std::string& name, const std::string& location)
{
	assert(m_spriteSheetDetails.emplace(name, location).second);
}

void Utilities::registerEntityDetails(const std::string& name, const std::string& location)
{
	assert(m_spriteSheetDetails.emplace(name, location).second);
}

const std::unordered_map<std::string, std::string> Utilities::loadInDetails(const std::string & fileName) const
{
	std::fstream file(fileName);
	assert(file.is_open());
	std::unordered_map<std::string, std::string> container;

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '/')
		{
			continue;
		}
		std::stringstream keyStream(line);
		std::string name;
		std::string location;

		keyStream >> name >> location;
		std::cout << name << "\n";
		std::cout << location << "\n";
		assert(container.emplace(name, location).second);
	}

	return container;
}