#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED

/// TD
/*
    render symbols
    (*?) how does this generalize to any of the other font renderers, for example in a terminal, in a game, in a browser, etc. (?)
    use ML to "learn a font from training data", for example handwritten data; now, there are a few options: write cursively, mimic
        handwritting, actually spawn variaties of "glyphs" for the same "symbol", etc.
    a ML that learns to recognize what letter a symbol is, from multiple possible input fonts (not necessarely also know the font because
        that's not what interests me
    dynamically learn a font through ML (the point would be that given just a part of a font, for the model to extrapolate what the other
        letters ought to probably look like; this could help with photo-editing of documents when the same font is desired to be used)
    replacing the font in an image / document, using ML -> especially for digitalizing old books (any books -> strings of symbols occupy
        less space than pixels / glyphs do)

*/
/*
    (*?) a progam shouldn't need to be either completly ASCI or completly Unicode (and even then maybe having to chose the encoding or something ?);
        instead I'd rather have a local declaration syntax for explicitating what is which
    (*?) still, then there's the template programming that integrates with types, which has to decide which functions ought to be called -> the same
        alias with multiple "type overloads" (*!?) vs their macro ~ #ifdef Unicode then #define callFunc callFuncUnicode #else then #define callFunc callFuncASCI

*/

#endif // FONT_HPP_INCLUDED
