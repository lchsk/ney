#include <iostream>
#include "../../include/ney/ney.hpp"

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

    s = ney::open<char>("../data/file1.txt").output(text);

    // to lowercase

    s = ney::apply<char>(ney::function::lower).vector1(text);

    // vectors: one holding output and the one holding list of all letters

    ney::vector<int> counts = ney::new_vector().size(26);
    ney::vector<char> letters = ney::new_vector().size(26);

    letters[0] = 'a';
    letters[1] = 'b';
    letters[2] = 'c';
    letters[3] = 'd';
    letters[4] = 'e';
    letters[5] = 'f';
    letters[6] = 'g';
    letters[7] = 'h';
    letters[8] = 'i';
    letters[9] = 'j';
    letters[10] = 'k';
    letters[11] = 'l';
    letters[12] = 'm';
    letters[13] = 'n';
    letters[14] = 'o';
    letters[15] = 'p';
    letters[16] = 'q';
    letters[17] = 'r';
    letters[18] = 's';
    letters[19] = 't';
    letters[20] = 'u';
    letters[21] = 'v';
    letters[22] = 'w';
    letters[23] = 'x';
    letters[24] = 'y';
    letters[25] = 'z';

    if (s.success())
    {
        // count

        for (int i = letters.from(); i < letters.to(); i += letters.stride())
        {
            s = ney::count<char>(letters[i]).in(text).output(counts[i]);

            // print

            std::cout << letters[i] << " : " << counts[i] << "\n";
        }

    }
    else
    {
        std::cerr << "File does not exist\n";
        return -1;
    }

    // print time

    ney::clock::get().end().print();

    return 0;
}
