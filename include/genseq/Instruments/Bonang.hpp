#ifndef BONANG_H
#define BONANG_H

#include <genseq/Instrument.hpp>

class Bonang : public Instrument {
public:
    Bonang() {
        Init();
        SetScale(Laras::Pelog);
    }

    Bonang(Laras laras) {
        Init();
        SetScale(laras);
    }

    void Init() {
        assignPelogNotes();
        assignSlendroNotes();
    }

    void assignPelogNotes() {
        mPelogNotes["0"] = {0}; 
        mPelogNotes["1"] = {64}; 
        mPelogNotes["2"] = {65}; 
        mPelogNotes["3"] = {67}; 
        mPelogNotes["4"] = {69}; 
        mPelogNotes["5"] = {71};
        mPelogNotes["6"] = {72};
        mPelogNotes["7"] = {74};
        mPelogNotes["1h"] = {76};
        mPelogNotes["2h"] = {77};
        mPelogNotes["3h"] = {79};
        mPelogNotes["4h"] = {81};
        mPelogNotes["5h"] = {83};
        mPelogNotes["6h"] = {84};
        mPelogNotes["7h"] = {86};
    }

    void assignSlendroNotes() {
        mSlendroNotes["0"] = 0; 
        mSlendroNotes["2"] = 66;
        mSlendroNotes["3"] = 68;
        mSlendroNotes["5"] = 70;
        mSlendroNotes["6"] = 73;
        mSlendroNotes["1"] = 75;
        mSlendroNotes["2h"] = 78;
        mSlendroNotes["3h"] = 80;
        mSlendroNotes["5h"] = 82;
        mSlendroNotes["6h"] = 85;
        mSlendroNotes["1h"] = 87;
    }
};
#endif /* BONANG_H */
