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
	m_MapTexture[TextureName::EXIT] = loadTexture("images/exit.png");
	m_MapTexture[TextureName::EXITPRESSED] = loadTexture("images/exitPressed.png");
	m_MapTexture[TextureName::NOSOUND] = loadTexture("images/nosound.png");
	m_MapTexture[TextureName::SOUND] = loadTexture("images/sound.png");
	m_MapTexture[TextureName::PLAY] = loadTexture("images/play.png");
	m_MapTexture[TextureName::PLAYPRESSED] = loadTexture("images/playPressed.png");
	m_MapTexture[TextureName::RESTART] = loadTexture("images/restart.png");
	m_MapTexture[TextureName::RESTARTPRESSED] = loadTexture("images/restartPressed.png");

	m_MapSound[SoundName::BACK_GROUND] = loadSound("sounds/backSound.mp3");
	m_MapSound[SoundName::DROP] = loadSound("sounds/sendTet.mp3");
	m_MapSound[SoundName::MOVE] = loadSound("sounds/moveTet.mp3");
	m_MapSound[SoundName::ROTATE] = loadSound("sounds/rotateTet.mp3");
	m_MapSound[SoundName::CLEARLINE] = loadSound("sounds/clearLine.mp3");
	m_MapSound[SoundName::GAMEOVER] = loadSound("sounds/gameOver.mp3");

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

sf::Music* ResourceManager::loadSound(const std::string& path)
{
	Music* music = new Music();
	if (!music->openFromFile(path))
	{
		cerr << "error open music at this path: " << path << endl;
		delete music;
		return nullptr;
	}
	return music;
}

Texture& ResourceManager::getTexture(TextureName name)
{
	return *m_MapTexture.at(name);
}

sf::Font& ResourceManager::getFont(FontName name)
{
	return *m_MapFont.at(name);
}

sf::Music& ResourceManager::getSound(SoundName name)
{
	return *m_MapSound.at(name);
}

ResourceManager::ResourceManager()
	:m_isLoad(false)
{

}