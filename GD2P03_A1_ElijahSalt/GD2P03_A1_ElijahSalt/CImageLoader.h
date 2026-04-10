#pragma once
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"

class CImageLoader
{
public:
	CImageLoader();
	~CImageLoader();

	void LoadFiles();
	void LoadImages();

	void DrawImages(sf::RenderWindow &_window);


private:

	std::vector<std::string> m_fileNames;
	std::vector<sf::Texture*> m_textures;
	std::vector<sf::Sprite*> m_imageSprites;

};
