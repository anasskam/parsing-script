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
        "Adresse:",
        "Ville:",
    };

    try {

        DIR* dir = opendir("../pdfs");
        dirent *ent = dir ? readdir(dir) : nullptr;
        
        if(!dir) {
            throw std::runtime_error("Can't open the directory");
            return 1; //EXIT_FAILURE
        }

        int count = 1;
        
        while((ent = readdir(dir)) != nullptr) {
            std::string fileName = ent->d_name;

            if(fileName == "." || fileName == "..") continue;

            Parser parser(fileName);
            
            std::string line;
            std::ifstream tempFile("temp.out");

            bool start = false;

            while(std::getline(tempFile, line)) {
                if(line == "Nom/Raison Sociale:") {
                   start = true;
                   continue;
                }

                if(start) {
                    auto found = std::find(exclude.begin(), exclude.end(), line);
                    if(!line.size()) continue;
                    if(found == exclude.end()) break;
                }
            }

            std::ofstream result("result.txt", std::ios_base::app);
            result << fileName << ": " << line << "\n";

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