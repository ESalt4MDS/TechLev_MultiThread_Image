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

    int threadCount = std::thread::hardware_concurrency();

    CThreadPool pool(threadCount);

    std::vector<std::future<std::wstring>> futures;
    int c = 0;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        std::wstring imagePath = entry.path().wstring();
        c++;
        //std::cout << "image: " << c << " " << imagePath << "\n" << std::endl;
        auto fut = pool.Submit([imagePath]()
        {
            std::wstring fileName;
            fileName = imagePath;
            return fileName;
        });
        futures.push_back(std::move(fut));
        //m_fileNames.push_back(entry.path().string());
    }
    pool.Start();

    while (pool.TasksDone() < pool.GetNumTasks());

    for (auto& fut : futures)
    {
        std::wstring fileName = fut.get();
        m_fileNames.push_back(fileName);
    }

    pool.Stop();

    LoadImages();
}

void CImageLoader::LoadImages()
{
    int threadCount = std::thread::hardware_concurrency();

    CThreadPool pool(threadCount);

    std::vector<std::future<sf::Sprite*>> spriteFutures;

    //set position of sprite images in a grid
    /*float colCount = 0.0f;
    float rowCount = 0.0f;*/

    for (int i = 0; i < m_fileNames.size(); i++)
    {
        /*if (colCount >= 5.0f)
        {
            colCount = 0.0f;
            rowCount++;
        }*/

        std::wstring fileName = m_fileNames[i];
        auto fut = pool.Submit([fileName]()
        {
            //load texture with the image and store texture in vector
            sf::Texture* texture = new sf::Texture(fileName);
            float scaleX = 200.0f / texture->getSize().x;
            float scaleY = 200.0f / texture->getSize().y;
            texture->setSmooth(true);

            //create sprite to hold texture to display to screen and store sprite in vector
            sf::Sprite* sprite = new sf::Sprite(*texture);
            sprite->setScale({ scaleX, scaleY });
            //sprite->setPosition({ 200.0f * colCount, 200.0f * rowCount });

            return sprite;
        });
        spriteFutures.push_back(std::move(fut));


        
        //colCount++;


        ////load texture with the image and store texture in vector
        //sf::Texture* texture = new sf::Texture(m_fileNames[i]);
        //float scaleX = 200.0f / texture->getSize().x;
        //float scaleY = 200.0f / texture->getSize().y;
        //texture->setSmooth(true);
        //m_textures.push_back(texture);

        ////create sprite to hold texture to display to screen and store sprite in vector
        //sf::Sprite* sprite = new sf::Sprite(*texture);
        //sprite->setScale({ scaleX, scaleY });
        //m_imageSprites.push_back(sprite);


    }
    pool.Start();

    //for (auto& fut : futures)
    //{
    //    //sf::Sprite* sprite = fut.get();
    //    m_imageSprites.push_back(fut.get());
    //}

    while (pool.TasksDone() < pool.GetNumTasks());

    for (auto& fut : spriteFutures)
    {
        m_imageSprites.push_back(fut.get());
    }

    pool.Stop();

    //set position of sprite images in a grid
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
}

void CImageLoader::DrawImages(sf::RenderWindow& _window)
{
    /*int threadCount = std::thread::hardware_concurrency();

    CThreadPool pool(threadCount);*/

    //std::vector<std::future<void>> futures;

    for (int i = 0; i < m_imagePositions.size(); i++)
    {
       /* sf::Sprite* imageSprite = m_imageSprites[i];
        auto fut = pool.Submit([&_window, imageSprite]()
        {*/
        if (i >= m_imageSprites.size())
        {
            break;
        }
        m_imageSprites[i]->setPosition(*m_imagePositions[i]);
        _window.draw(*m_imageSprites[i]);

        //});
    }
    /*pool.Start();

    while (pool.TasksDone() < pool.GetNumTasks());

    pool.Stop();*/

}


