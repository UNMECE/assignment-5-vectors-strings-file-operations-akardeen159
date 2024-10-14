#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "pixel.h"

std::vector<Pixel> pixel_list;

void read_data(const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;

    if (!infile) {
        std::cerr << "error opening file" << std::endl;
        return;
    }

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string token;
        Pixel p;

        std::getline(ss, token, ',');
        p.x = std::stoi(token);

        std::getline(ss, token, ',');
        p.y = std::stoi(token);

        std::getline(ss, token, ',');
        p.r = std::stof(token);

        std::getline(ss, token, ',');
        p.g = std::stof(token);

        std::getline(ss, token, ',');
        p.b = std::stof(token);

        pixel_list.push_back(p);
    }
    infile.close();
}

void flip_vertically(std::vector<Pixel>& pixel_list) {
    int y_max = 256 - 1;
    for (auto& p : pixel_list) {
        p.y = y_max - p.y;
    }
}

void save_flipped(const std::string& filename, const std::vector<Pixel>& pixel_list) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "error opening file" << std::endl;
        return;
    }

    for (const auto& p : pixel_list) {
        outfile << p.x << "," << p.y << "," << p.r << "," << p.g << "," << p.b << std::endl;
    }
    outfile.close();
}

void average_colors(const std::vector<Pixel>& pixel_list) {
    float total_r = 0.0, total_g = 0.0, total_b = 0.0;
    for (const auto& p : pixel_list) {
        total_r += p.r;
        total_g += p.g;
        total_b += p.b;
    }
    int total_pixels = pixel_list.size();
    std::cout << "Average R: " << total_r / total_pixels << std::endl;
    std::cout << "Average G: " << total_g / total_pixels << std::endl;
    std::cout << "Average B: " << total_b / total_pixels << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_name>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    read_data(filename);
    std::cout << "Successfully loaded " << pixel_list.size() << " pixels from " << filename << "\n";

    average_colors(pixel_list);
    flip_vertically(pixel_list);
    save_flipped("flipped.dat", pixel_list);

    return 0;
}

