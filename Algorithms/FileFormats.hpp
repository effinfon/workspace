#ifndef FILEFORMATS_HPP_INCLUDED
#define FILEFORMATS_HPP_INCLUDED

/// TD
/*
    text -> ASCII, UTF-8, UTF-16, UTF-32, etc.
    bitmap -> grayscale, RGB, RGBA, YCrCb, etc.
    sound -> ? (I suppose this is based on the number of bits allocated per sample's amplitude)
        // and then there is the frequency, but that's more like a global variable for the file
        // or some segment of the file -> there's the possibility for synchronous, multi-frequency
        // and multi-precision "channels" (basically sound samples that occur simultaneously, thus
        // "channels", like "color layers" in bitmaps) => Bitmaps could also have different precision
        // for each layer (?!)
    folder
    executable (?!)
    partition table
    master boot table
    GUID partition table
*/

#endif // FILEFORMATS_HPP_INCLUDED
