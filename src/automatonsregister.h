#ifndef AUTOMATONSREGISTER_H
#define AUTOMATONSREGISTER_H

#include <map>
#include <string>
#include "state.h"
#include "finitestateautomaton.h"

/**
 * @brief The AutomatonsRegister class is singleton that contains database with used automatons
 * Just a simple wrapper to provide global visibility and single instance
 */
class AutomatonsRegister {
    private:
        /// Automaton name used as a key
        std::map<std::string, FiniteStateAutomaton> automatons;

        // hiding constructor for singleton realization
        AutomatonsRegister();
    public:
        /**
         * @brief inst -- used for access to singleton object
         * @return -- instance of class
         */
        static AutomatonsRegister& inst();

        //################### AUTOMATONS OPERATIONS #####################

        /**
         * @brief push -- moves automaton to database storage
         * @param automaton -- rvalue reference to automaton to push in database
         */
        void push(FiniteStateAutomaton&& automaton);
        /**
         * @brief get -- provides access to automaton by it's name
         * @param name -- name of automaton to access
         * @return -- automaton with given name
         */
        FiniteStateAutomaton& get(std::string name);
};

#endif // AUTOMATONSREGISTER_H
