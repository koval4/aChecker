#ifndef AUTOMATONREADER_H
#define AUTOMATONREADER_H

#include <map>
#include <list>
#include <string>
#include <sstream>
#include "state.h"
#include "finitestateautomaton.h"

/**
 * @brief The AutomatonReader class used for reading single automaton
 */
class AutomatonReader {
    private:
        struct Call {
            std::string automaton_name; /// automaton that will be called
            State::ptr caller;          /// state that calls some automaton
        };

        std::map<std::string, State::Iteratator> jumps;
        std::list<Call> calls;

    public:
        AutomatonReader();

        FiniteStateAutomaton read(std::string automaton_name, std::stringstream ss);
};

#endif // AUTOMATONREADER_H
