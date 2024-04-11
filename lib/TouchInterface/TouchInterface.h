/*       Fichier .h de la librairie TouchInterface          */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#ifndef TOUCH_STATE_LIBRARY_H
#define TOUCH_STATE_LIBRARY_H

#include <mbed.h>

enum EtatLib
{
    caseDemarrage,
    caseAttente,
    caseDetectionAppui,
    caseBatterie,
    caseMenu,
    caseModes,
    caseLibre,
    caseDemo,
    caseDebogage,
    caseEnregistrer,
    caseSelection,
    caseEnvoiPosition,
    caseEnregistrement,
    caseFinEnregistrement,
    caseRejouer,
    LedOn,
    LedOff
};

class TouchInterface
{
public:
    static EtatLib detectBouton(int positionX, int positionY, bool flagMenu, bool flagModes, uint8_t flagEnregistremnent);
};

#endif