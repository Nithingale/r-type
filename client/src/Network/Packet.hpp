/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Created by Vleb
*/

#ifndef RTYPE_PACKET_HPP
#define RTYPE_PACKET_HPP

#define PACKET_ACTION_UP "action_up"
#define PACKET_ACTION_DOWN "action_down"
#define PACKET_ACTION_LEFT "action_left"
#define PACKET_ACTION_RIGHT "action_right"
#define PACKET_ACTION_SPACE "action_space"
#define PACKET_COLLISION "collision:%i"
#define PACKET_CONNECT "connect"
#define PACKET_DISCONNECT "disconnect"
#define PACKET_MATE_CONNECTED "mate_connected"
#define PACKET_MATE_LOST "mate_lost"
#define PACKET_PLAYER_CONNECTED "player_connected"
#define PACKET_START_GAME "start_game"

#define MAGIC_NB 9360624
#define DEFAULT_ID 0

#include <cstdint>
#include <SFML/Network.hpp>
#include <string>

namespace Client {
    struct RawPacket {
        uint32_t magic;
        std::array<uint8_t, 256> payload;
        uint32_t id;
    };

    class Packet {
    public:
        Packet(const uint32_t &id = DEFAULT_ID);
        Packet(const std::string &payload, const uint32_t &id = DEFAULT_ID);
        Packet(const RawPacket &rawPacket);
        ~Packet();
        RawPacket *getRaw() const;
        std::string getPayload() const;
        uint32_t getId() const;
        void setPayload(const std::string &payload);
    private:
        RawPacket *_packet;
    };
}

#endif