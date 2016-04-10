#include "automatonreader.h"
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include "state.h"
#include "finitestateautomaton.h"
#include "automatonsregister.h"

AutomatonReader::AutomatonReader() {}

FiniteStateAutomaton AutomatonReader::read(std::string automaton_name, std::stringstream& ss) {
    std::list<State::ptr> states;
    std::string state_name;
    std::string symbols;
    std::string jump_name;
    std::string temp;
    bool is_reading;
    bool is_error;
    bool is_call;
    while (ss.rdbuf()->in_avail()) {
        // TODO: add checks and error handling in AutomatonReader
        ss >> state_name;
        ss >> symbols;
        ss >> jump_name;
        ss >> temp;
        is_reading =  (temp == "true") ? true : false;
        ss >> temp;
        is_error =  (temp == "true") ? true : false;
        ss >> temp;
        is_call =  (temp == "true") ? true : false;

        State::ptr state { new State(state_name, is_reading, is_error, is_call) };
        state->make_check_fn(symbols);
        states.push_back(state);
        State::Iteratator it = states.end();
        it--;
        // if something is referring as jump this state => link it
        auto jump_from = jumps.find((state_name));
        if (jump_from != jumps.end()) {
            State::Iteratator jump_it = jump_from->second;
            State::ptr jump = *jump_it;
            jump->set_jump_to(it);
        }
        if (!is_call) {
            // making jump ref
            // searching jump state in states list
            auto jump_to = std::find_if(states.begin(), states.end(),
                                        [&jump_name] (State::ptr state) -> bool {
                                            return (state->get_name() == jump_name);
                                        }
                                       );
            if (jump_to == states.end()) {
                // if state isn't created yet => remembering that it should be created
                jumps.insert({jump_name, it});
            } else {
                // else if state is found => setting jump to it
                state->set_jump_to(jump_to);
            }
        } else {
            // making call
            state->set_jump_to(AutomatonsRegister::inst().get(jump_name).get_begin());
        }
    }

    // TODO: add references check (jumps map must be empty at the end)

    return { automaton_name, std::move(states) };
}
