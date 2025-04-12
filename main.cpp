#include<iostream>
#include<string>
#include<dirent.h>
#include <fstream>
#include "parser.cpp"
#include <vector>
#include <algorithm>

int main() {
    
    std::vector<std::string> exclude = {
        ":‫( ﺃﻥ‬1) ‫ﻳﺸﻬﺪ ﺍﻟﻤﺪﻳﺮ ﺍﻟﻌﺎﻡ ﻟﻠﺼﻨﺪﻭﻕ ﺍﻟﻮﻃﻨﻲ ﻟﻠﻀﻤﺎﻥ ﺍﻹﺟﺘﻤﺎﻋﻲ‬",
        ":‫ ﺍﻹﺳﻢ ﺍﻟﺘﺠﺎﺭﻱ‬/ ‫ﺍﻹﺳﻢ‬",
        ":‫ﺍﻟﻨﺸﺎﻁ ﺍﻟﻤﺰﺍﻭﻝ‬",
        "Activité exercée:",
        " ",
    };

    try {

        DIR* dir = opendir("../pdfs");
        dirent *ent = dir ? readdir(dir) : nullptr;
        
        if(!dir) {
            throw std::runtime_error("Can't open the directory");
            return 1; //EXIT_FAILURE
        }

        int readFilesFrom = 1;
        int count = 1;
        
        while((ent = readdir(dir)) != nullptr) {
            std::string fileName = ent->d_name;

            if(readFilesFrom <= 1) {
                readFilesFrom++;
                continue;
            }

            Parser parser(fileName);
            
            std::string line;
            std::ifstream tempFile("temp.out");
            std::streampos cursorPos;

            while(std::getline(tempFile, line)) {
                if(line == "Nom/Raison Sociale:") {
                    cursorPos = tempFile.tellg();
                    break;
                }
            }

            std::string nextLine;

            while(std::getline(tempFile, nextLine)) {
                auto found = std::find(exclude.begin(), exclude.end(), nextLine);

                if(!nextLine.size()) continue;
                if(found == exclude.end()) break;
                
            }

            std::ofstream result("result.txt", std::ios_base::app);

            result << fileName << ": " << nextLine << "\n";
            std::cout << count << " Passed\n";

            tempFile.close();
            result.close();
            count++;
        
        }

    } catch(const std::runtime_error& error) {
        std::cerr << error.what() << '\n';
    }
    
    return 0;
}