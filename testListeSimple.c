#include "stdio.h"
#include "testListeSimple.h"
#include "listeSimple.h"

int testListeSimple() {
    T_liste l;

    // These values are completely bogus.
    Tunite testUnitRoi;
    testUnitRoi.nom = tourRoi;
    testUnitRoi.cibleAttaquable = solEtAir;
    testUnitRoi.maposition = sol;

    testUnitRoi.pointsDeVie = 200;
    testUnitRoi.vitesseAttaque = 2;
    testUnitRoi.degats = 30;
    testUnitRoi.portee = 20;

    testUnitRoi.vitessedeplacement = 1;
    testUnitRoi.posX = 4;
    testUnitRoi.posY = 2;
    testUnitRoi.peutAttaquer = 1;

    Tunite testUnit;
    testUnit.nom = dragon;
    testUnit.cibleAttaquable = solEtAir;
    testUnit.maposition = air;

    testUnit.pointsDeVie = 100;
    testUnit.vitesseAttaque = 1.5;
    testUnit.degats = 50;
    testUnit.portee = 30;

    testUnit.vitessedeplacement = 20;
    testUnit.posX = 6;
    testUnit.posY = 9;
    testUnit.peutAttaquer = 1;

    initListe(&l);

    l = ajoutEnTete(l, testUnitRoi);

    l = ajoutEnN(l, 1, testUnit);
    l = ajoutEnN(l, 1, testUnit);
    l = ajoutEnN(l, 1, testUnitRoi);
    l = ajoutEnN(l, 1, testUnit);


    afficheListeShort(l);
    return 0;
}
