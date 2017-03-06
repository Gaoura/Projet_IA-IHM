#include "PElement.h"
#include <string>
#include <iostream>

bool estPlusPetitOuEgal(const double * a1, const double * a2)
{
    return *a1 <= *a2;
}

bool estPlusPetitOuEgal2(const std::string * a1, const std::string * a2)
{
    return a1->compare(*a2) <= 0;
}

int main()
{
	PElement<double> * l1{ nullptr };
	PElement<std::string> * l2{ nullptr };

	double p{ 9. };
	double p2 = 7.5;
	double p3 = 5.;
	double p4 = 2.;
	l1 = new PElement<double>(&p, l1);
	l1 = new PElement<double>(&p2, l1);
	l1 = new PElement<double>(&p3, l1);
	l1 = new PElement<double>(&p4, l1);

	std::string s{ "orange" };
	std::string s2 = "cerise";
    std::string s3 = "carotte";
	l2 = new PElement<std::string>(&s, l2);
	l2 = new PElement<std::string>(&s2, l2);
	l2 = new PElement<std::string>(&s3, l2);

    // ---------- AFFICHAGE ----------
	std::cout << PElement<double>::toString(l1) << std::endl;
	std::cout << PElement<std::string>::toString(l2) << std::endl;

    double a = -7.;
    double b = 6.;
    double c = 13.;
    PElement<double>::insertionOrdonnee(&a, l1, estPlusPetitOuEgal);
    PElement<double>::insertionOrdonnee(&b, l1, estPlusPetitOuEgal);
    PElement<double>::insertionOrdonnee(&c, l1, estPlusPetitOuEgal);

    std::string s4 = "fraise";
    std::string s5 = "ananas";
    std::string s6 = "pomme";

    PElement<std::string>::insertionOrdonnee(&s4, l2, estPlusPetitOuEgal2);
    PElement<std::string>::insertionOrdonnee(&s5, l2, estPlusPetitOuEgal2);
    PElement<std::string>::insertionOrdonnee(&s6, l2, estPlusPetitOuEgal2);

    // ---------- AFFICHAGE ----------
    std::cout << PElement<double>::toString(l1) << std::endl;
	std::cout << PElement<std::string>::toString(l2) << std::endl;

    std::cout << "Valeur dépilée : " << std::to_string(*PElement<double>::depiler(l1)) << std::endl;
    std::cout << "Valeur dépilée : " << *(PElement<std::string>::depiler(l2)) << std::endl;

    // ---------- AFFICHAGE ----------
    std::cout << PElement<double>::toString(l1) << std::endl;
	std::cout << PElement<std::string>::toString(l2) << std::endl;

    // renvoie true
    std::cout << PElement<double>::retire(&b, l1) << std::endl;
    std::cout << PElement<double>::retire(&c, l1) << std::endl;
	std::cout << PElement<std::string>::retire(&s, l2) << std::endl;

    double truc = 24.;
    // ne peut rien retirer, renvoie false
    std::cout << PElement<double>::retire(&truc, l1) << std::endl;

    // ---------- AFFICHAGE ----------
    std::cout << PElement<double>::toString(l1) << std::endl;
	std::cout << PElement<std::string>::toString(l2) << std::endl;

    PElement<double>::efface1(l1);
    PElement<std::string>::efface1(l2);

    double * aea = new double (2.);
	l1 = new PElement<double>(aea, l1);

    PElement<double>::efface2(l1);

	getchar();
}
