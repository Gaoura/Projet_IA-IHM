#ifndef __ARETE
#define __ARETE

#include "GElement.h"
#include "Sommet.h"

/**
 * représente une arête d'un graphe en général.
 * Une arête est définie par un sommet-début et par un sommet-fin et par une information v.
 *
 * On ne connait pas la nature de v à ce niveau (v pourrait contenir une couleur, une longueur, un nom, etc.)
 *
 * T est la nature de l'information portée par un sommet et
 * S est la nature de l'information portée par une arête
 **/
template <class S, class T>
class Arete : public GElement
{
public:
    Sommet<T> * debut;  // représente un pointeur sur l'extrémité initiale de l'arête
    Sommet<T> * fin;    // représente un pointeur sur l'extrémité finale de l'arête
    S v;                // représente l'information associée à l'arête

    Arete(const int &, Sommet<T> *, Sommet<T> *, const S &);

    operator std::string() const;

    /**
     * vérifie si *this s'appuie sur s1 et s2
     *
     * DONNEES : *this, s1, s2
     *
     * RESULTATS : true si *this s'appuie sur s1 et s2
     * c'est-à-dire si (début == s1 et fin == s2) ou (début == s2 et fin == s1),
     * false sinon
     **/
    bool estEgal(const Sommet<T> *, const Sommet<T> *) const;
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

template <class S, class T>
Arete<S,T>::Arete(const int & c, Sommet<T> * d, Sommet<T> * f, const S & val)
                : GElement(c), debut(d), fin(f), v(val) {}

template <class S, class T>
Arete<S,T>::operator std::string() const
{
    // l'hypothèse est faite que la classe S est munie de l'opérateur << d'écriture sur un flux
    // il est suffisant, pour la conversion en string d'une arête,
    // d'indiquer les clefs primaires des sommets debut et fin
    std::ostringstream stream;
    stream << "(" << GElement::operator std::string()
            << " ; debut = " << debut->clef
            << " ; fin = " << fin->clef
            << " ; v = " << v << ")";
    return stream.str();
}

template <class S, class T>
bool Arete<S,T>::estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const
{
    return (debut == s1 && fin == s2) || (debut == s2 && fin == s1);
}

template <class S, class T>
std::ostream & operator<< (std::ostream & os, const Arete<S,T> & op)
{
    return os << std::string(op);
}


#endif
