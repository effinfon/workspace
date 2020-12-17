#ifndef VERSIONCONTROL_HPP_INCLUDED
#define VERSIONCONTROL_HPP_INCLUDED

#include <filesystem>
#include <string>

/// TD
/*
    file-wise versioning, with a diff visualization tool
    somehow identify "relevant diffs"
    diffs might (!*) include a suite of analyses done, to test what worked and how
        // well (for example performance benchmarks, static analyses, coverage analyses, whatever metrics, etc.)
    integrated into the IDE, of course; the IDE should also integrate a database, a "general / system AI" and
        // multiple sub-AIs ("specialized AIs")
*/

struct Repository {
    // list of files and their metadata, with hash and CRC of the entry itself (?)
    //
};

#endif // VERSIONCONTROL_HPP_INCLUDED
