
/*
 * vector_hash.h
 * This file is part of Classifiers
 *
 * Copyright (C) 2021 - Giacomo Bergami
 *
 * ProbabilisticTraceAlignment is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ProbabilisticTraceAlignment is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProbabilisticTraceAlignment. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 14/11/20.
//
#ifndef CLASSIFIERS_PAIR_HASH_H2
#define CLASSIFIERS_PAIR_HASH_H2

#include <yaucl/hashing/hash_combine.h>
#include <utility>

namespace std {
    template <typename T, typename K>
    struct hash<std::pair<T, K>>
    {
        virtual ~hash<std::pair<T, K>>() {}

        std::size_t operator()(const std::pair<T, K>& k) const
        {
            size_t init = 31;
            init = yaucl::hashing::hash_combine<T>(init, k.first);
            init = yaucl::hashing::hash_combine<K>(init, k.second);
            return init;
        }
    };

    // Recursive template code derived from Matthieu M., https://stackoverflow.com/a/7115547/1376095
    template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
    struct HashValueImpl
    {
        static void apply(size_t& seed, Tuple const& tuple)
        {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            yaucl::hashing::hash_combine(seed, std::get<Index>(tuple));
        }
    };

    // https://stackoverflow.com/a/7115547/1376095
    template <class Tuple>
    struct HashValueImpl<Tuple,0>
    {
        static void apply(size_t& seed, Tuple const& tuple)
        {
            yaucl::hashing::hash_combine(seed, std::get<0>(tuple));
        }
    };

    template <typename ... TT>
    struct hash<std::tuple<TT...>>
    {
        size_t
        operator()(std::tuple<TT...> const& tt) const
        {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
            return seed;
        }
    };

}

template <typename T, typename K>
struct hashing_pair
{

    std::size_t operator()(const std::pair<T, K>& k) const
    {
        size_t init = 31;
        init = yaucl::hashing::hash_combine<T>(init, k.first);
        init = yaucl::hashing::hash_combine<K>(init, k.second);
        return init;
    }
};

#endif //FUZZYSTRINGMATCHING2_VECTOR_HASH_H
