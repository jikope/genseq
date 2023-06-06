#ifndef KENONG_H
#define KENONG_H

#include <genseq/Instrument.hpp>

class Kenong : public Instrument {
public:
    Kenong() {
        Init();
        SetScale(Laras::Pelog);
    }

    Kenong(Laras laras) {
        Init();
        SetScale(laras);
    }

    void Init() {
        assignPelogNotes();
        assignSlendroNotes();
    }

    void assignPelogNotes() {
        mPelogNotes["kt"] = 51;
        mPelogNotes["kp"] = 87;
        mPelogNotes["2"] = 69; 
        mPelogNotes["3"] = 71;
        mPelogNotes["5"] = 74;
        mPelogNotes["6"] = 76;
        mPelogNotes["7"] = 77;
        mPelogNotes["1"] = 79;
    }

    void assignSlendroNotes() {
        mSlendroNotes["kt"] = 56;
        mSlendroNotes["2"] = 68;
        mSlendroNotes["3"] = 70;
        mSlendroNotes["5"] = 73;
        mSlendroNotes["6"] = 75;
        mSlendroNotes["1"] = 78;
        mSlendroNotes["2"] = 80;
    }
};
#endif /* KENONG_H */
