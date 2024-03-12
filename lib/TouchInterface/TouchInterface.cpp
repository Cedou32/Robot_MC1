/*      Fichier .cpp de la librairie TouchInterface         */
/*Cette permet de detecter sur quel bouton l'utilisateur    */
/*a appuye et ainsi retourner l'etat dans lequel le code    */
/*                 principal doit continuer                 */
/*Créée par Mihai Stinga                                    */

#include "TouchInterface.h"

EtatLib TouchInterface::detectBouton(int positionX, int positionY, bool flagMenu, bool flagVitesse, bool flagModes) {
    if (positionX >= 210 && positionX <= 310 && positionY >= 10 && positionY <= 40 && !flagMenu) {
        return menu;
    } else if (positionX >= 10 && positionX <= 90 && positionY >= 50 && positionY <= 70 && !flagVitesse) {
        return vitesse;
    } else if (positionX >= 10 && positionX <= 90 && positionY >= 80 && positionY <= 100) {
        return modes;
    } else if (positionX >= 120 && positionX <= 210 && positionY >= 80 && positionY <= 100 && flagModes) {
        return libre;
    } else if (positionX >= 220 && positionX <= 310 && positionY >= 80 && positionY <= 100 && flagModes) {
        return enregistrer;
    } else if (positionX >= 120 && positionX <= 210 && positionY >= 110 && positionY <= 130 && flagModes) {
        return etendu;
    } else if (positionX >= 220 && positionX <= 310 && positionY >= 110 && positionY <= 130 && flagModes) {
        return debogage;
    } else if (positionX >= 120 && positionX <= 140 && positionY >= 50 && positionY <= 70 && flagVitesse) {
        return selectVitesse1;
    } else if (positionX >= 150 && positionX <= 170 && positionY >= 50 && positionY <= 70 && flagVitesse) {
        return selectVitesse2;
    } else if (positionX >= 180 && positionX <= 200 && positionY >= 50 && positionY <= 70 && flagVitesse) {
        return selectVitesse3;
    } else if (positionX >= 240 && positionX <= 310 && positionY >= 210 && positionY <= 230) {
        return fermer;
    } else if (positionX >= 240 && positionX <= 310 && positionY >= 180 && positionY <= 200) {
        return ok;
    } else { 
        return attente;
    }
}