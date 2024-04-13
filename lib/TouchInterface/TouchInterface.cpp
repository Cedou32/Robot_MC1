/*      Fichier .cpp de la librairie TouchInterface         */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#include "TouchInterface.h"

EtatLib TouchInterface::detectBouton(int positionX, int positionY, bool flagMenu, bool flagModes, uint8_t flagSelectionMode, uint8_t flagSelectionEnregistrement)
{
    if (positionX >= 209 && positionX <= 311 && positionY >= 9 && positionY <= 41)
    {
        return caseMenu;
    }
    else if (positionX >= 99 && positionX <= 221 && positionY >= 59 && positionY <= 91 && flagMenu == true)
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
    else if (positionX >= 84 && positionX <= 236 && positionY >= 99 && positionY <= 131 && flagSelectionMode == 4 && flagSelectionEnregistrement > 0 && flagSelectionEnregistrement < 4)
    {
        return caseEnregistrement;
    }
    else if (positionX >= 84 && positionX <= 236 && positionY >= 139 && positionY <= 171 && flagSelectionMode == 4 && flagSelectionEnregistrement > 0 && flagSelectionEnregistrement < 4)
    {
        return caseRejouer;
    }
    else if (positionX >= 69 && positionX <= 111 && positionY >= 129 && positionY <= 171 && flagSelectionMode == 4)
    {
        return caseEnregistrement1;
    }
    else if (positionX >= 139 && positionX <= 181 && positionY >= 129 && positionY <= 171 && flagSelectionMode == 4)
    {
        return caseEnregistrement2;
    }
    else if (positionX >= 209 && positionX <= 251 && positionY >= 129 && positionY <= 171 && flagSelectionMode == 4)
    {
        return caseEnregistrement3;
    }
    else if (positionX >= 239 && positionX <= 311 && positionY >= 189 && positionY <= 221 && flagSelectionMode > 0 && flagSelectionMode <5 && flagModes)
    {
        return caseSelection;
    }
    else
    {
        return caseAttente;
    }
}