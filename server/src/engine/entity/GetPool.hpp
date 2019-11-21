/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** GetPool.cpp
*/

#include "ObjectPool.hpp"
#include "EntityAdmin.hpp"

namespace ecs
{
    template<typename T>
    ObjectPool<T> &GetPool(EntityAdmin &admin)
    {
        return std::get<ObjectPool<T>>(admin.pools);
    }
}