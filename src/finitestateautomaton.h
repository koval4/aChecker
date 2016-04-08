#ifndef FINITESTATEAUTOMATON_H
#define FINITESTATEAUTOMATON_H

#include <list>
#include <string>
#include "state.h"

class FiniteStateAutomaton {
    private:
        std::list<State::ptr> states;

    public:
        FiniteStateAutomaton();
        FiniteStateAutomaton(std::string filename);

        void run(std::string line);
};

#endif // FINITESTATEAUTOMATON_H
