//
// Created by giacomo on 02/10/24.
//

#ifndef DT_N_VECTOR_H
#define DT_N_VECTOR_H
#include <yaucl/functional/cond_inline.h>
#include <vector>

struct n_vector {

    INLINE void init(size_t nclasses) {
        nclazzes = nclasses+1;
        n.resize(nclazzes, 0);
    }
    INLINE void reset() {
        std::fill(n.begin(), n.end(), 0);
    }
    INLINE void increment(size_t clazzNo) {
        if (clazzNo <= nclazzes)
            n[clazzNo]++;
    }
    INLINE size_t count(size_t clazzNo) const {
        return n.at(clazzNo);
    }
private:
    std::vector<size_t> n;
    size_t nclazzes;
};

#endif //DT_N_VECTOR_H
