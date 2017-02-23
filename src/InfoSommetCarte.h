#ifndef __INFOSOMMETCARTE
#define __INFOSOMMETCARTE

#include <string>
#include <sstream>

#include "Vecteur2D.h"

/**
 * Cette classe représente les informations relatives à un lieu d'une carte routière.
 * Pour simplifier, un lieu est défini par un nom et une position.
 */
class InfoSommetCarte
{
public:
    std::string nom;
    Vecteur2D position;

    InfoSommetCarte(const std::string & n, const Vecteur2D & pos);

    operator std::string() const;
};

std::ostream & operator<< (std::ostream & os, const InfoSommetCarte & op);

#endif
