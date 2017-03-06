#ifndef __PELEMENT
#define __PELEMENT

#include <string>
#include <sstream>

#include "Erreur.h"

template <class T>
class PElement
{
public:
	T * v;
	PElement<T> * s;

    /**
     * Ne crée pas de copie de *v.
     * Pointe donc sur la donnée originale *v
     **/
	PElement(T * val, PElement<T> * suiv);

	static int taille(const PElement<T> * l);

    static const std::string toString(const PElement<T> * p,
    	const char * debut = "( ",
    	const char * separateur = ", ",
    	const char * fin = ")");

    /**
     * Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
     * Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
     *
     * Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
     * Résultats : l modifiée par l'insertion
     * Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
     **/
    static void insertionOrdonnee(T * a, PElement<T> * & l,
                                    bool (*estPlusPetitOuEgal) (const T * a1, const T * a2));

    /**
     * retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
     *
     * l est donc modifiée par l'appel. En sortie l compte un élément de moins.
     * lance une exception Erreur si l == NULL à l'appel
     **/
    static T * depiler(PElement<T> * & l);

    /**
     * retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
     *
     * L'élément trouvé n'est pas effacé
     *
     * La comparaison est faite sur les pointeurs
     *
     * Données : a, l
     * Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
     **/
    static bool retire(const T * a, PElement<T> * & l);

    /**
     * efface toute la liste l
     * mais n'efface pas les données *v
     **/
    static void efface1(PElement<T> * & l);

    /**
     * efface toute la liste l
     * et efface toutes les données *v
     **/
    static void efface2(PElement<T> * & l);
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
PElement<T>::PElement(T * val, PElement<T> * suiv)
                    : v(val), s(suiv) {}

template <class T>
/*static*/ int PElement<T>::taille(const PElement<T> * l)
{
	if (l == nullptr)
		return 0;
	else
		return taille(l->s) + 1;
}

template <class T>
/*static*/ const std::string PElement<T>::toString(const PElement<T> * p,
                                                    const char * debut,
                                                    const char * separateur,
                                                    const char * fin)
{
	std::ostringstream os;
	os << debut;
	const PElement<T> * temp = p;
	while (temp != nullptr)
	{
		os << *(temp->v);
		if (temp->s != nullptr)
        {
            temp = temp->s;
            os << separateur;
        }
        else
            break;
	}
	os << fin;

	return os.str();
}

template <class T>
/*static*/ void PElement<T>::insertionOrdonnee(T * a, PElement<T> * & l,
                                bool (*estPlusPetitOuEgal) (const T * a1, const T * a2))
{
    if (l == nullptr)
        l = new PElement<T>(a, l);
    else
    {
        if (estPlusPetitOuEgal(l->v, a))
            insertionOrdonnee(a, l->s, estPlusPetitOuEgal);
        else
        {
            // on crée une copie de l'élément courant (pointe donc vers le même suivant)
            PElement<T> * t = new PElement<T>(l->v, l->s);
            // on fait pointer l'original vers la copie
            l->s = t;
            // on change la valeur de l'original par l'élément à insérer
            l->v = a;
        }
    }
}

template <class T>
/*static*/  T * PElement<T>::depiler(PElement<T> * & l)
{
    if (l == nullptr)
        throw Erreur("Impossible de dépiler une liste vide");

    // on copie la valeur de la tête
    T * v = l->v;
    // on copie l'adresse de la tête
    PElement<T> * t = l;
    // on change l'adresse de la tête par l'adresse de l'élément suivant
    l = l->s;
    // on supprime l'élément dépilé
    delete t;
    // on renvoie la valeur de l'élément dépilée
    return v;
}

template <class T>
/*static*/ bool PElement<T>::retire(const T * a, PElement<T> * & l)
{
    if (l == nullptr)
        return false;

    if (l->v == a)
    {
        if (l->s != nullptr)
        {
            // on copie l'adresse de l'élément suivant
            PElement<T> * t = l->s;
            // on copie le contenu de l'élément suivant dans l'élément courant
            l->v = t->v;
            l->s = t->s;
            // on supprime l'élément suivant
            delete t;
        }
        else
        {
            delete l;
            l = nullptr;
        }

        return true;
    }

    return retire(a, l->s);
}

template <class T>
/*static*/ void PElement<T>::efface1(PElement<T> * & l)
{
    if (l != nullptr)
    {
        efface1(l->s);
        delete l;
        l = nullptr;
    }
}

template <class T>
/*static*/ void PElement<T>::efface2(PElement<T> * & l)
{
    if (l != nullptr)
    {
        efface2(l->s);
        // il faut veiller à ce que la structure T en v ait été alloué dynamiquement
        delete l->v;
        delete l;
        l = nullptr;
    }
}

template <class T>
std::ostream & operator<< (std::ostream & os, const PElement<T> * p)
{
    return os << PElement<T>::toString(p);
}

#endif
