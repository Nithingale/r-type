/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** SendProtocol.cpp
*/

#include "SendProtocol.hpp"

const std::unordered_map<ecs::SendProtocol::Key, std::string_view> ecs::SendProtocol::commands = {
    {ecs::SendProtocol::CONNECTED, "player_connected"},
    {ecs::SendProtocol::ENTITY_SET, "entity_set"},
};

std::string_view ecs::SendProtocol::get(ecs::SendProtocol::Key key)
{
    return commands.at(key);
}
