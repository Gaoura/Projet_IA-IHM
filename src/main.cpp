#include <fstream>
#include <iostream>
#include <string>

#include "Graphe.h"
#include "DessinGrapheRecuitSimule.h"
#include "OutilsCarteRecuitSimule.h"
#include "CircuitGraphe.h"
#include "recuitSimule.h"

#define S1 6                // nombre de sommets du graphe g1
#define S2 8                // nombre de sommets du graphe g2
#define A1 (S1*(S1-1)/2)    // nombre d'arêtes du graphe g1 car g1 est complet
#define A2 17               // nombre d'arêtes du graphe g2


// Fonction tres simple pour la diminution de la temperature
double succ(const double & x)
{
	return x - 1;
}

int main()
{
/*
/////////////////////////////////////////////////////////////////////////////////////////////

             ######   ########     ###    ########  ##     ## ########       ##
            ##    ##  ##     ##   ## ##   ##     ## ##     ## ##           ####
            ##        ##     ##  ##   ##  ##     ## ##     ## ##             ##
            ##   #### ########  ##     ## ########  ######### ######         ##
            ##    ##  ##   ##   ######### ##        ##     ## ##             ##
            ##    ##  ##    ##  ##     ## ##        ##     ## ##             ##
             ######   ##     ## ##     ## ##        ##     ## ########     ######

/////////////////////////////////////////////////////////////////////////////////////////////
*/
    char ch;
     //--------------- 1er exemple de graphe ------------------------------

    std::cout << "construction d'un 1er exemple de graphe complet à 6 sommets" << std::endl;

    Graphe<InfoAreteCarte,InfoSommetCarte> g1;	// création du graphe g1 vide


    //----------------------- on crée les sommets dans g1 -------------------------------------

    Sommet<InfoSommetCarte> * s[S1];
    s[0] = g1.creeSommet(InfoSommetCarte("s0",Vecteur2D(1,2)));
    s[1] = g1.creeSommet(InfoSommetCarte("s1",Vecteur2D(3,1)));
    s[2] = g1.creeSommet(InfoSommetCarte("s2",Vecteur2D(5,2)));
    s[3] = g1.creeSommet(InfoSommetCarte("s3",Vecteur2D(5,3)));
    s[4] = g1.creeSommet(InfoSommetCarte("s4",Vecteur2D(3,4)));
    s[5] = g1.creeSommet(InfoSommetCarte("s5",Vecteur2D(1,3)));		// cette répétition de 6 instructions pourrait être avantageusement remplacée par une boucle
    																// elle a été uniquement été laissée pour améliorer la lisibilité



    //----------------------- on crée les arêtes dans g1 --------------------------------------

    int i,j;	// indices des sommets

    for (i = 0; i < S1; ++i)
    	for (j = i+1; j < S1; ++j)
    	{
    		double d = OutilsCarteRecuitSimule::distance(s[i],s[j]);  // calcul de la distance du sommet s[i] à s[j]
    		g1.creeArete( s[i], s[j], InfoAreteCarte(d));
    	}
    //--------------- ca y est, g1 est créé et complet ----------------------------------
    // ----------------- on affiche sur la console toutes les informations contenues dans g1

    std::cout << "g1 = "<< std::endl << g1 << std::endl;

    std::cout <<"tapez un caractère, puis ENTER\n"; std::cin >> ch;

    //----------------- on crée le fichier texte pour dessiner g1 ------------------------------

    string nomFichierDessin = "grapheHexagonalComplet.txt";
    std::ofstream f(nomFichierDessin);      // ouverture de f en écriture, en mode texte
                                            // (cf. doc cplusplus.com)
    Vecteur2D coinBG(-1,-1), coinHD(5,5);   // limites de la fenêtre à visualiser.
                                            // calculées à partir des coordonnées des sommets
    string couleurRepere = "blue";
    int rayonSommet = 5;                    // unité :  pixel
    string couleurSommets = "red";
    string couleurAretes = "blue";

    DessinGrapheRecuitSimule::ecritGraphe(f, g1, coinBG, coinHD, couleurRepere,
                                            rayonSommet, couleurSommets, couleurAretes);

    std::cout << "le fichier texte de  dessin " << nomFichierDessin << " a été créé" << std::endl;

    //--------------- fin 1er exemple de graphe ------------------------------


/*
/////////////////////////////////////////////////////////////////////////////////////////////

             ######   #######  ##       ##     ## ######## ####  #######  ##    ##
            ##    ## ##     ## ##       ##     ##    ##     ##  ##     ## ###   ##
            ##       ##     ## ##       ##     ##    ##     ##  ##     ## ####  ##
             ######  ##     ## ##       ##     ##    ##     ##  ##     ## ## ## ##
                  ## ##     ## ##       ##     ##    ##     ##  ##     ## ##  ####
            ##    ## ##     ## ##       ##     ##    ##     ##  ##     ## ##   ###
             ######   #######  ########  #######     ##    ####  #######  ##    ##

/////////////////////////////////////////////////////////////////////////////////////////////
*/

    std::cout <<"tapez un caractère, puis ENTER pour passer a la creation d'un chemin\n";std::cin >> ch;

    // on cree un CircuitGraphe qui va contenir le chemin sur lequel va travailler le recuit simule
    CircuitGraphe s0 = CircuitGraphe(&g1);

    // comme le graphe est complet on va juste ajouter les sommets dans l'ordre
    // et les melanger une fois
    for (int i{0}; i < S1; i++)
        s0.add(s[i]);

    std::cout << "Circuit initial :" << std::endl << s0 << std::endl << std::endl;

    double tInitiale = 100.;
    double tFinale = 0.;
    int nombreTentativesMax = 100;
    int nombreSuccesMax = 50;

    s0 = s0.changementAleatoire();

    std::cout << "Circuit changé avant recuit simule :" << std::endl << s0 << std::endl << std::endl;

    SolutionCout<CircuitGraphe> solution_recuit = recuitSimule(tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax, s0, coutParcours, changementAleatoire, succ);
    std::cout << "Meilleure solution et son coût : " << std::endl << solution_recuit << std::endl;

    std::cin >> ch;




    // on cree un graphe a partir du circuit solution
    Graphe<InfoAreteCarte,InfoSommetCarte> * g_solution;
    g_solution = solution_recuit.solution.convertirEnGraphe();

    // on crée le fichier texte pour dessiner le circuit solution ---------------------------

    nomFichierDessin = "grapheHexagonalCircuitSolution.txt";
    std::ofstream f2(nomFichierDessin);     // ouverture de f en écriture, en mode texte
                                            // (cf. doc cplusplus.com)

    DessinGrapheRecuitSimule::ecritGraphe(f2, *g_solution, coinBG, coinHD, couleurRepere,
                                            rayonSommet, couleurSommets, couleurAretes);

    std::cout << "le fichier texte de  dessin " << nomFichierDessin << " a été créé" << std::endl;

    delete g_solution;


    std::cout <<"tapez un caractère, puis ENTER\n"; std::cin >> ch;
/*
/////////////////////////////////////////////////////////////////////////////////////////////

             ######   ########     ###    ########  ##     ## ########     #######
            ##    ##  ##     ##   ## ##   ##     ## ##     ## ##          ##     ##
            ##        ##     ##  ##   ##  ##     ## ##     ## ##                 ##
            ##   #### ########  ##     ## ########  ######### ######       #######
            ##    ##  ##   ##   ######### ##        ##     ## ##          ##
            ##    ##  ##    ##  ##     ## ##        ##     ## ##          ##
             ######   ##     ## ##     ## ##        ##     ## ########    #########

/////////////////////////////////////////////////////////////////////////////////////////////
*/

    std::cout << "construction d'un 2ème exemple de graphe complet à 8 sommets" << std::endl;

    Graphe<InfoAreteCarte,InfoSommetCarte> g2;	// création du graphe g2 vide


    //----------------------- on crée les sommets dans g2 -------------------------------------

    Sommet<InfoSommetCarte> * s2[S2];
    s2[0] = g2.creeSommet(InfoSommetCarte("s0",Vecteur2D(1.5,2)));
    s2[1] = g2.creeSommet(InfoSommetCarte("s1",Vecteur2D(1,3)));
    s2[2] = g2.creeSommet(InfoSommetCarte("s2",Vecteur2D(1.5,4)));
    s2[3] = g2.creeSommet(InfoSommetCarte("s3",Vecteur2D(3,5)));
    s2[4] = g2.creeSommet(InfoSommetCarte("s4",Vecteur2D(4.5,4)));
    s2[5] = g2.creeSommet(InfoSommetCarte("s5",Vecteur2D(5,3)));
    s2[6] = g2.creeSommet(InfoSommetCarte("s6",Vecteur2D(4.5,2)));
    s2[7] = g2.creeSommet(InfoSommetCarte("s7",Vecteur2D(3,1)));

    //----------------------- on crée les arêtes dans g2 --------------------------------------

    OutilsCarteRecuitSimule::creeArete(s2[0], s2[1], g2);
    OutilsCarteRecuitSimule::creeArete(s2[0], s2[3], g2);
    OutilsCarteRecuitSimule::creeArete(s2[0], s2[7], g2);
    OutilsCarteRecuitSimule::creeArete(s2[1], s2[2], g2);
    OutilsCarteRecuitSimule::creeArete(s2[1], s2[4], g2);
    OutilsCarteRecuitSimule::creeArete(s2[1], s2[7], g2);
    OutilsCarteRecuitSimule::creeArete(s2[2], s2[3], g2);
    OutilsCarteRecuitSimule::creeArete(s2[2], s2[4], g2);
    OutilsCarteRecuitSimule::creeArete(s2[2], s2[6], g2);
    OutilsCarteRecuitSimule::creeArete(s2[3], s2[4], g2);
    OutilsCarteRecuitSimule::creeArete(s2[3], s2[5], g2);
    OutilsCarteRecuitSimule::creeArete(s2[3], s2[7], g2);
    OutilsCarteRecuitSimule::creeArete(s2[4], s2[5], g2);
    OutilsCarteRecuitSimule::creeArete(s2[4], s2[7], g2);
    OutilsCarteRecuitSimule::creeArete(s2[5], s2[6], g2);
    OutilsCarteRecuitSimule::creeArete(s2[5], s2[7], g2);
    OutilsCarteRecuitSimule::creeArete(s2[6], s2[7], g2);

    //--------------- ca y est, g2 est créé et complet ----------------------------------

    //----------------- on crée le fichier texte pour dessiner g2 ---------------------------

    nomFichierDessin = "grapheOctogonal.txt";
    std::ofstream f3(nomFichierDessin);      // ouverture de f en écriture, en mode texte
                                            // (cf. doc cplusplus.com)
    DessinGrapheRecuitSimule::ecritGraphe(f3, g2, coinBG, coinHD, couleurRepere,
                                            rayonSommet, couleurSommets, couleurAretes);

    std::cout << "le fichier texte de  dessin " << nomFichierDessin << " a été créé" << std::endl;

    //--------------- fin 2ème exemple de graphe ------------------------------


/*
/////////////////////////////////////////////////////////////////////////////////////////////

             ######   #######  ##       ##     ## ######## ####  #######  ##    ##
            ##    ## ##     ## ##       ##     ##    ##     ##  ##     ## ###   ##
            ##       ##     ## ##       ##     ##    ##     ##  ##     ## ####  ##
             ######  ##     ## ##       ##     ##    ##     ##  ##     ## ## ## ##
                  ## ##     ## ##       ##     ##    ##     ##  ##     ## ##  ####
            ##    ## ##     ## ##       ##     ##    ##     ##  ##     ## ##   ###
             ######   #######  ########  #######     ##    ####  #######  ##    ##

/////////////////////////////////////////////////////////////////////////////////////////////
*/

    std::cout <<"tapez un caractère, puis ENTER pour passer à la création d'un chemin\n";std::cin >> ch;

    // on cree un CircuitGraphe qui va contenir le chemin sur lequel va travailler le recuit simule
    CircuitGraphe sInitiale2 = CircuitGraphe(&g2);

    // on cree un circuit avec une arete inexistante
    // NOTE: s'il y a plusieurs aretes inexistantes, le fait que la solution initiale soit
    // toujours conservee tant qu'on ne trouve pas strictement moins, et qu'une arete inexistante
    // donne un cout de valeur infini, alors
    // on compare 2 circuits de cout infini continuellement 
    sInitiale2.add(s2[0]);
    sInitiale2.add(s2[1]);
    sInitiale2.add(s2[2]);
    sInitiale2.add(s2[3]);
    sInitiale2.add(s2[4]);
    sInitiale2.add(s2[6]);
    sInitiale2.add(s2[5]);
    sInitiale2.add(s2[7]);

    std::cout << "Circuit initial :" << std::endl
                << sInitiale2 << "  " << sInitiale2.coutParcours() << std::endl << std::endl;

    tInitiale = 100.;
    tFinale = 0.;
    nombreTentativesMax = 10;
    nombreSuccesMax = 5;

    SolutionCout<CircuitGraphe> solution_recuit2 = recuitSimule(tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax, sInitiale2, coutParcours, changementAleatoire, succ);
    std::cout << "Meilleure solution et son coût : " << std::endl << solution_recuit2 << std::endl;

    std::cout << "tapez un caractère, puis ENTER" << std::endl; std::cin >> ch;


    Graphe<InfoAreteCarte,InfoSommetCarte> * g_solution2 = solution_recuit2.solution.convertirEnGraphe();

    // on crée le fichier texte pour dessiner le circuit solution ---------------------------

    nomFichierDessin = "grapheOctogonalCircuitSolution.txt";
    std::ofstream f4(nomFichierDessin);     // ouverture de f en écriture, en mode texte
                                            // (cf. doc cplusplus.com)

    DessinGrapheRecuitSimule::ecritGraphe(f4, *g_solution2, coinBG, coinHD, couleurRepere,
                                            rayonSommet, couleurSommets, couleurAretes);

    std::cout << "le fichier texte de  dessin " << nomFichierDessin << " a été créé" << std::endl;

    delete g_solution;

    return 0;
}
