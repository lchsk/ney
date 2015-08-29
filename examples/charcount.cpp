#include <iostream>
#include "../include/ney/ney.hpp"

//! A simple program that opens a text file, changes text to lowercase and counts occurences of each letter

int main (int argc, char** argv)
{
    std::cout << "\nA simple program that opens a text file, changes text to lowercase and counts occurences of each letter\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    ney::vector<char> text;

    // open file

    s = ney::open<char>("./data/file1.txt").output(text).as_text();

    if (s.success())
    {
        // to lowercase

        s = ney::apply<char>(ney::function::lower).vector1(text);

        // vectors: one holding output and the one holding list of all letters

        ney::vector<int> counts = ney::new_vector().size(26);
        ney::vector<char> letters = ney::new_vector().size(26);

        letters << 'a' << 'b' << 'c' << 'd' << 'e' << 'f' << 'g' << 'h' << 'i' << 'j' << 'k' << 'l' << 'm' << 'n' << 'o' << 'p' << 'q' << 'r' << 's' << 't' << 'u' << 'v' << 'w' << 'x' << 'y' << 'z';

        for (int i = letters.from(); i < letters.to(); i += letters.stride())
        {
            s = ney::count<char>(letters[i]).in(text).output(counts[i]);

            // print

            std::cout << letters[i] << " : " << counts[i] << "\n";
        }
    }
    else
    {
        std::cerr << s.error() << std::endl;;
        return -1;
    }

    // print time

    ney::clock::get().end().print();

    return 0;
}
