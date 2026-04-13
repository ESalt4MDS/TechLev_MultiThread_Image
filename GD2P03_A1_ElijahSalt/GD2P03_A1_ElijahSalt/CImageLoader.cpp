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

void CImageLoader::LoadFiles(SetType _set)
{
    std::string path = std::filesystem::current_path().string();

    switch (_set)
    {
        case SetType::SMALL:
            path.append("\\small set");
            break;
        case SetType::LARGE:
            path.append("\\large set");
            break;
        default:
            break;
    }

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        m_fileNames.push_back(entry.path().string());
    }

    /*for (auto iter : m_fileNames)
    {
        std::cout << iter << std::endl;
    }*/

    /*for (int i = 0; i < m_fileNames.size(); i++)
    {
        std::thread* thread = new std::thread(&CImageLoader::ThreadLoadImages, i);
        m_threads.push_back(thread);
    }

    for (auto& iter : m_threads)
    {
        if (iter->joinable())
        {
            iter->join();
        }
    }*/

    LoadImages();
}

void CImageLoader::LoadImages()
{
    for (int i = 0; i < m_fileNames.size(); i++)
    {
        //load texture with the image and store texture in vector
        sf::Texture* texture = new sf::Texture(m_fileNames[i]);
        float scaleX = 200.0f / texture->getSize().x;
        float scaleY = 200.0f / texture->getSize().y;
        texture->setSmooth(true);
        m_textures.push_back(texture);

        //create sprite to hold texture to display to screen and store sprite in vector
        sf::Sprite* sprite = new sf::Sprite(*texture);
        sprite->setScale({ scaleX, scaleY });
        m_imageSprites.push_back(sprite);


        //set position of sprite images in a grid
        float colCount = 0.0f;
        float rowCount = 0.0f;

        for (int i = 0; i < m_imageSprites.size(); i++)
        {
            if (colCount >= 5.0f)
            {
                colCount = 0.0f;
                rowCount++;
            }

            sprite->setPosition({ 200.0f * colCount, 200.0f * rowCount });

            colCount++;

        }


    }
}

void CImageLoader::ThreadLoadImages(int _image)
{
    //load texture with the image and store texture in vector
    sf::Texture* texture = new sf::Texture(m_fileNames[_image]);
    float scaleX = 200.0f / texture->getSize().x;
    float scaleY = 200.0f / texture->getSize().y;
    texture->setSmooth(true);
    m_textures.push_back(texture);

    //create sprite to hold texture to display to screen and store sprite in vector
    sf::Sprite* sprite = new sf::Sprite(*texture);
    sprite->setScale({ scaleX, scaleY });
    //sprite->setPosition({ 100.0f * i, 100.0f });
    m_imageSprites.push_back(sprite);
}

void CImageLoader::DrawImages(sf::RenderWindow& _window)
{
    for (int i = 0; i < m_imageSprites.size(); i++)
    {
        _window.draw(*m_imageSprites[i]);
    }
}


