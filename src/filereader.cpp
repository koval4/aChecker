#include "filereader.h"
#include <string>
#include <fstream>
#include <sstream>
#include "automatonreader.h"
#include "automatonsregister.h"

FileReader::FileReader(std::string filename)
 : file(filename) {}

void FileReader::read_automaton(std::string name) {
    uint32_t brackets_count = 0;
    char symbol;
    std::stringstream automaton_stream;
    do {
        file.get(symbol);
        if (symbol == '{')
            brackets_count++;
        else if (symbol == '}')
            brackets_count--;
        else automaton_stream << symbol;
    } while (brackets_count > 0);
    AutomatonsRegister::inst().push(AutomatonReader().read(name, automaton_stream));
}

void FileReader::read() {
    std::string str;
    while (file.rdbuf()->in_avail()) {
        file >> str;
        read_automaton(str);
    }
}
