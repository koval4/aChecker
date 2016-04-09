#include "automatonsregister.h"
#include <map>
#include <string>
#include "state.h"
#include "finitestateautomaton.h"

/**
 * @brief AutomatonsRegister::AutomatonsRegister -- hidden ctor, called only once
 */
AutomatonsRegister::AutomatonsRegister() {}

/**
* @brief inst -- used for access to singleton object
* @return -- instance of class
*/
AutomatonsRegister& AutomatonsRegister::inst() {
    static AutomatonsRegister inst;
    return inst;
}

/**
* @brief push -- moves automaton to database storage
* @param automaton -- rvalue reference to automaton to push in database
*/
void AutomatonsRegister::push(FiniteStateAutomaton&& automaton) {
    automatons.insert({ automaton.get_name(), automaton });
}

/**
* @brief get -- provides access to automaton by it's name
* @param name -- name of automaton to access
* @return -- automaton with given name
*/
FiniteStateAutomaton& AutomatonsRegister::get(std::string name) {
    return automatons.at(name);
}
