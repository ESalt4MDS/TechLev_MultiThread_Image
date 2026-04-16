#include "CManager.h"

CManager::CManager()
{
    m_loader = new CImageLoader();
}

CManager::~CManager()
{
    delete m_window;
    m_window = nullptr;


}

void CManager::RunProgram()
{
    /*
    const int totalTasks = 50;

    CThreadPool pool;

    for (int i = 0; i < totalTasks; i++)
    {
        pool.Submit(CTask(i));
        printf("task %i pushed to work queue\n", i);
    }
    printf("\n\n");

    while (pool.TasksProcessed() < totalTasks);

    pool.Stop();
    printf("done\n");
    */
    //CImageLoader m_loader;
    
    //m_loader->LoadFiles(SetType::SMALL);
    m_loader->LoadFiles(SetType::LARGE);

    m_window = new sf::RenderWindow(sf::VideoMode({ 1000, 1000 }), "SFML works!");


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
        }

        m_window->clear();

        m_loader->DrawImages(*m_window);

        m_window->display();
        //Draw();
    }
}

void CManager::Draw()
{
    m_window->clear();

    //m_loader.DrawImages(*m_window);

    m_window->display();

}
