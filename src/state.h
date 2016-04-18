#ifndef STATE_H
#define STATE_H

#include <string>
#include <list>
#include <memory>
#include <functional>
#include <iterator>

class State {
    public:
        using ptr = std::shared_ptr<State>;
        using Iterator = std::list<State::ptr>::iterator;

    private:
        std::string name;
        std::function<bool(char)> check;
        bool is_reading;
        bool is_error;
        bool is_call;
        Iterator jump_to;

        std::string error_msg;

    public:
        State();
        State( std::string name
             , bool is_reading = false
             , bool is_error = false
             , bool is_call = false
             );
        State( std::string name
             , std::function<bool(char)> check
             , bool is_reading = false
             , bool is_error = false
             , bool is_call = false
             );

        std::string get_name() const;

        void set_jump_to(Iterator jump_to);

        void make_check_fn(std::string symbols);

        /**
         * @brief operator () -- checks first symbol of line with check f-n and processing it
         * @param line -- line to check and process
         * @return -- ptr to next state (jump of nullptr for next in collection)
         */
        Iterator operator () (std::string& line);

        void run_automaton(Iterator state_iter, std::string& line);
};

#endif // STATE_H
