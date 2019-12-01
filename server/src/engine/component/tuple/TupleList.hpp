/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** TupleList.hpp
*/

#ifndef RTYPE_TUPLELIST_HPP
#define RTYPE_TUPLELIST_HPP

#include "SendRenderTuple.hpp"
#include "MoveTuple.hpp"
#include "InputTuple.hpp"
#include "InputDirectionTuple.hpp"

namespace ecs
{
    using TupleList = std::tuple
        <
            MoveTuple,
            InputTuple,
            SendRenderTuple,
            CreationBulletTuple,
            InputDirectionTuple
        >;
}

#endif
