#ifndef __INFOARETECARTE
#define __INFOARETECARTE

#include <string>
#include <sstream>

/**
 * La classe InfoAreteCarte contient l'information associée à une arête d'une carte routière.
 * Pour simplifier, seul le coût de l'arête, c-à-d sa longueur, est noté.
 * Ce coût est supposé être un nombre réel positif ou nul.
 */
class InfoAreteCarte
{
public:
    double cout_;

    InfoAreteCarte(const double & c);

    operator std::string() const;
};

std::ostream & operator<< (std::ostream & os, const InfoAreteCarte & op);

#endif
