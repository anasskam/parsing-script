#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class Parser {

public:
    Parser(const std::string& filePath): m_FilePath(filePath) {
        init();
    }

private:
    void init() {
        try {
            std::string cmd = "pdftotext -f 1 -l 1 ../pdfs/" + m_FilePath + " temp.out";
            
            int status = system(cmd.c_str());

            if(status == 1) throw std::runtime_error("Text extraction failed.");

        } catch(const std::runtime_error& error) {
            std::cerr << error.what() << '\n';
        }
    }
    std::string m_FilePath;
};