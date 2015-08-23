#include <iostream>
#include "../include/ney/ney.hpp"

//! Some image effects

#define dtype unsigned char

struct image_bmp
{
    int size;
    int width;
    int height;
    ney::vector<unsigned char> header;
    ney::vector<dtype> data;
};

void readBMP(const char* filename, struct image_bmp& frame)
{
    FILE* f = fopen(filename, "rb");

    frame.header = ney::new_vector().size(54);

    fread(frame.header.raw(), sizeof(unsigned char), 54, f);

    // little endian

    int width = *(int*) &frame.header[18];
    int height = *(int*) &frame.header[22];
    frame.width = width;
    frame.height = height;

    int size = 3 * width * height;
    frame.size = size;

    frame.data = ney::new_vector().size(size);

    fread(frame.data.raw(), sizeof(dtype), size, f);

    fclose(f);
}

void saveBMP(const char* filename, struct image_bmp& frame)
{
    FILE* f = fopen(filename, "wb");

    fwrite(frame.header.raw(), sizeof(unsigned char), 54, f);
    fwrite(frame.data.raw(), sizeof(unsigned char), frame.size, f);

    fclose(f);
}

int main (int argc, char** argv)
{
    std::cout << "\n\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    struct image_bmp img;

    const char* input = "./data/cat.bmp";
    const char* out_gray = "./data/cat_gray.bmp";
    const char* out_color = "./data/cat_color.bmp";
    const char* out_dark = "./data/cat_dark.bmp";
    const char* out_stripes = "./data/cat_stripes.bmp";

    readBMP(input, img);

    ney::vector<dtype> copy1(img.data);

    // print information about input image

    std::cout << "File: " << input << std::endl;
    std::cout << "Size: " << img.size << std::endl;
    std::cout << "Width: " << img.width << std::endl;
    std::cout << "Height: " << img.height << std::endl << std::endl;

    img.data.reset().stride(3);

    // grayscale

    s = ney::apply<dtype>(ney::operation::mul).vector1(img.data.from(0)).d_value(0.11);
    s = ney::apply<dtype>(ney::operation::mul).vector1(img.data.from(1)).d_value(0.59);
    s = ney::apply<dtype>(ney::operation::mul).vector1(img.data.from(2)).d_value(0.3);

    dtype g;

    for (int i = 0; i < img.data.to(); i += img.data.stride())
    {
        g = img.data[i] + img.data[i + 1] + img.data[i + 2];

        img.data[i] = g;
        img.data[i + 1] = g;
        img.data[i + 2] = g;
    }

    //
    saveBMP(out_gray, img);
    std::cout << "Saved file: " << out_gray << std::endl;

    // dark

    s = ney::apply<dtype>(ney::operation::mul).vector1(copy1.from(0)).d_value(0.4);

    img.data = copy1;
    saveBMP(out_dark, img);
    std::cout << "Saved file: " << out_dark << std::endl;

    // change colors

    readBMP(input, img);

    img.data.reset();
    img.data.stride(3);

    s = ney::apply<dtype>(ney::function::sine).vector1(img.data.from(0));
    s = ney::apply<dtype>(ney::function::sine).vector1(img.data.from(1));

    saveBMP(out_color, img);
    std::cout << "Saved file: " << out_color << std::endl;

    // stripes

    readBMP(input, img);

    img.data.reset();
    img.data.stride(9);

    s = ney::apply<dtype>(ney::operation::mul).vector1(img.data.from(0)).d_value(0.4);
    s = ney::apply<dtype>(ney::operation::mul).vector1(img.data.from(1)).d_value(0.7);
    s = ney::apply<dtype>(ney::operation::mul).vector1(img.data.from(2)).d_value(0.5);

    saveBMP(out_stripes, img);
    std::cout << "Saved file: " << out_stripes << std::endl << std::endl;

    // print time

    ney::clock::get().end().print();

    return 0;
}
