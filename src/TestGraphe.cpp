#include <string>
#include <iostream>

#include "GElement.h"
#include "Sommet.h"
#include "Arete.h"
#include "Graphe.h"

int main()
{
    // Test GElement
    GElement g = GElement(7);
    std::string s = std::string(g);

    std::cout << g << std::endl;
    std::cout << s << std::endl;

    // Test Sommet
    double a = 5.;
    std::string s2 = "OUI.";
    Sommet<double> p = Sommet<double>(10, a);
    Sommet<std::string> p2 = Sommet<std::string>(11, s2);

    std::cout << p << std::endl;
    std::cout << p2 << std::endl;

    // Test Arete
    std::string s3 = "CHOUCROUTE";
    char c1 = 'a';
    char c2 = 'b';
    Sommet<char> som1 = Sommet<char>(12, c1);
    Sommet<char> som2 = Sommet<char>(13, c2);
    Arete<std::string, char> arete = Arete<std::string, char>(14, &som1, &som2, s3);

    std::cout << arete << std::endl;

    // Test estEgal
    char c3 = 'c';
    Sommet<char> som3 = Sommet<char>(12, c3);

    std::cout << arete.estEgal(&som1, &som2) << std::endl;  // renvoie true
    std::cout << arete.estEgal(&som2, &som1) << std::endl;  // renvoie true
    std::cout << arete.estEgal(&som1, &som3) << std::endl;  // renvoie false

    // Test Graphe
    Graphe<std::string, char> graphe = Graphe<std::string, char>();

    Sommet<char> * som[5];
    som[0] = graphe.creeSommet('a');
    som[1] = graphe.creeSommet('b');
    som[2] = graphe.creeSommet('c');
    som[3] = graphe.creeSommet('d');
    som[4] = graphe.creeSommet('e');

    graphe.creeArete(som[0],som[1],"myrtille");
    graphe.creeArete(som[1],som[2],"champignon");

    std::cout << "g = " << graphe << std::endl;


    char ch ; std::cin >> ch;

}
