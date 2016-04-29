#include "state.h"
#include <string>
#include <list>
#include <memory>
#include <functional>
#include <iterator>
#include "parseexception.h"

State::State()
    : name()
    , check()
    , is_reading(false)
    , is_error(false)
    , is_call(false)
    , jump_to() {}

State::State( std::string name
            , bool is_reading
            , bool is_error
            , bool is_call
            )
    : name(name)
    , check()
    , is_reading(is_reading)
    , is_error(is_error)
    , is_call(is_call)
    , jump_to() {}

State::State( std::string name
            , std::function<bool (char)> check
            , bool is_reading
            , bool is_error
            , bool is_call
            )
    : name(name)
    , check(check)
    , is_reading(is_reading)
    , is_error(is_error)
    , is_call(is_call)
    , jump_to() {}

std::string State::get_name() const {
    return name;
}

void State::set_jump_to(Iterator jump_to) {
    this->jump_to = jump_to;
}

void State::make_check_fn(std::string symbols) {
    expected = symbols;
    if (symbols == "[:digit:]")
        check = [] (char symbol) -> bool {
            return isdigit(symbol);
        };
    else if (symbols == "[:letter:]")
        check = [] (char symbol) -> bool {
            return isalpha(symbol);
        };
    else if (symbols == "[:alphanum:]")
        check = [] (char symbol) -> bool {
            return isalnum(symbol);
        };
    else if (symbols == "[:any:]")
        check = [] (char symbol) -> bool {
            symbol = 0; // just to remove warning about unused variable
            return true;
        };
    else
        check = [symbols] (char symbol) -> bool {
            return symbols.find(symbol) != std::string::npos;
        };
}

State::Iterator State::operator ()(std::string& line, size_t pos) {
    if (check(line[0])) {
        if (is_reading) {
            line.erase(0, 1);
            pos++;
        }
        if (is_call) {
            run_automaton(jump_to, line, pos);
            return Iterator();
        } else return jump_to;
    } else {
        if (is_error)
            throw ParseException { line, expected, pos };
        return Iterator();
    }
}

void State::run_automaton(Iterator state_iter, std::string& line, size_t& pos) {
    auto end = Iterator();
    while ((*state_iter)->name != "end") {
        auto state = *state_iter;
        auto next = (*state)(line, pos);
        if (next != end)
            state_iter = next;
        else state_iter++;
    }
}
