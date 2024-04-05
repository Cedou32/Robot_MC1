/*      Fichier .cpp de la librairie TouchInterface         */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#include "TouchInterface.h"

EtatLib TouchInterface::detectBouton(int positionX, int positionY, bool flagMenu, bool flagVitesse, bool flagModes)
{
    if (positionX >= 210 && positionX <= 310 && positionY >= 10 && positionY <= 40)
    {
        return menu;
    }
    else if (positionX >= 9 && positionX <= 131 && positionY >= 69 && positionY <= 101 && !flagVitesse)
    {
        return vitesse;
    }
    else if (positionX >= 9 && positionX <= 131 && positionY >= 119 && positionY <= 151)
    {
        return modes;
    }
    else if (positionX >= 20 && positionX <= 110 && positionY >= 160 && positionY <= 180 && flagModes)
    {
        return libre;
    }
    else if (positionX >= 120 && positionX <= 210 && positionY >= 160 && positionY <= 180 && flagModes)
    {
        return enregistrer;
    }
    else if (positionX >= 20 && positionX <= 110 && positionY >= 190 && positionY <= 210 && flagModes)
    {
        return etendu;
    }
    else if (positionX >= 120 && positionX <= 210 && positionY >= 190 && positionY <= 210 && flagModes)
    {
        return debogage;
    }
    else if (positionX >= 144 && positionX <= 176 && positionY >= 69 && positionY <= 101 && flagVitesse)
    {
        return selectVitesse1;
    }
    else if (positionX >= 184 && positionX <= 216 && positionY >= 69 && positionY <= 101 && flagVitesse)
    {
        return selectVitesse2;
    }
    else if (positionX >= 224 && positionX <= 256 && positionY >= 69 && positionY <= 101 && flagVitesse)
    {
        return selectVitesse3;
    }
    else if (positionX >= 240 && positionX <= 310 && positionY >= 210 && positionY <= 230)
    {
        return fermer;
    }
    else if (positionX >= 240 && positionX <= 310 && positionY >= 180 && positionY <= 200)
    {
        return ok;
    }
    /*else if (positionX >= 60 && positionX <= 130 && positionY >= 100 && positionY <= 140)
    {
        return LedOn;
    }
    else if (positionX >= 190 && positionX <= 260 && positionY >= 100 && positionY <= 140)
    {
        return LedOff;
    }*/
    else
    {
        return attente;
    }
}