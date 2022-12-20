#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>


std::string Passgen(std::mt19937& gen, int length, bool symb) {

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
        else if (symb) {
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
    std::string history_file = "history.json";
    std::string password;
    std::mt19937 gen(std::random_device{}());
    int length = std::stoi(argv[1]);

    if (argc > 1 && std::string(argv[argc - 1]) == "-s") {
        bool symb = false;
        password = Passgen(gen, length, symb);
    }
    else {
        bool symb = true;
        password = Passgen(gen, length, symb);
    }

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

    if (argument == "showhistory" || argument == "sh") {
        std::ifstream infile(history_file);
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


    if (argument == "oh" || argument == "openhistory") {
        int result = system(("start " + history_file).c_str());
        if (result != 0) {
            std::cerr << "Error: could not open the history file." << std::endl;
            return 1;
        }
        return 0;
    }

    if (argc == 2) {
        if (argument == "rmh") {
            std::remove("history.json");
            std::cout << "History file removed." << std::endl;
            return 1;
        }
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

        std::string name = argv[2];
        if (j.count(name) == 0) {
            std::cerr << "Error: name not found in the password file." << std::endl;
            return 1;
        }

        j.erase(name);

        std::ofstream outfile(output_file);
        if (!outfile.good()) {
            std::cerr << "Error: could not open the password file for writing." << std::endl;
            return 1;
        }

        outfile << j;
        outfile.close();

        std::cout << name << " removed from the password file." << std::endl;
        return 0;
    }


    if ((argument == "f" || argument == "find") && argc == 3) {
        std::string name = argv[2];
        std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });

        std::ifstream infile(output_file);
        if (!infile.good()) {
            std::cerr << "Error: could not open the password file." << std::endl;
            return 1;
        }

        nlohmann::json j;
        infile >> j;
        infile.close();

        bool found = false;
        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            std::string lowercase_key = it.key();
            std::transform(lowercase_key.begin(), lowercase_key.end(), lowercase_key.begin(), [](unsigned char c) { return std::tolower(c); });
            if (lowercase_key.find(name) != std::string::npos) {
                std::cout << it.key() << ": " << it.value() << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cerr << "Error: name not found in password file." << std::endl;
            return 1;
        }
    }

    if (argc == 2) {
        try {
            if (length > 0) {
                std::mt19937 gen(std::random_device{}());

      
                std::time_t t = std::time(nullptr);
                std::tm tm; localtime_s(&tm, &t);

                std::ostringstream oss;
                oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
                std::string time_string = oss.str();

                nlohmann::json entry;
                entry[time_string] = password;

                std::ifstream infile("history.json");
                if (!infile.good()) {
                    std::cerr << "Error: could not open the history file." << std::endl;
                    std::ofstream outfile("history.json", std::ios::out);
                    if (!outfile.good()) {
                        std::cerr << "Error: could not create the history file." << std::endl;
                        return 1;
                    }
                    outfile << "[]" << std::endl;
                    outfile.close();
                    infile.open("history.json");
                }

                nlohmann::json history;
                infile >> history;
                infile.close();

                history.push_back(entry);

                std::ofstream outfile("history.json", std::ios::out);
                if (!outfile.good()) {
                    std::cerr << "Error: could not open the history file." << std::endl;
                    return 1;
                }

                outfile << history.dump(4) << std::endl;
                outfile.close();

                std::cout << password << std::endl;
            }
            else {
                std::cerr << "Error: password length must be a positive integer." << std::endl;
                return 1;
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error: password length must be a positive integer." << std::endl;
            return 1;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Error: password length must be a positive integer within the range of an int." << std::endl;
            return 1;
        }
    }

    std::string name = argv[2];
    std::random_device rd; 

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

    std::cout << "Generated password for "<< name << ": " << password << std::endl;

    return 0;
}
