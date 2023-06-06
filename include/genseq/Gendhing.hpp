#ifndef GENDHING_H
#define GENDHING_H

#include "genseq/Instrument.hpp"
#include <vector>
#include <string>

class Gendhing {
public:
    Gendhing(
             const std::string& title,
             Laras laras,
             const std::vector<std::string>& notation
             ) : m_Laras(laras), m_Title(title), m_Notation(notation)
    {}

    Laras m_Laras;
    std::string m_Title;
    std::vector<std::string> m_Notation;
};

#endif /* GENDHING_H */
