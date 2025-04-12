#include "ResourceManager.h"

using namespace sf;
using namespace std;

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager resManager;
	return resManager;
}

void ResourceManager::load()
{
	if (m_isLoad)
	{
		cerr << "Resources have been loaded\n";
	}
	/*m_MapTexture[TextureName::EXIT] = loadTexture("images/exit1.png");
	m_MapTexture[TextureName::EXITPRESSED] = loadTexture("images/exit2.png");
	m_MapTexture[TextureName::NOSOUND] = loadTexture("images/nosound.png");
	m_MapTexture[TextureName::SOUND] = loadTexture("images/sound.png");
	m_MapTexture[TextureName::PAUSE] = loadTexture("images/pause1.png");
	m_MapTexture[TextureName::PAUSEPRESSED] = loadTexture("images/pause2.png");
	m_MapTexture[TextureName::RESTART] = loadTexture("images/restart1.png");
	m_MapTexture[TextureName::RESTARTPRESSED] = loadTexture("images/restart2.png");*/

	m_MapFont[FontName::GAMEOVER] = loadFont("fonts/gameOverFont.ttf");
	m_MapFont[FontName::SCORE] = loadFont("fonts/scoreFont.ttf");

	m_isLoad = true;
}

Texture* ResourceManager::loadTexture(const string& path)
{
	Texture* texture = new Texture();
	if (!texture->loadFromFile(path))
	{
		cerr << "error loading texture at this path: " << path << endl;
		delete texture;
		return nullptr;
	}
	return texture;
}

sf::Font* ResourceManager::loadFont(const std::string& path)
{
	Font* font = new Font();
	if (!font->loadFromFile(path))
	{
		cerr << "error loading font at this path: " << path << endl;
		delete font;
		return nullptr;
	}
	return font;
}

Texture& ResourceManager::getTexture(TextureName name)
{
	return *m_MapTexture.at(name);
}

sf::Font& ResourceManager::getFont(FontName name)
{
	return *m_MapFont.at(name);
}

ResourceManager::ResourceManager()
	:m_isLoad(false)
{

}