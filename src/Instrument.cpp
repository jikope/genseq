#include <genseq/Instrument.hpp>

void Instrument::SetScale(Laras scale) {
    if (scale == Laras::Pelog) 
        currentScale = std::make_unique<noteMapping>(mPelogNotes);
    else
        currentScale = std::make_unique<noteMapping>(mSlendroNotes);
}
