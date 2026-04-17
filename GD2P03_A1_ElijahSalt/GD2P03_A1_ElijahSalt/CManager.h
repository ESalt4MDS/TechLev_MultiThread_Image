//************************************************************************
//Bachelor of Software Engineering
//Media Design School
//Auckland
//New Zealand
//
//File Name : [CManager.h]
//Description : [handles program flow and input]
//Author : [Elijah Salt]
//Email : [elijah.salt@mds.ac.nz]
//
//(c) Elijah Salt
//************************************************************************

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

	/*
	* setup member variables
	Parameters:

	Returns:
	- void
	*/
	void Initialize();
	
	/*
	* run the program every frame
	Parameters:

	Returns:
	- void
	*/
	void RunProgram();

	/*
	* draw calls to the window
	Parameters:

	Returns:
	- void
	*/
	void Draw();

	/*
	* save the window to a .png
	Parameters:

	Returns:
	- void
	*/
	void SaveImage();

private:
	sf::RenderWindow* m_window;
	CImageLoader* m_loader;
};

