#include "finitestateautomaton.h"

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
    state->run_automaton(states.begin(), line);
}
