#include "CImageLoader.h"
#include <iostream>

CImageLoader::CImageLoader()
{
}

CImageLoader::~CImageLoader()
{
    for (auto iter : m_textures)
    {
        delete iter;
        iter = nullptr;
    }

    for (auto iter : m_imageSprites)
    {
        delete iter;
        iter = nullptr;
    }
}

void CImageLoader::LoadFiles()
{
    std::string path = std::filesystem::current_path().string();
    path.append("\\small set");
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        m_fileNames.push_back(entry.path().string());
    }

    for (auto iter : m_fileNames)
    {
        std::cout << iter << std::endl;
    }

    LoadImages();
}

void CImageLoader::LoadImages()
{
    for (int i = 0; i < m_fileNames.size(); i++)
    {
        //load texture with the image and store texture in vector
        sf::Texture* texture = new sf::Texture(m_fileNames[i]);
        m_textures.push_back(texture);

        //create sprite to hold texture to display to screen and store sprite in vector
        sf::Sprite* sprite = new sf::Sprite(*texture);
        m_imageSprites.push_back(sprite);
    }
}

void CImageLoader::DrawImages(sf::RenderWindow& _window)
{
    for (int i = 0; i < m_imageSprites.size(); i++)
    {
        _window.draw(*m_imageSprites[i]);
    }
}


