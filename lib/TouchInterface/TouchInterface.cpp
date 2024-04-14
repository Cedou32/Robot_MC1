/*      Fichier .cpp de la librairie TouchInterface         */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#include "TouchInterface.h"

StateInfo TouchInterface::detectBouton(int positionX, int positionY, bool flagMenu, bool flagModes, uint8_t flagSelectionMode, uint8_t flagSelectionEnregistrement)
{
    StateInfo result;

    if (positionX >= 209 && positionX <= 311 && positionY >= 9 && positionY <= 41)
    {
        result.etat = Menu;
        result.nom = "Menu";
    }
    else if (positionX >= 99 && positionX <= 221 && positionY >= 59 && positionY <= 91 && flagMenu == true)
    {
        result.etat = Modes;
        result.nom = "Modes";
    }
    else if (positionX >= 49 && positionX <= 151 && positionY >= 109 && positionY <= 136 && flagModes)
    {
        result.etat = Libre;
        result.nom = "Libre";
    }
    else if (positionX >= 169 && positionX <= 271 && positionY >= 109 && positionY <= 136 && flagModes)
    {
        result.etat = Enregistrer;
        result.nom = "Enregistrer";
    }
    else if (positionX >= 49 && positionX <= 151 && positionY >= 144 && positionY <= 171 && flagModes)
    {
        result.etat = Demo;
        result.nom = "Demo";
    }
    else if (positionX >= 169 && positionX <= 271 && positionY >= 144 && positionY <= 171 && flagModes)
    {
        result.etat = Debogage;
        result.nom = "Debogage";
    }
    else if (positionX >= 84 && positionX <= 236 && positionY >= 99 && positionY <= 131 && flagSelectionMode == 4 && flagSelectionEnregistrement > 0 && flagSelectionEnregistrement < 4)
    {
        result.etat = Enregistrer;
        result.nom = "Enregistrement";
    }
    else if (positionX >= 84 && positionX <= 236 && positionY >= 139 && positionY <= 171 && flagSelectionMode == 4 && flagSelectionEnregistrement > 0 && flagSelectionEnregistrement < 4)
    {
        result.etat = Enregistrer;
        result.nom = "Rejouer";
    }
    else if (positionX >= 69 && positionX <= 111 && positionY >= 129 && positionY <= 171 && flagSelectionMode == 4)
    {
        result.etat = Enregistrer;
        result.nom = "Enregistrement1";
    }
    else if (positionX >= 139 && positionX <= 181 && positionY >= 129 && positionY <= 171 && flagSelectionMode == 4)
    {
        result.etat = Enregistrer;
        result.nom = "Enregistrement2";
    }
    else if (positionX >= 209 && positionX <= 251 && positionY >= 129 && positionY <= 171 && flagSelectionMode == 4)
    {
        result.etat = Enregistrer;
        result.nom = "Enregistrement3";
    }
    else if (positionX >= 239 && positionX <= 311 && positionY >= 189 && positionY <= 221 && flagSelectionMode > 0 && flagSelectionMode <5 && flagModes)
    {
        result.etat = Selection;
        result.nom = "Selection";
    }
    else
    {
        result.etat = Attente;
        result.nom = "Attente";
    }

    return result;
}
