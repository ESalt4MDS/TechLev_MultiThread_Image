#pragma once
#include <vector>
#include <string>
#include <thread>
#include "SFML/Graphics.hpp"

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
	void ThreadLoadImages(int _image);


	void DrawImages(sf::RenderWindow &_window);

private:

	std::vector<std::string> m_fileNames;
	std::vector<sf::Texture*> m_textures;
	std::vector<sf::Sprite*> m_imageSprites;
	std::vector<std::thread*> m_threads;

};
