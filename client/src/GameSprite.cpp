/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Created by Arthamios
*/

#include <iostream>
#include "GameSprite.hpp"

game::GameSprite::GameSprite() : strToType(initTypes()), images(initImages()), simpleTexture(initBasicTextures()),
                                 typeSprite(initSprites())
{
}

game::GameSprite::Type game::GameSprite::getType(const std::string &str)
{
    auto it = strToType.find(str);

    if (it == strToType.end()) {
        std::cerr << "could not match \"" << str << "\" to a type" << std::endl;
        return INVALID_T;
    }
    return it->second;
}

sf::Sprite game::GameSprite::getSpriteOfType(const game::GameSprite::Type &type)
{
    return typeSprite.at(type)();
}

sf::Sprite game::GameSprite::getSpriteOfType(const std::string &type)
{
    return getSpriteOfType(getType(type));
}

sf::Texture game::GameSprite::loadTexture(const std::string &filename, const sf::Rect<int> &rect)
{
    sf::Texture texture;

    texture.loadFromImage(images.at(filename), rect);
    return texture;
}

std::unordered_map<std::string, game::GameSprite::Type> game::GameSprite::initTypes()
{
    return {{"spaceship_right_most", SPACESHIP_RIGHT_MOST}, {"spaceship_right", SPACESHIP_RIGHT},
        {"ship", SPACESHIP_NORMAL}, {"spaceship_left", SPACESHIP_LEFT},
        {"spaceship_left_most", SPACESHIP_LEFT_MOST}, {"spaceship_right_most_rev", SPACESHIP_RIGHT_MOST_REV},
        {"spaceship_right_rev", SPACESHIP_RIGHT_REV}, {"alien", SPACESHIP_NORMAL_REV},
        {"spaceship_left_rev", SPACESHIP_LEFT_REV}, {"spaceship_left_most_rev", SPACESHIP_LEFT_MOST_REV},

        {"missile_fire1", BASIC_MISSILE_LAUNCH}, {"missile_fire2", BASIC_MISSILE_LAUNCH_2},
        {"missile_standard", BASIC_MISSILE_LAUNCHED}, {"missile_inverted", BASIC_MISSILE_LAUNCHED_REV},
        {"missile_inverted", BASIC_MISSILE_LAUNCH_2_REV},
        {"missile_inverted", BASIC_MISSILE_LAUNCH_REV},};
}

std::unordered_map<std::string, sf::Image> game::GameSprite::initImages()
{
    return {{"../../client/assets/r-typesheet1.gif", []() {
        sf::Image image;
        image.loadFromFile("../../client/assets/r-typesheet1.gif");
        return image;
    }()}};
}

std::unordered_map<game::GameSprite::BasicType, sf::Texture> game::GameSprite::initBasicTextures()
{
    return {{SPACESHIP, loadTexture("../../client/assets/r-typesheet1.gif",
        sf::Rect(sf::Vector2<int>(101, 2), sf::Vector2<int>(330, 15)))}, {BASIC_MISSILE,
        loadTexture("../../client/assets/r-typesheet1.gif",
            sf::Rect(sf::Vector2<int>(215, 85), sf::Vector2<int>(102, 12)))},};
}

std::function<sf::Sprite()> game::GameSprite::getSpriteConstructor(BasicType type, sf::Vector2i pos,
                                                                   sf::Vector2i size) const
{
    return [this, type, pos, size]() -> sf::Sprite {
        return sf::Sprite(this->simpleTexture.at(type), sf::Rect(pos, size));
    };
}

std::unordered_map<game::GameSprite::Type, std::function<sf::Sprite()>> game::GameSprite::initSprites()
{
    return {{INVALID_T, [this]() -> sf::Sprite {
        return sf::Sprite();
    }}, {SPACESHIP_RIGHT_MOST, getSpriteConstructor(SPACESHIP, {0, 1}, {32, 14})},
        {SPACESHIP_RIGHT, getSpriteConstructor(SPACESHIP, {33, 1}, {32, 13})},
        {SPACESHIP_NORMAL, getSpriteConstructor(SPACESHIP, {66, 1}, {32, 12})},
        {SPACESHIP_LEFT, getSpriteConstructor(SPACESHIP, {99, 1}, {32, 13})},
        {SPACESHIP_LEFT_MOST, getSpriteConstructor(SPACESHIP, {132, 0}, {32, 14})},
        {SPACESHIP_LEFT_MOST_REV, getSpriteConstructor(SPACESHIP, {166, 0}, {32, 14})},
        {SPACESHIP_LEFT_REV, getSpriteConstructor(SPACESHIP, {299, 1}, {32, 13})},
        {SPACESHIP_NORMAL_REV, getSpriteConstructor(SPACESHIP, {232, 1}, {32, 12})},
        {SPACESHIP_RIGHT_REV, getSpriteConstructor(SPACESHIP, {265, 1}, {32, 13})},
        {SPACESHIP_RIGHT_MOST_REV, getSpriteConstructor(SPACESHIP, {298, 1}, {32, 14})},
        {BASIC_MISSILE_LAUNCH, getSpriteConstructor(BASIC_MISSILE, {0, 0}, {14, 12})},
        {BASIC_MISSILE_LAUNCH_2, getSpriteConstructor(BASIC_MISSILE, {18, 2}, {11, 9})},
        {BASIC_MISSILE_LAUNCHED, getSpriteConstructor(BASIC_MISSILE, {34, 5}, {16, 4})},
        {BASIC_MISSILE_LAUNCHED_REV, getSpriteConstructor(BASIC_MISSILE, {52, 5}, {16, 4})},
        {BASIC_MISSILE_LAUNCH_2_REV, getSpriteConstructor(BASIC_MISSILE, {73, 2}, {11, 9})},
        {BASIC_MISSILE_LAUNCH_REV, getSpriteConstructor(BASIC_MISSILE, {88, 0}, {14, 12})},};
}