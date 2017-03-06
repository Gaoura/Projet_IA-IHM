#ifndef __CYCLEGRAPHE
#define __CYCLEGRAPHE

#include <limits>
#include <random>
#include <iostream>
#include <sstream>

#include "PElement.h"
#include "OutilsCarteRecuitSimule.h"

/**
 * Classe representatnt un circuit elementaire dans un graphe
 */
class CircuitGraphe
{
private:
    // graphe dans lequel on cherchera les aretes
    Graphe<InfoAreteCarte, InfoSommetCarte> * graphe_;
    // liste des sommets du circuit
    PElement<Sommet<InfoSommetCarte> > * circuit_;

    /**
     *  Utilise un generateur de nombre aleatoire pour choisir un sommet de la liste
     */
    Sommet<InfoSommetCarte> * sommetAleatoire() const;

    /**
     * Renvoie le sommet de la liste suivant le somemt passe en parametre
     * ou un nullptr en cas de probleme, ce qui ne devrait jamais arriver
     */
    Sommet<InfoSommetCarte> * sommetSuivant(const Sommet<InfoSommetCarte> * s) const;

    /**
     * Utilise par changementAleatoire donc se referer a l'algo de changementAleatoire
     * pour connaitre l'utilite de la methode statique suivante
     * Utilise deux sommets pour construire la liste de sommets du CircuitGraphe
     * passe en parametre a partir d'un tableau de sommets
     */
    static void nouvListeCircuitGraphe(Sommet<InfoSommetCarte> * s_preums,
                                        Sommet<InfoSommetCarte> * s_deuz,
                                        CircuitGraphe & cg,
                                        Sommet<InfoSommetCarte> * tab_sommets[],
                                        const int size);

public:

    /**
     * Constructeur a partir d'un graphe
     * Le graphe doit etre non vide et posseder 4 sommets ou plus
     * pour eviter tout probleme dans changementAleatoire,
     * sinon une exception est levee
     */
    CircuitGraphe(Graphe<InfoAreteCarte, InfoSommetCarte> *);

    CircuitGraphe(const CircuitGraphe & c);

    const CircuitGraphe & operator= (const CircuitGraphe & c);

    /**
     * Destructeur obligatoire car la classe comporte une partie dynamique
     **/
    ~CircuitGraphe();

    Graphe<InfoAreteCarte, InfoSommetCarte> * getGraphe() const
    {
        return graphe_;
    }

    PElement<Sommet<InfoSommetCarte> > * getCircuit() const
    {
        return circuit_;
    }

    /**
     * Ajoute un sommet en fin de liste de sommets
     * Leve une exception si le sommet est NULL ou s'il n'est pas dans le graphe
     * ou s'il est deja dans la liste (circuit elementaire)
     */
    void add(Sommet<InfoSommetCarte> *);

    /**
     * Retire le sommet de la liste de sommets (sans supprimer le sommet lui-même)
     * Leve une exception si le sommet est NULL ou s'il n'est pas dans la liste de sommets
     */
    void remove(Sommet<InfoSommetCarte> *);

    operator std::string() const;

    /**
     *  Renvoie un chemin ou l'on a fait effectuee la procedure suggeree par le sujet :
     *  1. On choisit deux sommets non consecutifs A et B au hasard dans ce circuit.
     *     Notons C et D  les sommets respectivement suivants de A et de B.
     *  2. On remplace l'arete A->C par l'arete A->B.
     *  3. On change le sens du chemin C->B.
     *  4. On remplace l'arete B->D par l'arete C->D.
     */
    CircuitGraphe changementAleatoire() const;

    /**
     * Renvoie le cout d'un tour complet de circuit
     */
    double coutParcours() const;

};

std::ostream & operator<< (std::ostream & os, const CircuitGraphe & op);

const CircuitGraphe changementAleatoire(const CircuitGraphe & c);

double coutParcours(const CircuitGraphe & c);

#endif
