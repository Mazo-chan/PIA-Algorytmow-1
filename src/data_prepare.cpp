#include "data_prepare.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace data_prepare {
    void remove_nan(const std::string& input_file, const std::string& output_file) {
        std::ifstream infile(input_file);
        std::ofstream outfile(output_file);
        if (!infile.is_open()) {
            std::cerr << "Nie można otworzyć pliku: " << input_file << std::endl;
            return;
        }
        // , title header, score header
        // id, title, score
        array_list<DataIn> data_list;
        std::string line;
        // pomijamy header
        std::getline(infile, line);
        while (std::getline(infile, line)) {
            size_t comma_pos = line.find(',');
            if (comma_pos == std::string::npos) continue; // Nieprawidłowy format
            line = line.substr(comma_pos + 1); // Pomijamy id
            comma_pos = line.find(',');
            std::string title = line.substr(0, comma_pos);
            std::string score_str = line.substr(comma_pos + 1);
            try {
                int score = static_cast<int>(std::stof(score_str));
                data_list.push_back(DataIn(score, title));
            } catch (const std::invalid_argument&) {
                // Nie można przekonwertować na int, pomijamy
                continue;
            }
        }
        infile.close();
        // Zapisujemy do nowego pliku
        while (data_list.get_size() > 0) {
            DataIn data = data_list.get_last();
            data_list.pop_back();
            outfile << data._score << "," << data._title << std::endl;
        }
        outfile.close();
    }
    void load_data(const std::string& file, array_list<DataIn>& data_list, int max_size) {
        std::ifstream infile(file);
        if (!infile.is_open()) {
            std::cerr << "Nie można otworzyć pliku: " << file << std::endl;
            return;
        }
        std::string line;
        while (std::getline(infile, line) && data_list.get_size() < max_size) {
            size_t comma_pos = line.find(',');
            if (comma_pos == std::string::npos) continue; // Nieprawidłowy format
            std::string score_str = line.substr(0, comma_pos);
            std::string title = line.substr(comma_pos + 1);
            try {
                int score = std::stoi(score_str);
                data_list.push_back(DataIn(score, title));
            } catch (const std::invalid_argument&) {
                // Nie można przekonwertować na int, pomijamy
                continue;
            }
        }
        infile.close();
    }
}
