/*      Fichier .cpp de la librairie TouchInterface         */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#include "TouchInterface.h"

EtatLib TouchInterface::detectBouton(int positionX, int positionY, bool flagMenu, bool flagModes)
{
    if (positionX >= 210 && positionX <= 310 && positionY >= 10 && positionY <= 40)
    {
        return menu;
    }
    else if (positionX >= 179 && positionX <= 301 && positionY >= 59 && positionY <= 91)
    {
        return modes;
    }
    else if (positionX >= 49 && positionX <= 151 && positionY >= 109 && positionY <= 136 && flagModes)
    {
        return libre;
    }
    else if (positionX >= 169 && positionX <= 271 && positionY >= 109 && positionY <= 136 && flagModes)
    {
        return enregistrer;
    }
    else if (positionX >= 49 && positionX <= 151 && positionY >= 144 && positionY <= 171 && flagModes)
    {
        return etendu;
    }
    else if (positionX >= 169 && positionX <= 271 && positionY >= 144 && positionY <= 171 && flagModes)
    {
        return debogage;
    }
    else if (positionX >= 239 && positionX <= 311 && positionY >= 189 && positionY <= 221)
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