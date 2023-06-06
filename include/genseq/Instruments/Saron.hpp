#ifndef SARON_H
#define SARON_H

#include <genseq/Instrument.hpp>

class Saron : public Instrument {
public:
    Saron() {
        Init();
        SetScale(Laras::Pelog);
    }

    Saron(Laras laras) {
        Init();
        SetScale(laras);
    }

    void Init() {
        assignPelogNotes();
        assignSlendroNotes();
    }

    void assignPelogNotes() {
        mPelogNotes["1"] = 72;
        mPelogNotes["2"] = 74;
        mPelogNotes["3"] = 76;
        mPelogNotes["4"] = 77;
        mPelogNotes["5"] = 79;
        mPelogNotes["6"] = 81;
        mPelogNotes["7"] = 83;
    }

    void assignSlendroNotes() {
        mSlendroNotes["1"] = 70;
        mSlendroNotes["2"] = 73;
        mSlendroNotes["3"] = 75;
        mSlendroNotes["5"] = 78;
        mSlendroNotes["6"] = 80;
        mSlendroNotes["1h"] = 82;
    }
};
#endif /* SARON_H */
