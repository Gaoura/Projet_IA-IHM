#ifndef __ERREUR
#define __ERREUR

#include <string>

class Erreur
{
    std::string msg;
public:
    Erreur(const std::string & s) : msg(s) {}
    const std::string & getMsg()
    {
        return msg;
    }
};

#endif
