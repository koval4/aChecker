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

        struct StateData {
            std::string name;
            std::string symbols;
            std::string jump_name;
            bool is_reading;
            bool is_error;
            bool is_call;
        };

        FiniteStateAutomaton::ptr automaton;
        std::map<std::string, State::Iterator> jumps;
        std::list<Call> calls;

        StateData read_state_data(std::stringstream& ss);

    public:
        AutomatonReader(FiniteStateAutomaton::ptr automaton);

        void read(std::stringstream& ss);
};

#endif // AUTOMATONREADER_H
