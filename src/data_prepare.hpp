#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include "array_list.hpp"

class DataIn{
    public:
        int _score;
        std::string _title;
        
        // Default constructor
        DataIn() : _score(0), _title("") {}
        DataIn(int score, const std::string& title) : _score(score), _title(title) {}
        // Comparison operators for sorting and searching
        bool operator==(const DataIn& other) const {
            return _score == other._score && _title == other._title;
        }
        
        bool operator<(const DataIn& other) const {
            if(_score < other._score) return true;
            else if(_score == other._score) return _title < other._title;
            return false;
        }

        bool operator>(const DataIn& other) const {
            if(_score > other._score) return true;
            else if(_score == other._score) return _title > other._title;
            return false;
        }
};

namespace data_prepare {
    void remove_nan(const std::string& input_file, const std::string& output_file);
    void load_data(const std::string& file, array_list<DataIn>& data_list, int max_size);
}