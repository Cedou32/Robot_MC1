/*       Fichier .h de la librairie TouchInterface          */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#ifndef TOUCH_STATE_LIBRARY_H
#define TOUCH_STATE_LIBRARY_H

#include <mbed.h>
#include <string>

enum EtatLib
{
    Demarrage,
    Attente,
    Batterie,
    Menu,
    Modes,
    Libre,
    Demo,
    Debogage,
    Enregistrer,
    TransmissionTrame,
};

struct StateInfo { // Déclaration de la structure
    EtatLib etat;
    std::string nom;
    uint8_t mode;
    bool status;
};

class TouchInterface
{
public:
    static StateInfo detectBouton(int positionX, int positionY, bool flagMenu, bool flagModes, uint8_t modeActuel, uint8_t enregistrementActuel);
};

#endif
