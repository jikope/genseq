#ifndef KEMPUL_H
#define KEMPUL_H

#include <genseq/Instrument.hpp>

class Kempul : public Instrument {
public:
    Kempul() {
        Init();
        SetScale(Laras::Pelog);
    }

    Kempul(Laras laras) {
        Init();
        SetScale(laras);
    }

    void Init() {
        assignPelogNotes();
        assignSlendroNotes();
    }

    void assignPelogNotes() {
        mPelogNotes["G"] = 43;
        mPelogNotes["1"] = 64;
        mPelogNotes["2"] = 65; // Suwuk
        mPelogNotes["3"] = 67; // Suwuk
        mPelogNotes["5"] = 71;
        mPelogNotes["6"] = 72;
        mPelogNotes["7"] = 74;
    }

    void assignSlendroNotes() {
        mSlendroNotes["G"] = 43;
        mSlendroNotes["2S"] = 54;
        mSlendroNotes["1S"] = 58;
        mSlendroNotes["1"] = 63;
        mSlendroNotes["2"] = 66;
        mSlendroNotes["3"] = 68;
        mSlendroNotes["5"] = 70;
        mSlendroNotes["6"] = 73;
    }
};

#endif /* KEMPUL_H */
