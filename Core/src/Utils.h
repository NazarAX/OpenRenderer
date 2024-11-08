#pragma once

#include <iostream>
#include <fstream>
#include <string>

struct File 
{
    static std::string readFile(const std::string& filename) 
    {
        std::ifstream file(filename);
        std::string content;

        // Check if the file opened successfully
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return ""; // Return an empty string on failure
        }

        std::string line;
        while (std::getline(file, line)) {
            content += line + '\n'; // Append each line and add a newline character
        }

        file.close();
        return content; // Return the complete content of the file
    }
};