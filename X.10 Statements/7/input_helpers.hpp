#ifndef INPUT_HELPERS_HPP
#define INPUT_HELPERS_HPP

#include <istream>
#include <string>

template <typename CharT>
std::string GetUntilEx(std::basic_istream<CharT> &in, CharT ch)
{
    std::basic_string<CharT> out;

    while (auto ch_in{in.get()})
    {
        if (ch_in == ch)
            break;

        out.push_back(ch_in);
    }

    return out;
}

#endif // #ifndef INPUT_HELPERS_HPP
