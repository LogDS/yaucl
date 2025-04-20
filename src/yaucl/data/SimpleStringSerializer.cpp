//
// Created by giacomo on 11/04/25.
//

#include <yaucl/data/SimpleStringSerializer.h>
#include <string.h>

size_t SimpleStringReader::query_equals(const std::string& val) const {
    size_t hash_val = SimpleStringSerializer::compute_hash(val);
    size_t low = 0;
    size_t high = index_len-1;    // ans will store the prev index of element which is the lower bound of k
    size_t ans = 0;
    bool found = false;

    while(low <= high){
        int mid = low + (high - low) / 2;
        if (hash_index[1+mid*3] == hash_val) {
            found = true;
            ans = mid;
            break;
        }
        else if(hash_index[1+mid*3] >hash_val){
            high = mid-1;
        }
        else{
            ans = mid;
            low = mid+1;
        }
    }     // return only ans+1 if you want just the index of lower-bound

    if (!found)
        return -1;
    size_t len = block_len(ans);
    auto block_ = block(ans);
    for (size_t idx = 0; idx < len; idx++) {
        auto i = block_[idx];
        if (strncmp(str(i), val.c_str(), val.size()) == 0)
            return i;
    }
    return -1;
}