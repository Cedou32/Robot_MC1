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
    demarrage,
    attente,
    detectionAppui,
    menu,
    vitesse,
    modes,
    libre,
    enregistrer,
    etendu,
    debogage,
    selectVitesse1,
    selectVitesse2,
    selectVitesse3,
    ok,
    fermer,
    mvtRobot,
    battery
};

class TouchInterface
{
public:
    static EtatLib detectBouton(int positionX, int positionY, bool flagMenu, bool flagVitesse, bool flagModes);
};

#endif