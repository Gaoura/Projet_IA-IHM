#include <random>
#include <cmath>

#include "SolutionCout.h"

/* retourne un nombre aleatoire dans [0,1) */
double tirageAleatoire()
{
    /* http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution */
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distr(0., 1.); // define the range
    // Use distr to transform the random unsigned int generated by gen into an int in [0., 1)
    return distr(gen);
}

template <class S>
const SolutionCout<S> recuitSimule(const double & tInitiale, const double & tFinale,
	const int & nombreTentativesMax, const int & nombreSuccesMax,
	const S & s0, double(*cout1)(const S & s), const S(*changementAleatoire)(const S & s),
	double(*succ)(const double & t))
{
	double t = tInitiale;
	SolutionCout<S> s(s0, cout1);
	SolutionCout<S> sBest(s);
	double v;
	double deltaCout;

	while (t > tFinale)
	{
		int nombreTentatives = 0;
		int nombreSucces = 0;

		while (nombreTentatives < nombreTentativesMax && nombreSucces < nombreSuccesMax)
		{
			nombreTentatives++;
			SolutionCout<S> sPrecedente(s);
			s = s.change(changementAleatoire, cout1);

			if (s.cout_ < sPrecedente.cout_)
			{
				nombreSucces++;
				if (s.cout_ < sBest.cout_)
					sBest = s;
			}
			else
			{
				v = tirageAleatoire();
				deltaCout = s.cout_ - sPrecedente.cout_;

				if (v < exp(-(deltaCout / t)))
					nombreSucces++;
				else
					s = sPrecedente;
			}
		}

		if (nombreSucces == 0)
			return sBest;
		t = succ(t);
	}

	return sBest;
}