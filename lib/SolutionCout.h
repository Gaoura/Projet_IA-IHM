#include <iostream>
#include <sstream>

/**
pour optimiser le temps de calcul, il vaut mieux économiser les appels à la fct cout(). Aussi il vaut mieux stocker les coûts calculés.

Le plus simple est d'alors associer une solution particulière et son coût. C'est le but de cette classe

*/
template <class S>
class SolutionCout
{
public:
    S solution;
    double cout_; // cout de solution

    SolutionCout( const S & solution, double (*cout1)( const S & solution))
                : solution(solution), cout_(cout1(solution)) {}

    const SolutionCout<S> change( const S (*changementAleatoire) (const S & solution), double (*cout1) (const S & solution)) const;

    operator std::string() const;
};

template <class S>
std::ostream & operator << (std::ostream & os, const SolutionCout<S> & solutionCout)
{
    return os << (std::string)solutionCout;
}

template <class S>
const SolutionCout<S> SolutionCout<S>::change( const S (*changementAleatoire) (const S & solution), double (*cout1) (const S & solution)) const
{
    return SolutionCout<S>(changementAleatoire(this->solution), cout1);
}

template <class S>
SolutionCout<S>::operator std::string() const
{
    std::ostringstream oss;

    oss << "( " << solution <<", " << cout_ << ")";
    return oss.str();
}
