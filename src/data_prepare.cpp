#include "data_prepare.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace data_prepare {
    // Helper function to extract next CSV field starting at position pos
    // Returns the field content and updates pos to point after the comma
    std::string get_next_field(const std::string& line, size_t& pos) {
        std::string field;
        bool in_quotes = false;
        
        // Skip leading whitespace
        while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) {
            pos++;
        }
        
        // Check if field starts with quote
        if (pos < line.length() && line[pos] == '"') {
            in_quotes = true;
            pos++; // Skip opening quote
            
            // Read until closing quote
            while (pos < line.length()) {
                if (line[pos] == '"') {
                    pos++; // Skip closing quote
                    break;
                }
                field += line[pos];
                pos++;
            }
        } else {
            // Read until comma or end of line
            while (pos < line.length() && line[pos] != ',') {
                field += line[pos];
                pos++;
            }
        }
        
        // Skip trailing whitespace
        while (field.length() > 0 && (field.back() == ' ' || field.back() == '\t')) {
            field.pop_back();
        }
        
        // Skip comma if present
        if (pos < line.length() && line[pos] == ',') {
            pos++;
        }
        
        return field;
    }

    void remove_nan(const std::string& input_file, const std::string& output_file) {
        std::ifstream infile(input_file);
        std::ofstream outfile(output_file);
        if (!infile.is_open()) {
            std::cerr << "Nie można otworzyć pliku: " << input_file << std::endl;
            return;
        }
        array_list<DataIn> data_list;
        std::string line;
        // Pomijamy header
        std::getline(infile, line);
        while (std::getline(infile, line)) {
            size_t pos = 0;
            
            // Parse id (first field, we skip it)
            std::string id_str = get_next_field(line, pos);
            
            // Parse title (second field)
            std::string title = get_next_field(line, pos);
            
            // Parse score (third field)
            std::string score_str = get_next_field(line, pos);
            
            if (title.empty() || score_str.empty()) continue;
            
            try {
                int score = static_cast<int>(std::stof(score_str));
                data_list.push_back(DataIn(score, title));
            } catch (const std::invalid_argument&) {
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

