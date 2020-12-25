#include "FileLoaderBMP.hpp"

Bitmap_v2 LoadBMP(const char * imagepath) {
    char file_type[2];
    uchar8_t header[54];
    uint32_t dataPos;   // position in the file where data begins; so I suppose that file[dataPos] is the first color byte ?
    uint32_t width;
    uint32_t height;
    uint32_t imageSize; // width * height * 3 for RGB
    uchar8_t* data;

    FILE* file = fopen(imagepath, "rb");
    if(!file) { fprintf(stderr, "Image not found or could not be opened.\n"); return Bitmap_v2{}; }
    else {
        printf("Loaded file successfully.\n");
        if(fread(header, 1, 54, file) != 54) { fprintf(stderr, "The header has too few bytes. Might not be a BMP file.\n"); return Bitmap_v2{}; }
        else {
                // (!?) byte ordering independent / agnostic (?!) -> "array index"-based description language
            file_type[0] = *(char*)&header[0];
            file_type[1] = *(char*)&header[1];
            dataPos = *(uint32_t*)&header[0x0A];
            width = *(uint32_t*)&header[0x12];  // /* 0E ... is there something inbetween them ?*/ /* this is for 8 bytes, not 4*/ ;  // I have the feeling that it's uint64_t not uint32_t
                    // the reference I found uses int, but int is supposed to be int32_t
            height = *(uint32_t*)&header[0x16]; // right, so it's just 4 bytes; that means there is something inbetween
            imageSize = width * height; // or read it... but why would you ?
            imageSize = *(uint32_t*)&header[0x22];  // again, a 4 byte spacing

            // author: "some BMP files are misformatted, guess missing information"
                // really now ... wtf is with these file formats ?! they are hard to understand, hard
                // to find, it's hard to find the sourrce code for the structs... and then there's also
                // often all too many variations and differences... just what the actual fuck ? and now
                // there's also misformatting
            if(imageSize == 0) imageSize = width * height * 3;
            if(dataPos == 0) dataPos = 54;  // like, what else could it even be... ? to me it seems like this
                // is just redundant data; but, likely this is a ~ of "modular hierarchical design", because as
                // long as this "equivalent to a  base class" in file format design is present, one can still
                // read the BMP (or something of it) but also extensions can be added to the file format after
                // the usual 54 byte space, because dataPos just gets changed and even a base class file loader
                // can still find the data; still, it's quite a pain to not have source code for that or something
                // diagramatic, visual, to easily understand what is where and why / what for
            data = new uchar8_t[imageSize];
            fread(data, 1, imageSize, file);    // a FILE* is a state machine (!?)
            fclose(file);
        }
        Bitmap_v2 bitmap {header, width, height, data};
        return bitmap;
    }
    return Bitmap_v2{};
}
