#ifndef __GELEMENT
#define __GELEMENT

#include <string>

/**
 * Représente la classe de base des éléments d'un graphe qui peuvent être des sommets ou des arêtes.
 *
 * A ce niveau, on ne peut que définir que la clef d'un élément.
 *
 * En effet tout élément d'un graphe est défini par une clef (c-à-d une valeur non nulle et unique)
 **/
class GElement
{
public:
    int clef;   // sert de clef primaire

    GElement(const int &);

    operator std::string() const;

};

extern std::ostream & operator<< (std::ostream & os, const GElement & op);

#endif
