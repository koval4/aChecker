#ifndef FINITESTATEAUTOMATON_H
#define FINITESTATEAUTOMATON_H

#include <memory>
#include <list>
#include <string>
#include "state.h"

class FiniteStateAutomaton {
    public:
        using ptr = std::shared_ptr<FiniteStateAutomaton>;

    private:
        std::string name;
        std::list<State::ptr> states;

    public:
        FiniteStateAutomaton();
        FiniteStateAutomaton(std::string name, std::list<State::ptr>&& states);

        std::string get_name() const;
        State::Iterator get_begin();
        std::list<State::ptr>& get_states();

        void add_state(State::ptr state);

        void run(std::string line);
};

#endif // FINITESTATEAUTOMATON_H
