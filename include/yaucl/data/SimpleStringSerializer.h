//
// Created by giacomo on 11/04/25.
//

#ifndef GSM2_SIMPLESTRINGSERIALIZER_H
#define GSM2_SIMPLESTRINGSERIALIZER_H

#include <yaucl/structures/any_to_uint_bimap.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>


class SimpleStringSerializer {
    yaucl::structures::any_to_uint_bimap<std::string> data;

public:

    static inline long long compute_hash(std::string const& s) {
        const int p = 31;
        const int m = 1e9 + 9;
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : s) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }

    inline std::pair<size_t,bool> put(const std::string& val) {
        return data.put(val);
    }

    inline std::string get(size_t idx) const {
        return data.get(idx);
    }

    inline void serialize_to_disk(const std::filesystem::path& path) const {
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
        }
        std::ofstream file(path / "data.bin", std::ios::binary);
        size_t num_val, size;

        // Writing how many strings are there
        num_val = data.size();
        file.write((const char*)&num_val, sizeof(num_val));
        std::map<size_t, std::vector<size_t>> W;

        // Serializing the lengths of the strings
        size_t begin = 0;
        size_t end = 0;
        for (size_t i = 0; i<num_val; i++) {
            size = data.int_to_T.at(i).size()+1;
            end += size;
            W[compute_hash(data.int_to_T.at(i))].emplace_back(i);
            file.write((const char*)&begin, sizeof(begin));
            file.write((const char*)&end, sizeof(end));
            begin = end;
        }

        for (size_t i = 0; i<num_val; i++) {
            size = data.int_to_T.at(i).size()+1;
            file.write(data.int_to_T.at(i).c_str(), sizeof(char)*size);
        }

        std::ofstream secondary_index(path / "hash_index.bin", std::ios::binary);
        begin = 0;
        end = 0;
        num_val = W.size();
        secondary_index.write((const char*)&num_val, sizeof(num_val));
        for (const auto& [k, v] : W) {
            end += v.size();
            secondary_index.write((const char*)&k, sizeof(k));
            secondary_index.write((const char*)&begin, sizeof(begin));
            secondary_index.write((const char*)&end, sizeof(end));
            begin = end;
        }
        for (const auto& [k, v] : W) {
            for (const auto& val : v) {
                secondary_index.write((const char*)&val, sizeof(val));
            }
        }
    }

};

#include <yaucl/data/VariadicSizeArrayElements.h>

class SimpleStringReader {
    yaucl::data::FixedSizeArrayElements<size_t> data, hash_index;
    size_t len;
    size_t index_len;
    size_t data_afterheader_offset;
    size_t index_afterheader_offset;

    inline size_t block_size() const { return index_len; }
    inline size_t block_len(size_t idx) const {
        if (idx >= index_len) return 0;
        auto idx_begin = idx*3+1;
        auto begin = hash_index[idx_begin+1], end = hash_index[idx_begin+2];
        return end-begin;
    }
    inline const size_t* block(size_t idx) const {
        if (idx >= len) return nullptr;
        auto idx_begin = idx*3+1;
        return (size_t*)(hash_index.raw_data() + index_afterheader_offset) + hash_index[idx_begin+1];
    }

public:
    SimpleStringReader(const std::filesystem::path& path) : data{path / "data.bin"}, hash_index{path / "hash_index.bin"} {
        len = data[0];
        index_len = hash_index[0];
        data_afterheader_offset = (len)*sizeof (size_t)*2+sizeof (size_t);
        index_afterheader_offset = ((index_len)*sizeof (size_t)*3)+sizeof (size_t);
    }

    inline size_t size() const { return len; }

    inline size_t strlen(size_t idx) const {
        if (idx >= len) return 0;
        auto idx_begin = idx*2+1;
        auto begin = data[idx_begin], end = data[idx_begin+1];
        return end-begin-1;
    }

    inline const char* str(size_t idx) const {
        if (idx >= len) return nullptr;
        auto idx_begin = idx*2+1;
        return data.raw_data() + data_afterheader_offset + data[idx_begin];
    }

    size_t query_equals(const std::string& val) const;
};

#endif //GSM2_SIMPLESTRINGSERIALIZER_H
