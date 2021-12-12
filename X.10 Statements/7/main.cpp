#include "input_helpers.hpp"

#include <fstream>
#include <iostream>
#include <istream>
#include <string>

using namespace std;

static string StripComments(istream &code);

int main()
{
    ifstream in{"main.cpp"};
    cout << StripComments(in) << endl;
}

static string StripComments(istream &code)
{
    string out;

    enum class State
    {
        normal,
        comment_line,
        comment_block,
        literal_char,
        literal_string,
        punct_quote_single,
        punct_quote_double,
        punct_slash
    } state{State::normal};

    bool done{false};
    while (!done)
    {
        switch (state)
        {
        case State::normal:
            switch (auto ch{code.get()})
            {
            case EOF: done = true; break;

            case '"': state = State::punct_quote_double; break;

            case '\'': state = State::punct_quote_single; break;

            case '/': state = State::punct_slash; break;

            default:
                out.push_back(static_cast<decltype(out)::value_type>(ch));
                break;
            }
            break;

        case State::punct_slash:
            switch (code.peek())
            {
            case '/': state = State::comment_line; break;

            case '*': state = State::comment_block; break;

            default: state = State::normal; break;
            }
            break;

        case State::punct_quote_single:
            out.push_back('\'');
            state = State::literal_char;
            break;

        case State::punct_quote_double:
            out.push_back('"');
            state = State::literal_string;
            break;

        case State::comment_line:
            if (GetUntilEx(code, '\n').back() != '\\')
            {
                out.push_back('\n');
                state = State::normal;
            }
            break;

        case State::comment_block:
            if (GetUntilEx(code, '/').back() == '*')
                state = State::normal;
            break;

        case State::literal_string:
            // TODO: Handle raw and multiline string literals
            out += GetUntilEx(code, '\"');
            if (out.back() != '\\' || out[out.size() - 2] == '\\')
                state = State::normal;
            out += '\"';
            break;

        case State::literal_char:
            // TODO: Handle multiline character literals
            out += GetUntilEx(code, '\'');
            if (out.back() != '\\' || out[out.size() - 2] == '\\')
                state = State::normal;
            out += '\'';
            break;

        default: state = State::normal; break;
        }
    }

    return out;
}
