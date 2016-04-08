#include "finitestateautomaton.h"

FiniteStateAutomaton::FiniteStateAutomaton() {

}

FiniteStateAutomaton::FiniteStateAutomaton(std::string filename) {

}

void FiniteStateAutomaton::run(std::string line) {
    auto state = *states.begin();
    (*state)(line);
}
