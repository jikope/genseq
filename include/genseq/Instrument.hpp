#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include <string>
#include <memory>
#include <unordered_map>

enum class Laras {
    Pelog,
    Slendro
};

struct note {
    int index;
    int midiNote;
};

class Instrument
{
public:
    virtual void assignPelogNotes() = 0;
    virtual void assignSlendroNotes() = 0;

    int operator[](const std::string &key) {
        return (*currentScale)[key];
    }

    void SetScale(Laras scale);

protected:
    typedef std::unordered_map<std::string, int> noteMapping;
    std::unique_ptr<noteMapping> currentScale;
    noteMapping mSlendroNotes;
    noteMapping mPelogNotes;
};


#endif /* INSTRUMENT_H */
