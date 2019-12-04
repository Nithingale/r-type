/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Menu.hpp
*/

#ifndef RTYPE_MENU_HPP
#define RTYPE_MENU_HPP

#include "Component/Button.hpp"
#include "IScene.hpp"

namespace Client {
    class Menu : public IScene {
    public:
        Menu();
        ~Menu() override;
        void event(Client::IScene *&self, sf::Event &event, Client::KeyBind &keyBind, Client::Network &network) override;
        void update(Client::IScene *&self, Client::Network &network, Client::Window &window) override;
        void render(Client::Window &window) override;
    private:
    };
}

#endif