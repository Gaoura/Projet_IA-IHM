#ifndef __GRAPHE
#define __GRAPHE

#include <utility>

#include "PElement.h"
#include "Sommet.h"
#include "Arete.h"

template <class S, class T>
class Graphe
{
private:
    int prochaineClef;              // définit la clef primaire du prochain élément (sommet
                                    // ou arête) qui sera inséré dans le graphe,
                                    // est incrémenté à chaque insertion d'un élément

public:
    PElement<Sommet<T> > * lSommets; // contient la liste des sommets
    PElement<Arete<S,T> > * lAretes; // contient la liste des arêtes

    /**
     * crée un graphe vide
     **/
    Graphe();

    /**
     * destructeur obligatoire car la classe comporte une partie dynamique
     **/
    ~Graphe();

    /**
     * crée un sommet isolé
     **/
    Sommet<T> * creeSommet(const T & info);

    /**
     * crée une arête joignant les 2 sommets debut et fin
     * on suppose que debut et fin sont déjà contenus dans le graphe,
     * met à jour les champs degré de debut et de fin
     **/
    Arete<S,T> * creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info);

    int nombreSommets() const;

    int nombreAretes() const;

    operator std::string() const;

    /**
     * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
     *
     * DONNEES : s1 et s2 deux sommets quelconques du graphe
     * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
     **/
    Arete<S,T> * getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;

    /**
     * recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
     **/
    PElement<std::pair<Sommet<T> *, Arete<S,T> * > > * adjacences(const Sommet<T> * sommet) const;
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
Graphe<S,T>::Graphe()
                : prochaineClef(0), lSommets(nullptr), lAretes(nullptr) {}

template <class S, class T>
Graphe<S,T>::~Graphe()
{
    PElement<Arete<S,T>>::efface2(this->lAretes);
    PElement<Sommet<T>>::efface2(this->lSommets);
}

template <class S, class T>
Sommet<T> * Graphe<S,T>::creeSommet(const T & info)
{
    Sommet<T> * s = new Sommet<T>(prochaineClef++, info);
    lSommets = new PElement<Sommet<T>>(s, lSommets);
    return s;
}

template <class S, class T>
Arete<S,T> * Graphe<S,T>::creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info)
{
    Arete<S,T> * a = new Arete<S,T>(prochaineClef++, debut, fin, info);
    lAretes = new PElement<Arete<S,T>>(a, lAretes);
    (debut->degre)++;
    (fin->degre)++;

    return a;
}

template <class S, class T>
int Graphe<S,T>::nombreSommets() const
{
    return PElement<Sommet<T>>::taille(lSommets);
}

template <class S, class T>
int Graphe<S,T>::nombreAretes() const
{
    return PElement<Arete<S,T>>::taille(lAretes);
}

template <class S, class T>
Graphe<S,T>::operator std::string() const
{
    std::ostringstream stream;
    stream << "( prochaineClef = " << prochaineClef
            << " ; nombre de sommets = " << nombreSommets()
            << " ; lSommets = " << PElement<Sommet<T>>::toString(lSommets)
            << " ; nombre d'arêtes = " << nombreAretes()
            << " ; lAretes = " << PElement<Arete<S,T>>::toString(lAretes) << ")";
    return stream.str();
}

template <class S, class T>
Arete<S,T> * Graphe<S,T>::getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const
{
    if (s1 == nullptr || s2 == nullptr)
        return nullptr;

    PElement<Arete<S,T>> * l = lAretes;

    while (l != nullptr)
    {
        if (l->v->estEgal(s1, s2))
            return l->v;

        l = l->s;
    }

    return nullptr;
}

template <class S, class T>
PElement<std::pair<Sommet<T> *, Arete<S,T> * >> * Graphe<S,T>::adjacences(const Sommet<T> * sommet) const
{
    if (sommet == nullptr || lAretes == nullptr)
        return nullptr;

    PElement<Arete<S,T>> * temp = lAretes;
    PElement<std::pair<Sommet<T> *, Arete<S,T> * >> * liste = nullptr;

    while (temp != nullptr)
    {
        // si le sommet debut de l'arête courante est le sommet passé en paramètre
        // on crée une pair contenant le sommet fin et l'arête
        if (temp->v->debut == sommet)
            liste = new PElement<std::pair<Sommet<T>*, Arete<S,T>*>>(
                        new std::pair<Sommet<T>*, Arete<S,T>*>(
                            temp->v->fin,
                            temp->v),
                        liste);
        // si le sommet fin de l'arête courante est le sommet passé en paramètre
        // on crée une pair contenant le sommet debut et l'arête
        else
            if (temp->v->fin == sommet)
                liste = new PElement<std::pair<Sommet<T>*, Arete<S,T>*>>(
                            new std::pair<Sommet<T>*, Arete<S,T>*>(
                                temp->v->debut,
                                temp->v),
                            liste);
        // puis on passe à l'arête suivante
        temp = temp->s;
    }

    return liste;
}

template <class S, class T>
std::ostream & operator<< (std::ostream & os, const Graphe<S,T> & op)
{
    return os << std::string(op);
}



#endif
