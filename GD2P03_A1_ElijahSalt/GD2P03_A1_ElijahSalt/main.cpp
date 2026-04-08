#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 512, 512 }), "SFML works!");

    std::vector<std::string> fileNames;

    std::string path = std::filesystem::current_path().string();
    path.append("\\small set");
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        fileNames.push_back(entry.path().string());
    }

    for (auto iter : fileNames)
    {
        std::cout << iter << std::endl;
    }

    sf::Texture texture;
    texture.loadFromFile(fileNames[3]);
    sf::Sprite sprite(texture);
    sprite.setScale({ 0.25f, 0.25f });


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({ 0.0f, 0.0f }, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}