/*Copyright (c) 2020 Christoph Meyer

https://github.com/christophmeyer/twigy/blob/master/src/core/decision_tree.h

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
//
// Created by giacomo on 02/10/24.
//

#ifndef DT_NODES_H
#define DT_NODES_H

#include <yaucl/learning/dt/dt_predicate.h>


struct Nodes {
    size_t begin = 0, end = 0;
    size_t rightOffset, split;
    std::pair<dt_predicate,double> candidate;


    Nodes(size_t begin, size_t end, size_t max_height);

    bool isLeaf;
    std::vector<dt_predicate> leaf_class_result;
    int majority_class;
    double majority_class_precision;
    size_t max_height;
};


#endif //DT_NODES_H
