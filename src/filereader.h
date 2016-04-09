#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>
#include <sstream>

class FileReader {
    private:
        std::ifstream file;

        void read_automaton(std::string name);
    public:
        FileReader(std::string filename);
        void read();
};

#endif // FILEREADER_H
