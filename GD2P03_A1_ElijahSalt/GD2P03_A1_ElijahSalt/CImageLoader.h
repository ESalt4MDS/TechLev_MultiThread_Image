#pragma once
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "CThreadPool.h"

enum SetType
{
	SMALL,
	LARGE
};

class CImageLoader
{
public:
	CImageLoader();
	~CImageLoader();

	void LoadFiles(SetType _set);
	void LoadImages();


	void DrawImages(sf::RenderWindow &_window);

private:

	std::vector<std::wstring> m_fileNames;
	std::vector<sf::Texture*> m_textures;
	std::vector<sf::Sprite*> m_imageSprites;

};
