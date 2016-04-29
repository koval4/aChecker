#include "finitestateautomaton.h"
#include <memory>
#include <list>
#include <string>
#include "state.h"
#include "parseexception.h"

FiniteStateAutomaton::FiniteStateAutomaton() {

}

FiniteStateAutomaton::FiniteStateAutomaton(std::string name
                                          , std::list<State::ptr>&& states
                                          )
    : name(name)
    , states(states) {}

std::string FiniteStateAutomaton::get_name() const {
    return name;
}

State::Iterator FiniteStateAutomaton::get_begin() {
    return states.begin();
}

std::list<State::ptr>& FiniteStateAutomaton::get_states() {
    return states;
}

void FiniteStateAutomaton::add_state(State::ptr state) {
    states.push_back(state);
}

void FiniteStateAutomaton::run(std::string line) {
    auto state = *states.begin();
    size_t pos = 0;
    state->run_automaton(states.begin(), line, pos);
    if (!line.empty())
        throw ParseException { line, "end of line", 0 };
}
