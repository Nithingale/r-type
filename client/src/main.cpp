/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "INetwork.hpp"
#include "sfNetwork.hpp"
#include "GameSprite.hpp"

void handle_events(game::INetwork *network, sf::RenderWindow &window)
{
    size_t sent;
    sf::Event event{};
    static const std::vector<std::pair<sf::Keyboard::Key, std::string>> keys = {{sf::Keyboard::Left, "left"},
        {sf::Keyboard::Right, "right"}, {sf::Keyboard::Up, "up"}, {sf::Keyboard::Down, "down"},
        {sf::Keyboard::Space, "space"}, {sf::Keyboard::R, "r"}};

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            for (auto &key : keys)
                if (sf::Keyboard::isKeyPressed(key.first))
                    network->send(key.second.c_str(), key.second.length(), sent);
        }
    }
}

void handleServerInstructions(game::GameSprite &gameSprite, sf::RenderWindow &window, const char *data,
                              std::unordered_map<int, std::pair<game::GameSprite::Type, sf::Sprite>> &toDraw)
{
    std::string dataStr(data);

    std::cout << dataStr << std::endl;
    size_t semiColonIdx = dataStr.find(';');
    size_t dotIdx = dataStr.find(':');
    size_t comaIdx = dataStr.find(',');

    if (semiColonIdx == std::string::npos || dotIdx == std::string::npos || comaIdx == std::string::npos)
        return;

    int id = std::stoi(dataStr);
    std::string typeStr = dataStr.substr(semiColonIdx + 1, dotIdx - semiColonIdx - 1);
    const auto &pair = toDraw.find(id);

    std::cout << "received: " << dataStr << std::endl;
    if (pair == toDraw.end() || gameSprite.getType(typeStr) != pair->second.first)
        toDraw[id] = std::make_pair(gameSprite.getType(typeStr), gameSprite.getSpriteOfType(typeStr));
    toDraw.at(id).second.setPosition(std::stof(data + dotIdx + 1) * 10, std::stof(data + comaIdx + 1) * 10);
}

void updateWindow(sf::RenderWindow &window,
                  const std::unordered_map<int, std::pair<game::GameSprite::Type, sf::Sprite>> &toDraw)
{
    window.clear();
    if (!toDraw.empty()) {
        for (const auto &sprite : toDraw)
            window.draw(sprite.second.second);
        window.display();
    }
}

void endGame(game::INetwork *network)
{
    network->disconnect();
    delete network;
    std::cout << "client closed" << std::endl;
}

int display(game::INetwork *network)
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "r_type");
    game::GameSprite gameSprite;
    std::unordered_map<int, std::pair<game::GameSprite::Type, sf::Sprite>> toDraw;
    char data[1024] = {0};
    std::clock_t lastDrawTime = (double)std::clock() / CLOCKS_PER_SEC;

    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) {
        handle_events(network, window);
        std::size_t received = 0;
        if (network->receive(&data, sizeof(data), received))
            handleServerInstructions(gameSprite, window, data, toDraw);
        if ((double)std::clock() / CLOCKS_PER_SEC - lastDrawTime >= 0.016) {
            updateWindow(window, toDraw);
            lastDrawTime = (double)std::clock() / CLOCKS_PER_SEC;
        }
    }
    endGame(network);
    return 0;
}

int main()
{
    game::INetwork *network = new game::sfNetwork();
    if (!network->connect("127.0.0.1", 1234)) {
        std::cerr << "failed to connect" << std::endl;
        return 84;
    }
    return display(network);
}
