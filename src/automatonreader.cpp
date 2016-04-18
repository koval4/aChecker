#include "automatonreader.h"
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include "state.h"
#include "finitestateautomaton.h"
#include "automatonsregister.h"

AutomatonReader::AutomatonReader(FiniteStateAutomaton::ptr automaton)
    : automaton(automaton) {}

AutomatonReader::StateData AutomatonReader::read_state_data(std::stringstream& ss) {
    // TODO: add checks and error handling in AutomatonReader
    StateData data;
    std::string temp;
    ss >> data.name;
    ss >> data.symbols;
    ss >> data.jump_name;
    ss >> temp;
    data.is_reading =  (temp == "true") ? true : false;
    ss >> temp;
    data.is_error =  (temp == "true") ? true : false;
    ss >> temp;
    data.is_call =  (temp == "true") ? true : false;

    return data;
}

void AutomatonReader::read(std::stringstream& ss) {
    std::list<State::ptr>& states = automaton->get_states();
    while (ss.rdbuf()->in_avail()) {
        StateData data = read_state_data(ss);
        State::ptr state { new State(data.name, data.is_reading, data.is_error, data.is_call) };
        state->make_check_fn(data.symbols);
        states.push_back(state);
        State::Iterator it = std::prev(states.end());
        // if something is referring as jump this state => link it
        auto jump_from = jumps.find(state->get_name());
        if (jump_from != jumps.end()) {
            State::Iterator jump_it = jump_from->second;
            State::ptr jump = *jump_it;
            jump->set_jump_to(it);
        }
        if (!data.is_call) {
            // making jump ref
            // searching jump state in states list
            auto jump_to = std::find_if(states.begin(), states.end(),
                                        [&data] (State::ptr state) -> bool {
                                            return (state->get_name() == data.jump_name);
                                        }
                                       );
            if (jump_to == states.end()) {
                // if state isn't created yet => remembering that it should be created
                jumps.insert({data.jump_name, it});
            } else {
                // else if state is found => setting jump to it
                state->set_jump_to(jump_to);
            }
        } else {
            // making call
            state->set_jump_to(AutomatonsRegister::inst().get(data.jump_name)->get_begin());
        }
    }

    // TODO: add references check (jumps map must be empty at the end)
}
