/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** EntityAdmin.hpp
*/

#ifndef RTYPE_ENTITYADMIN_HPP
#define RTYPE_ENTITYADMIN_HPP

#include <unordered_map>
#include <tuple>
#include "TransformComponent.hpp"
#include "ObjectPool.hpp"
#include "HealthComponent.hpp"

namespace ecs
{
    struct EntityAdmin {
        std::tuple<
            ObjectPool<HealthComponent>,
            ObjectPool<TransformComponent>
        > pools;
    };
}

#endif
