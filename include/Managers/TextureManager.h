#pragma once

#include "Managers\ResourceManager.h"
#include <SFML\Graphics.hpp>

class TextureManager : public ResourceManager<sf::Texture>
{
public:
	TextureManager()
	{
	}

	~TextureManager()
	{}

private:
	sf::Texture* loadFromFile(const std::string& fileName) override
	{
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromFile(fileName))
		{
			delete texture;
			texture = nullptr;
			return nullptr;
		}
		return texture;
	}
};