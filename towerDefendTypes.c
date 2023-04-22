#include "stdio.h"
#include "towerDefendTypes.h"

// Retourne une chaîne de caractères contenant le nom d'une unité selon son type.
char* stringUniteDuJeu(TuniteDuJeu u) {
    char* type = "";

    switch(u) {
        case tourSol:
            type = "Tour Sol";
            break;
        case tourAir:
            type = "Tour Air";
            break;
        case tourRoi:
            type = "Tour Roi";
            break;
        case archer:
            type = "Archer";
            break;
        case chevalier:
            type = "Chevalier";
            break;
        case dragon:
            type = "Dragon";
            break;
        case gargouille:
            type = "Gargouille";
            break;
    }

    return type;

}

// // Retourne une chaîne de caractères contenant le nom d'un type de cible.
char* stringCible(Tcible c) {
    char* cible = "";

    switch(c) {
    case sol:
        cible = "Sol"; break;
    case solEtAir:
        cible = "Sol et Air"; break;
    case air:
        cible = "Air"; break;

    }

    return cible;
}

// Affiche toutes les informations sur une unité.
void printUnite(Tunite u) {
    printf("Type d'unite: %s\n", stringUniteDuJeu(u.nom));
    printf("Cibles attaquable: %s\n", stringCible(u.cibleAttaquable));
    printf("Position: %s\n", stringCible(u.maposition));

    printf("PV: %d\n", u.pointsDeVie);
    printf("Vitesse d'attaque: %f\n", u.vitesseAttaque);
    printf("Degats: %d\n", u.degats);
    printf("Portee: %d\n", u.portee);

    printf("Vitesse de deplacement: %f\n", u.vitessedeplacement);
    printf("Position: %d, %d\n", u.posX, u.posY);
    printf("Peut attaquer: %s\n", u.peutAttaquer ? "Oui" : "Non");
}

// Affiche le nom d'une unité.
void printUniteShort(Tunite u)
{
    printf("Type d'unite: %s\n", stringUniteDuJeu(u.nom));
}
