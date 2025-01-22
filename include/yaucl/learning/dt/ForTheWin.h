/*
 * ForTheWin.h
 * This file is part of yaucl-learning
 *
 * Copyright (C) 2022 - Giacomo Bergami
 *
 * yaucl-learning is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * yaucl-learning is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with yaucl-learning. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 03/11/22.
//

#ifndef DISTANCE_FORTHEWIN_H
#define DISTANCE_FORTHEWIN_H

#include <utility>
#include <vector>
#include <algorithm>
#include <yaucl/functional/cond_inline.h>
struct ForTheWin {
    enum gain_measures {
        Entropy,
        Gini,
        CART
    };
    std::vector<std::pair<double,double>> v;
    std::vector<double> n;
    double total, nPos, nNeg;

    ForTheWin() {}
    ForTheWin(const ForTheWin&) = default;
    ForTheWin(ForTheWin&& ) = default;
    ForTheWin& operator=(const ForTheWin&) = default;
    ForTheWin& operator=(ForTheWin&& ) = default;
    std::pair<double,double> dd{0.0,0.0};

    INLINE void setP(int clazz, double pos, double neg) {
        v[clazz].first = pos/nPos;
        v[clazz].second = neg/nNeg;
    }
    INLINE double countClass(int clazz) {
        total+=1.0;
        return (n[clazz]+=1.0);
    }
    INLINE void init(int max_classes) {
        v.resize(max_classes+1, dd);
        n.resize(max_classes+1, 0.0);
        total = 0.0;
    }

    INLINE size_t nClasses() const {
        return v.size();
    }
    INLINE double getClassPrecision(int clazz) const {
        return n[clazz];
    }
    INLINE double getP(int clazz, bool posNegOtherwise) const {
        return posNegOtherwise ? v[clazz].first : v[clazz].second;
    }
    double getGain(gain_measures type) const;
    INLINE void goodBad(double d, double d1) {
        nPos = d; nNeg = d1;
    }

    INLINE void normalizeCountClass() {
        std::transform(n.begin(), n.end(), n.begin(), [this](double x ){
            return x/total;
        });
    }

    void reset() {
        total = 0.0;
        std::fill(n.begin(), n.end(), 0.0);
        std::fill(v.begin(), v.end(), dd);
    }
};


#endif //DISTANCE_FORTHEWIN_H
