#include "InfoSommetCarte.h"

InfoSommetCarte::InfoSommetCarte(const std::string & n, const Vecteur2D & pos)
                                : nom(n), position(pos) {}

InfoSommetCarte::operator std::string() const
{
    std::ostringstream stream;
    stream << "(" << "nom = " << nom
                << " ; position = " << position << ")";
    return stream.str();
}

std::ostream & operator<< (std::ostream & os, const InfoSommetCarte & op)
{
    return os << std::string(op);
}
