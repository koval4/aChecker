#ifndef FINITESTATEAUTOMATON_H
#define FINITESTATEAUTOMATON_H

#include <list>
#include <string>
#include "state.h"

class FiniteStateAutomaton {
    private:
        std::string name;
        std::list<State::ptr> states;

    public:
        FiniteStateAutomaton();
        FiniteStateAutomaton(std::string name, std::list<State::ptr>&& states);

        std::string get_name() const;
        State::Iteratator get_begin();

        void add_state(State::ptr state);

        void run(std::string line);
};

#endif // FINITESTATEAUTOMATON_H
