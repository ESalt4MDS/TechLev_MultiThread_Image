//************************************************************************
//Bachelor of Software Engineering
//Media Design School
//Auckland
//New Zealand
//
//File Name : [CImageLoader.h]
//Description : [loads images from files and draws]
//Author : [Elijah Salt]
//Email : [elijah.salt@mds.ac.nz]
//
//(c) Elijah Salt
//************************************************************************

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

	/*
	* load the files paths into a std::vector
	Parameters:
	- SetType _set: an enum of the set to load
	Returns:
	- void
	*/
	void LoadFiles(SetType _set);

	/*
	* load the images into a sprite
	Parameters:

	Returns:
	- void
	*/
	void LoadImages();

	/*
	* setup image positions into a grid 
	Parameters:

	Returns:
	- void
	*/
	void SetupImageGrid();

	/*
	* draw images to window
	Parameters:

	Returns:
	- void
	*/
	void DrawImages(sf::RenderWindow* _window);

private:

	std::vector<std::wstring> m_fileNames;
	std::vector<sf::Texture*> m_textures;
	std::vector<sf::Sprite*> m_imageSprites;
	std::vector<sf::Vector2f*> m_imagePositions;
	std::vector< sf::Sprite*> m_imagesInGrid;

};
