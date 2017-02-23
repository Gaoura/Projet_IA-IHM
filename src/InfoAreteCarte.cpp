#include "InfoAreteCarte.h"

InfoAreteCarte::InfoAreteCarte(const double & c)
                                : cout_(c) {}

InfoAreteCarte::operator std::string() const
{
    std::ostringstream stream;
    stream << "(" << "coût = " << cout_ << ")";
    return stream.str();
}

std::ostream & operator<< (std::ostream & os, const InfoAreteCarte & op)
{
    return os << std::string(op);
}
