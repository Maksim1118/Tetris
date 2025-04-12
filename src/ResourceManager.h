#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

enum class TextureName
{
	BACKGROUND,
	PAUSE,
	PAUSEPRESSED,
	SOUND,
	NOSOUND,
	PLAY,
	PLAYPRESSED,
	RESTART,
	RESTARTPRESSED,
	EXIT,
	EXITPRESSED
};

enum class FontName
{
	GAMEOVER,
	SCORE
};

using MapTexture = std::unordered_map<TextureName, sf::Texture*>;
using FontMap = std::unordered_map<FontName, sf::Font*>;

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	void load();
	sf::Texture& getTexture(TextureName name);
	sf::Font& getFont(FontName name);
private:
	sf::Texture* loadTexture(const std::string& path);
	sf::Font* loadFont(const std::string& path);
	ResourceManager();
	bool m_isLoad;
	MapTexture m_MapTexture;
	FontMap m_MapFont;
};