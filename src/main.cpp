// g++ main.cpp functions.cpp -o ../Name-ID_Linker.exe

#include <filesystem>
#include <vector>

#include "functions.h"

namespace fs = std::filesystem;

void settingsPrompt(std::istream& file, char delimiter, bool full_names) {
    std::cout << "> The following settings can be changed in 'settings.cfg'.\n";
    std::cout << "\t> Output delimiter is set to '" << "\033[1;33m" << delimiter << "\033[0m" << "'. Note that only single chars are allowed (e.g. ',').\n";
    std::cout << "\t> Toggle for outputting full names/titles is set to '" << "\033[1;33m" << full_names << "\033[0m" << "'.\n";
    std::cout << std::endl;

    system("pause");
}

std::string reString(std::string inputStr, int chars) {
    std::string newString;
    for (int i = chars; i < inputStr.size(); i++) {
        newString += inputStr.at(i);
    }
    return newString;
}

std::string whittleString(std::string inputStr, int length) {
    std::string newString;
    for (int i = 0; i < length; i++) {
        newString += inputStr.at(i);
    }
    return newString;
}

int main(int argc, char* argv[]) {
    bool error = false;

    char delimiter;
    bool full_names;

    std::ifstream cfg("settings.cfg");
    if (!cfg.is_open()) {
        std::ofstream cfg("settings.cfg");
        std::cout << "> 'settings.cfg' file created with default settings.\n";
        cfg << "delimiter=,\n";
        cfg << "full_names=0\n";
        delimiter = ',';
        full_names = 0;
    }

    std::cout << "> Reading configuration settings...\n\n";
    std::string cfg_inputStr;
    while (cfg.peek()!=EOF) {
        cfg_inputStr = getCellStr(cfg, '=');
        if (cfg_inputStr == "delimiter") {
            delimiter = getCellStr(cfg, '\n').at(0);
        } else if (cfg_inputStr == "full_names") {
            full_names = getCellInt(cfg, '\n');
        }
    }

    if (argc == 1) {
        sendError("To input a file, simply drag it onto this application.\n\n");
        error = true;
        settingsPrompt(cfg, delimiter, full_names);
        return 0;
    } else if (argc != 2) {
        sendError("Too many files! Only 1 file is accepted.\n\n");
        error = true;
        settingsPrompt(cfg, delimiter, full_names);
        return 0;
    }

    fs::path filePath = argv[1];
    std::ifstream sheet(filePath);
    if (!error) {
        if (!sheet.is_open()) {
            sendError("File '" + filePath.filename().generic_string() + "' failed to open\n\n");
            error = true;
            settingsPrompt(cfg, delimiter, full_names);
            return 0;
        }
    }

    if (!error) {
        struct linkedData {
            std::string name;
            int id;
        };
        std::vector<linkedData> item;

        std::ifstream refs;
        std::string refsFilePath;
        if (full_names) { 
            refsFilePath = "refs_full.txt";
        } else {
            refsFilePath = "refs.txt";
        }
        refs.open(refsFilePath);
        if (!refs.is_open()) {
            sendError("Reference file '" + refsFilePath + "' could not be located. Download a new one from GitHub.\n\n");
            settingsPrompt(cfg, delimiter, full_names);
            return 0;
        }

        std::cout << "> Linking names and IDs...\n\n";

        std::string inputStr;
        std::string buffer;
        std::string t_name;
        int t_id;
        while (sheet.peek()!=EOF) {
            inputStr = getCellStr(sheet, '\n');
            while (inputStr.at(0) == '(' || inputStr.at(0) == '<') {
                inputStr = reString(inputStr, 1);
            }
            inputStr = whittleString(inputStr, 6);

            refs.seekg(0, refs.beg);
            while (true) {
                buffer = getCellStr(refs, '|');
                t_name = getCellStr(refs, '|');
                t_id = getCellInt(refs, '\n');
                if (inputStr == buffer) {
                    item.push_back({t_name, t_id});
                    break;
                }
            }
        }
        refs.close();

        std::ofstream output("output.csv");
        for (int i = 0; i < item.size(); i++) {
            output << item[i].name << delimiter << item[i].id << std::endl;
        }
        std::cout << "\033[32m> Conversion complete! File has been output to 'output.csv'.\n\n\033[0m";
        output.close();
    }

    settingsPrompt(cfg, delimiter, full_names);
    return 0;
}