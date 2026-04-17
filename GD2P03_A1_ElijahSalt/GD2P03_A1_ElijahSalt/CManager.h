#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <iostream>
#include "CThreadPool.h"
#include "CImageLoader.h"

class CManager
{
public:
	CManager();
	~CManager();

	void Initialize();
	
	void RunProgram();
	void Draw();

	void SaveImage();

private:
	sf::RenderWindow* m_window;
	CImageLoader* m_loader;
};

