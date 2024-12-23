/*Copyright (c) 2020 Christoph Meyer

 https://github.com/christophmeyer/twigy/blob/master/src/core/utils.cpp

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
SOFTWARE.
 */

#include <yaucl/data/csv/csv.h>

#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <yaucl/data/csv/parser.hpp>
#include <map>

void Split_X_y(table &data_frame, std::vector<std::vector<std::pair<std::string,union_minimal>>> &X,
               std::vector<int> &y, std::string feature) {
    std::map<union_minimal, int> def;
    auto it = std::find(data_frame.headers_.begin(), data_frame.headers_.end(),
                        feature);
    std::size_t label_idx = std::distance(data_frame.headers_.begin(), it);
    for (std::size_t row_idx = 0; row_idx < data_frame.data_.size(); row_idx++) {
        std::vector<std::pair<std::string,union_minimal>> current_row;
        for (std::size_t col_idx = 0; col_idx < data_frame.headers_.size();
             col_idx++) {
            if (col_idx != label_idx) {
                current_row.push_back(data_frame.data_[row_idx][col_idx]);
            }
        }
        std::sort(current_row.begin(), current_row.end());
        X.push_back(current_row);
        auto val = data_frame.data_[row_idx][label_idx].second;
        auto itt = def.find(val);
        if (itt != def.end()) {
            y.push_back(itt->second);
        } else {
            size_t ds = def.size();
            def[val] = ds;
            y.push_back(ds);
        }
    }
}

void table::AddRow(const std::vector<std::pair<std::string,union_minimal>>& row) { data_.push_back(row); }

void table::SetHeaders(std::vector<std::string> h) { headers_ = h; }

void table::Print(size_t num_rows) {
    for (size_t j = 0; j < headers_.size(); j++) {
        col_widths_.push_back(std::max(static_cast<int>(headers_[j].length()), 6));
    }
    size_t total_width = headers_.size();
    for (auto &n : col_widths_) {
        total_width += n;
    }

    for (size_t j = 0; j < total_width; j++) {
        std::cout << "-";
    }

    std::cout << std::endl;

    for (size_t j = 0; j < headers_.size(); j++) {
        std::cout << std::setw(col_widths_[j]) << headers_[j] << "|";
    }

    std::cout << std::endl;
    for (size_t j = 0; j < total_width; j++) {
        std::cout << "-";
    }

    std::cout << std::endl;
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < data_[i].size(); j++) {
            std::cout << std::setw(col_widths_[j]);
            if (std::holds_alternative<std::string>(data_[i][j].second))
                std::cout << std::get<std::string>(data_[i][j].second);
            else
                std::cout << std::get<double>(data_[i][j].second);
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}

table ReadCsv(const std::string &input_path) {
    std::ifstream input_file(input_path);
    aria::csv::CsvParser parser = aria::csv::CsvParser(input_file);

    bool first_row = true;
    table data;
    std::vector<std::pair<std::string,union_minimal>> data_row;
    std::vector<std::string> headers;

    for (auto &row : parser) {
        if (first_row) {
            first_row = false;
            for (auto &field : row) {
                headers.push_back(field);
            }
            data.SetHeaders(headers);
            continue;
        }

        size_t idx = 0;
        for (auto &field : row) {
            if (!field.empty()) {
                try {
                    data_row.emplace_back(headers.at(idx), std::stod(field));
                } catch (...) {
                    data_row.emplace_back(headers.at(idx), field);
                }
            }
            idx++;
        }
        data.AddRow(data_row);
        data_row.clear();
    }
    return data;
}

std::vector<int> GenerateRandomIntVector(int a, int b, int n_samples,
                                         std::mt19937 &gen) {
    std::uniform_int_distribution<> distrib(a, b);
    std::vector<int> rand_vector;
    for (int i = 0; i < n_samples; i++) {
        rand_vector.push_back(distrib(gen));
    }
    return rand_vector;
}

void CheckNegativeLabels(const std::vector<int> *label_data) {
    for (std::size_t i = 0; i < label_data->size(); i++) {
        if ((*label_data)[i] < 0) {
            throw std::invalid_argument(
                    "Negative class label given. The labels must be given by 0,1, ... "
                    "n_labels - 1.");
        }
    }
}

int ArgMax(std::vector<double> &vector) {
    std::size_t i = 0;
    std::size_t max_pos = 0;
    while (i < vector.size()) {
        if (vector[max_pos] < vector[i]) {
            max_pos = i;
        }
        i++;
    }
    return max_pos;
}

int ArgMax(std::vector<int> &vector) {
    std::size_t i = 0;
    std::size_t max_pos = 0;
    while (i < vector.size()) {
        if (vector[max_pos] < vector[i]) {
            max_pos = i;
        }
        i++;
    }
    return max_pos;
}

