#include "filereader.h"
#include <string>
#include <fstream>
#include <sstream>
#include "automatonreader.h"
#include "automatonsregister.h"

FileReader::FileReader(std::string filename)
 : file(filename) {}

void FileReader::read_automaton(std::string name) {
    uint32_t brackets_count = 1;
    char symbol = 0;
    std::stringstream automaton_stream;
    while (symbol != '{')
        file.get(symbol);
    do {
        file.get(symbol);
        if (symbol == '{')
            brackets_count++;
        else if (symbol == '}')
            brackets_count--;
        else automaton_stream << symbol;
    } while (brackets_count > 0);
    AutomatonsRegister::inst().push(FiniteStateAutomaton::ptr{ new FiniteStateAutomaton { name, {} } });
    AutomatonReader(AutomatonsRegister::inst().get(name)).read(automaton_stream);
}

void FileReader::read() {
    std::string str;
    while (file) {
        file >> str;
        if (str[0] == '#')
            continue;
        if (str == "def") {
            file >> str;
            read_automaton(str);
        }
    }
}
