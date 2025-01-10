//
// Created by giacomo on 06/12/24.
//

#ifndef GSM2_ROCKSDBMAP_H
#define GSM2_ROCKSDBMAP_H

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/convenience.h"
#include "rocksdb/cleanable.h"
#include <yaucl/functional/assert.h>
#include <filesystem>
#include <iostream>

namespace yaucl{
    namespace structures {
        class RocksDBStringSizeTMap {
            rocksdb::DB* db;
            rocksdb::Options options;
//
            bool isWriting = true;
            size_t size;
            std::filesystem::path path;

        public:
            RocksDBStringSizeTMap() {
                db = nullptr;
                size = 0;
                options.create_if_missing = true;
                path = std::filesystem::temp_directory_path() / std::tmpnam(nullptr);
                rocksdb::Status s = rocksdb::DB::Open(options, path, &db);
                if (s.ok())
                    db->DisableManualCompaction();

                if (!s.ok()) std::cerr << s.ToString() << std::endl;
            }

            void close() {
                if (db) {
                    rocksdb::CancelAllBackgroundWork(db, true);

                    db->Close();
                    delete db;
                    db = nullptr;
                    if (std::filesystem::is_directory(path)) {
                        std::filesystem::remove_all(path);
                    }
                }
            }

            bool put(const std::string& key, size_t value) {
                if (!db){
                    return false;
                }
                if (!isWriting) {
                    isWriting = true;
                }
//                rocksdb::Slice keySlice(key);
                rocksdb::Slice valSlice((char*)&value, sizeof(size_t));
                rocksdb::WriteOptions write_options = rocksdb::WriteOptions();
//                write_options.sync = true;
//                rocksdb::WriteBatch batch;
//                batch.Put(keySlice, valSlice);
                auto out = db->Put(write_options, key, valSlice);
                DEBUG_ASSERT(out.ok());
                return out.ok();
            }

            std::optional<size_t> get(const std::string& key) {
                if (!db) {
                    return {};
                }
//                rocksdb::Slice keySlice((char*)&key, sizeof(key));
                if (isWriting) {
                    rocksdb::FlushOptions flush_opts;
                    db->Flush(flush_opts);
//                    rocksdb::WriteOptions write_options = rocksdb::WriteOptions();
//                    write_options.sync = true;
//                    if (!db->Write(write_options, &batch).ok())
//                        return false;
//                    batch.Clear();
                    isWriting = false;
                }
                rocksdb::PinnableSlice pinnable_val;
                size_t value;
                rocksdb::Status s = db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(), key, &pinnable_val);
                value = *(size_t*)pinnable_val.data();
                DEBUG_ASSERT(s.ok());
                return (s.ok()) ? std::optional<size_t>{value} : std::optional<size_t>{};
            }

            ~RocksDBStringSizeTMap() {
                if (db) {
                    rocksdb::CancelAllBackgroundWork(db, true);
                    db->Close();
                    delete db;
                    db = nullptr;
                }
                if (std::filesystem::is_directory(path)) {
                    std::filesystem::remove_all(path);
                }
            }

        };
    }
}

#endif //GSM2_ROCKSDBMAP_H
