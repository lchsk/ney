#include <iostream>
#include "../include/ney/ney.hpp"

//! Counts how many words there are in a file

int main (int argc, char** argv)
{
    std::cout << "\nCounts how many words there are in a file\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    ney::vector<char> text;

    // open file

    std::string path = "./data/file1.txt";

    s = ney::open<char>(path).output(text).as_text();

    ney::vector<bool> o = ney::new_vector().size(text.size());

    if (s.success())
    {
        s = ney::compare<char>()
            .vector1(text)
            .vector2(text.from(1))
            .output(o)
            .condition(ney::condition::letter_space);

        int count = 0;

        s = ney::count<bool>(true).in(o).output(count);

        std::cout << "number of words in " << path << "\n" << count << "\n\n";

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
