#include "GElement.h"

GElement::GElement(const int & c)
                : clef(c) {}

GElement::operator std::string() const
{
    return "(clef = " + std::to_string(clef) + ")";
}

std::ostream & operator<< (std::ostream & os, const GElement & op)
{
    return os << std::string(op);
}
