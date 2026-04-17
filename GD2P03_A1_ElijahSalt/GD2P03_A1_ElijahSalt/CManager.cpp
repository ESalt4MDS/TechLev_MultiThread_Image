#include "CManager.h"

CManager::CManager()
{
    m_loader = new CImageLoader();
    m_window = new sf::RenderWindow(sf::VideoMode({ 1000, 1000 }), "Images!");
}

CManager::~CManager()
{
    delete m_window;
    m_window = nullptr;

    delete m_loader;
    m_loader = nullptr;
}

void CManager::Initialize()
{
    m_loader->LoadFiles(SetType::SMALL);
}

void CManager::RunProgram()
{
    
    while (m_window->isOpen())
    {
        while (const std::optional event = m_window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window->close();

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({ 0.0f, 0.0f }, sf::Vector2f(resized->size));
                m_window->setView(sf::View(visibleArea));
            }

            if (const auto* KeyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (KeyPressed->scancode == sf::Keyboard::Scancode::Num1)
                {
                    std::cout << "save image" << std::endl;
                    SaveImage();
                }

                if (KeyPressed->scancode == sf::Keyboard::Scancode::Num2)
                {
                    std::cout << "small set" << std::endl;
                    m_loader->LoadFiles(SetType::SMALL);
                }
                if (KeyPressed->scancode == sf::Keyboard::Scancode::Num3)
                {
                    std::cout << "large set" << std::endl;
                    m_loader->LoadFiles(SetType::LARGE);
                }

            }
        }

        Draw();
    }
}

void CManager::Draw()
{
    m_window->clear();

    m_loader->DrawImages(m_window);

    m_window->display();

}

void CManager::SaveImage()
{
    sf::Texture image;
    image.resize(sf::Vector2u(m_window->getSize().x, m_window->getSize().y));
    image.update(*m_window);
    if (image.copyToImage().saveToFile("screenshot.png"))
    {
        std::cout << "screenshot saved" << std::endl;
    }

}

