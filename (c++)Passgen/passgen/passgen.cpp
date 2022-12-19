#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <nlohmann/json.hpp>

std::string Passgen(std::mt19937& gen, int length) {
    std::string password;
    std::uniform_int_distribution<> random(0, 9);
    std::uniform_int_distribution<> random_lower(97, 122);
    std::uniform_int_distribution<> random_upper(65, 90);
    std::uniform_int_distribution<> random_symbol(35, 47);

    for (int i = 0; i < length; i++) {
        int r = std::uniform_int_distribution<>(0, 3)(gen);
        if (r == 0) {
            password += std::to_string(random(gen));
        }
        else if (r == 1) {
            char c = (char)random_lower(gen);
            password += c;
        }
        else if (r == 2) {
            char c = (char)random_upper(gen);
            password += c;
        }
        else if (r == 3) {
            char c = (char)random_symbol(gen);
            password += c;
        }
    }

    return password;
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        std::cerr << "Usage: passgen <password length> <name>" << std::endl;
        return 1;
    }

    std::string argument = argv[1];
    std::string output_file = "password.json";

    if (argument == "show" || argument == "s") {
        std::ifstream infile(output_file);
        if (!infile.good()) {
            std::cerr << "Error: could not open the password file." << std::endl;
            return 1;
        }

        nlohmann::json j;
        infile >> j;
        infile.close();

        std::cout << j.dump(4) << std::endl;
        return 0;
    }

    if (argument == "o" || argument == "open") {
        int result = system(("start " + output_file).c_str());
        if (result != 0) {
            std::cerr << "Error: could not open the password file." << std::endl;
            return 1;
        }
        return 0;
    }

    if (argument == "rm" || argument == "remove") {

        if (argc != 3) {
            std::cerr << "Error: please specify a name to remove." << std::endl;
            return 1;
        }

        std::ifstream infile(output_file);
        if (!infile.good()) {
            std::cerr << "Error: could not open the password file." << std::endl;
            return 1;
        }

        nlohmann::json j;
        infile >> j;
        infile.close();

        std::string lowercase_convert = argv[2];
        std::transform(lowercase_convert.begin(), lowercase_convert.end(), lowercase_convert.begin(), [](unsigned char c) { return std::tolower(c); });


        bool removed = false;
        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            std::string lowercase_key = it.key();
            std::transform(lowercase_key.begin(), lowercase_key.end(), lowercase_key.begin(), [](unsigned char c) { return std::tolower(c); });
            if (lowercase_key == lowercase_convert) {
                j.erase(it);
                removed = true;
                break;
            }
        }

        if (removed) {
            std::cerr << lowercase_convert << ": removed successfully." << std::endl;
            return 1;
        }

        if (!removed) {
            std::cerr << "Error: name not found in the password file." << std::endl;
            return 1;
        }

        std::ofstream outfile(output_file);
        outfile << std::setw(4) << j << std::endl;
        outfile.close();

        return 0;
    }

    int length = std::stoi(argv[1]);

    std::string name = argv[2];
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::string password = Passgen(gen, length);

    nlohmann::json j;
    std::ifstream infile(output_file);
    if (infile.good()) {
        infile >> j;
    }
    infile.close();

    if (j.count(name) > 0) {
        std::cerr << "Error: name already exists in the password file. Please choose a different name." << std::endl;
        return 1;
    }

    j[name] = password;

    std::ofstream outfile(output_file);
    outfile << std::setw(4) << j << std::endl;
    outfile.close();

    std::cout << "Generated password: " << password << std::endl;

    return 0;
}
