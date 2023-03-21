#include <stdlib.h>
#include <stdio.h>
#include "listeSimple.h"
#include "towerDefendTypes.h"

void initListe(T_liste *l)
{
    *l = NULL;
}

bool listeVide(T_liste l)
{
    return (l == NULL);
}

void afficheListe(T_liste l)
{
    if(listeVide(l))
    {
        printf("%s", "[]\n");
    }
    else
    {
        T_liste courant = l;

        printf("[ ");

        while(!listeVide(courant))
        {
            printf("%d ", *getPtrData(courant));
            courant = getPtrNextCell(courant);
        }
        printf("]\n");
    }
}

T_liste getPtrLastCell(T_liste l)
{
    while(l->suiv != NULL)
    {
        l = l->suiv;
    }

    return l;
}

T_liste getPtrNextCell(T_liste l)
{
    return l->suiv;
}

Tunite* getPtrData(T_liste l)
{
    return l->pdata;
}

T_liste ajoutEnTete(T_liste l, Tunite mydata)
{
    // Create a new cell to work with and the corresponding unit pointer.
    T_liste newLst = malloc(sizeof(struct T_cell));
    newLst->pdata = malloc(sizeof(Tunite));

    *(newLst->pdata) = mydata;

    if (listeVide(l))
    {
        newLst->suiv = NULL;
    }
    else
    {
        newLst->suiv = l;
    }

    return newLst;
}

T_liste ajoutEnFin(T_liste l, Tunite mydata)
{
    // If l is empty, initialize the pointers to NULL and set pdata to the new value
    if(listeVide(l))
    {
        l = malloc(sizeof(struct T_cell));
        l->pdata = malloc(sizeof(Tunite));
        l->suiv = NULL;
        *(l->pdata) = mydata;
    }
    else // If the list is not empty
    {
        // Create a new cell to work with.
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));

        // Assign the new value to the data field of the new cell
        *(newCell->pdata) = mydata;

        // This will hold a pointer to the last cell of l
        T_liste lastCell = l;

        // Find the last cell of l
        while(lastCell->suiv != NULL)
        {
            lastCell = lastCell->suiv;
        }

        newCell->suiv = NULL;
        lastCell->suiv = newCell;
    }

    return l;
}

/*T_liste ajoutEnN(T_liste l, int pos, Tunite mydata)
{
    if(listeVide(l)) // If l is empty
    {
        // Set the value of the first cell
        // Same as ajoutEnTete without boilerplate
        l->suiv = NULL;
        *(l->pdata) = mydata;
    }
    else if(pos == 0)
    {
        // Create a new cell to work with.
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));
        *(newCell->pdata) = mydata;

        newCell->suiv = l;

        return newCell;
    }
    // If l is not empty and pos is not 0
    else
    {
        // Create a new cell to work with.
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));
        *(newCell->pdata) = mydata;

        // This will hold a pointer to the desired cell of l
        T_liste desiredCell = l;

        // Find the cell at desired position
        bool reachedLastCell = false;
        desiredCell = findCell_old(l, pos, &reachedLastCell);

        if(reachedLastCell)
        {
            // ajoutEnFin, without boilerplate
            newCell->suiv = NULL;
            desiredCell->suiv = newCell;
        }
        else
        {
            newCell->suiv = desiredCell;
        }
    }

    return l;
}*/

