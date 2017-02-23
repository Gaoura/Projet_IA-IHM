#ifndef __SOMMET
#define __SOMMET

#include <sstream>

#include "GElement.h"

/**
 * Sommet d'un graphe en général
 * v est l'information associée au sommet : elle dépend de l'application du graphe
 **/
template <class T>
class Sommet : public GElement
{
public:
    int degre;  // représente le degré du sommet
    T v;      // représente l'information associée au sommet

    Sommet(const int & c, const T & val);

    operator std::string() const;
};

/*
/////////////////////////////////////////////////////////////////////////////////////////////

  ########  ######## ######## #### ##    ## #### ######## ####  #######  ##    ##  ######
  ##     ## ##       ##        ##  ###   ##  ##     ##     ##  ##     ## ###   ## ##    ##
  ##     ## ##       ##        ##  ####  ##  ##     ##     ##  ##     ## ####  ## ##
  ##     ## ######   ######    ##  ## ## ##  ##     ##     ##  ##     ## ## ## ##  ######
  ##     ## ##       ##        ##  ##  ####  ##     ##     ##  ##     ## ##  ####       ##
  ##     ## ##       ##        ##  ##   ###  ##     ##     ##  ##     ## ##   ### ##    ##
  ########  ######## ##       #### ##    ## ####    ##    ####  #######  ##    ##  ######

/////////////////////////////////////////////////////////////////////////////////////////////
*/

template <class T>
Sommet<T>::Sommet(const int & c, const T & val)
                : GElement(c), degre(0), v(val) {}

template <class T>
Sommet<T>::operator std::string() const
{
    // l'hypothèse est faite que la classe T est munie de l'opérateur << d'écriture sur un flux
    std::ostringstream stream;
    stream << "(" << GElement::operator std::string()
            << " ; degre = " << degre
            << " ; v = " << v << ")";
    return stream.str();
}

template <class T>
std::ostream & operator<< (std::ostream & os, const Sommet<T> & op)
{
    return os << std::string(op);
}


#endif
