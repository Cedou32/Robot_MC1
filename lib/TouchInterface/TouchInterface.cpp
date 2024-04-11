/*      Fichier .cpp de la librairie TouchInterface         */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#include "TouchInterface.h"

EtatLib TouchInterface::detectBouton(int positionX, int positionY, bool flagMenu, bool flagModes, uint8_t flagEnregistrement)
{
    if (positionX >= 210 && positionX <= 310 && positionY >= 10 && positionY <= 40)
    {
        return caseMenu;
    }
    else if (positionX >= 179 && positionX <= 301 && positionY >= 59 && positionY <= 91)
    {
        return caseModes;
    }
    else if (positionX >= 49 && positionX <= 151 && positionY >= 109 && positionY <= 136 && flagModes)
    {
        return caseLibre;
    }
    else if (positionX >= 169 && positionX <= 271 && positionY >= 109 && positionY <= 136 && flagModes)
    {
        return caseEnregistrer;
    }
    else if (positionX >= 49 && positionX <= 151 && positionY >= 144 && positionY <= 171 && flagModes)
    {
        return caseDemo;
    }
    else if (positionX >= 169 && positionX <= 271 && positionY >= 144 && positionY <= 171 && flagModes)
    {
        return caseDebogage;
    }
    else if (positionX >= 84 && positionX <= 236 && positionY >= 99 && positionY <= 131 && flagEnregistrement == 4)
    {
        return caseEnregistrement;
    }
    else if (positionX >= 84 && positionX <= 236 && positionY >= 139 && positionY <= 171 && flagEnregistrement == 4)
    {
        return caseRejouer;
    }
    else if (positionX >= 239 && positionX <= 311 && positionY >= 189 && positionY <= 221)
    {
        return caseSelection;
    }
    else
    {
        return caseAttente;
    }
}