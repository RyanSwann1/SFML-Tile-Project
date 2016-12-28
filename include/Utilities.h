#pragma once

#include <string>
#include <unordered_map>

class Utilities
{
public:
	Utilities();

	const std::string& getSpriteSheetDetails(const std::string& id) const;
	const std::string& getEntityDetails(const std::string& id) const;

private:
	std::unordered_map<std::string, std::string> m_spriteSheetDetails;

	const std::unordered_map<std::string, std::string> m_entityDetails;
	const std::unordered_map<std::string, std::string> loadInDetails(const std::string& fileName) const;
	void registerSpriteSheetDetails(const std::string& name, const std::string& location);
	void registerEntityDetails(const std::string& name, const std::string& location);
};