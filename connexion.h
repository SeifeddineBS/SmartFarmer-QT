#ifndef CONNEXION_H
#define CONNEXION_H
#include <qsqldatabase.h>

class Connexion
{
public:
    Connexion();
    bool connecter();
};

#endif // CONNEXION_H
