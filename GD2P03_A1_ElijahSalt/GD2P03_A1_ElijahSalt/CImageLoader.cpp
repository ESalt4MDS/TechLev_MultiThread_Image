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

    for (auto iter : m_imagePositions)
    {
        delete iter;
        iter = nullptr;
    }
}

void CImageLoader::LoadFiles(SetType _set)
{
    std::wstring path = std::filesystem::current_path().wstring();

    switch (_set)
    {
        case SetType::SMALL:
            path.append(L"\\small set");
            break;
        case SetType::LARGE:
            path.append(L"\\large set");
            break;
        default:
            break;
    }

    //clear vectors if not empty
    //when changing between sets
    if (!m_fileNames.empty())
    {
        m_fileNames.clear();
    }
    if (!m_imageSprites.empty())
    {
        m_imageSprites.clear();
    }
    if (!m_imagePositions.empty())
    {
        m_imagePositions.clear();
    }
    if (!m_imagesInGrid.empty())
    {
        m_imagesInGrid.clear();
    }
    if (!m_textures.empty())
    {
        m_textures.clear();
    }

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        std::wstring imagePath = entry.path().wstring();
        m_fileNames.push_back(imagePath);
    }

    LoadImages();
}

void CImageLoader::LoadImages()
{
    int threadCount = std::thread::hardware_concurrency();

    CThreadPool pool(threadCount);

    std::vector<std::future<sf::Sprite*>> spriteFutures;

    for (int i = 0; i < m_fileNames.size(); i++)
    {
        std::wstring fileName = m_fileNames[i];
        std::wcout << m_fileNames[i] << std::endl;

        auto fut = pool.Submit([fileName, i]()
        {
            //load texture with the image and store texture in vector
            sf::Texture* texture = new sf::Texture(fileName);

            float scaleX = 200.0f / texture->getSize().x;
            float scaleY = 200.0f / texture->getSize().y;
            texture->setSmooth(true);

            //create sprite from texture to display to screen and store sprite in vector
            sf::Sprite* sprite = new sf::Sprite(*texture);
            sprite->setScale({ scaleX, scaleY });

            return sprite;
        });
        spriteFutures.push_back(std::move(fut));
    }
    pool.Start();

    for (auto& fut : spriteFutures)
    {
        m_imageSprites.push_back(fut.get());
    }

    while (pool.TasksDone() < pool.GetNumTasks());

    pool.Stop();

    //set position of sprite images in a grid 5x5
    float colCount = 0.0f;
    float rowCount = 0.0f;

    for (int i = 0; i < 25; i++)
    {
        if (colCount >= 5.0f)
        {
            colCount = 0.0f;
            rowCount++;
        }

        sf::Vector2f* position = new sf::Vector2f(200.0f * colCount, 200.0f * rowCount);
        m_imagePositions.push_back(position);

        colCount++;

    }

    SetupImageGrid();
}

void CImageLoader::SetupImageGrid()
{
    for (int i = 0; i < m_imagePositions.size(); i++)
    {
        if (i >= m_imageSprites.size())
        {
            break;
        }
        m_imageSprites[i]->setPosition(*m_imagePositions[i]);
        
        m_imagesInGrid.push_back(m_imageSprites[i]);
    }
}

void CImageLoader::DrawImages(sf::RenderWindow* _window)
{
    for (int i = 0; i < m_imagesInGrid.size(); i++)
    {   
        _window->draw(*m_imagesInGrid[i]);
    }
}


