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
        printf("afficheListe: Liste vide.\n\n");
    }
    else
    {
        unsigned int i = 0;
        T_liste courant = l;

        printf("Affiche Liste:\n");

        while(!listeVide(courant))
        {
            printf("Unite %d:\n", i);
            printUnite(*getPtrData(courant));
            printf("\n");

            courant = getPtrNextCell(courant);
            i++;
        }
        printf("\n");
    }
}

void afficheListeShort(T_liste l)
{
    if(listeVide(l))
    {
        printf("afficheListe Short: Liste vide.\n\n");
    }
    else
    {
        unsigned int i = 0;
        T_liste courant = l;

        printf("Affiche Liste Short:\n");

        while(!listeVide(courant))
        {
            printf("Unite %d: ", i);
            printUniteShort(*getPtrData(courant));
            printf("\n");

            courant = getPtrNextCell(courant);
            i++;
        }
        printf("\n");
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
    // Create a new cell to work with and the corresponding pointer to a unit.
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

T_liste ajoutEnN(T_liste l, int pos, Tunite mydata)
{
    if(listeVide(l)) // If l is empty
    {
        // Set the value of the first cell
        // Same as ajoutEnTete without boilerplate
        l->suiv = NULL;
        l->pdata = malloc(sizeof(Tunite));
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
        T_liste desiredCellPrev = l;

        // Find the cell before the desired position
        bool reachedLastCell = false;
        for(int i = 0; i < pos - 1; i++)
        {
            if(desiredCellPrev->suiv != NULL)
            {
                desiredCellPrev = desiredCellPrev->suiv;
            }
            else
            {
                reachedLastCell = true;
            }
        }

        if(reachedLastCell)
        {
            // ajoutEnFin, without boilerplate
            newCell->suiv = NULL;
            desiredCellPrev->suiv = newCell;
        }
        else
        {
            newCell->suiv = desiredCellPrev->suiv;
            desiredCellPrev->suiv = newCell;
        }
    }

    return l;
}

T_liste suppEnTete(T_liste l)
{
    if (listeVide(l))
    {
        return l;
    }
    else
    {
        T_liste newFirst = NULL;

        newFirst = l->suiv;

        free(l->pdata);
        free(l);

        return newFirst;
    }
}

T_liste suppEnFin(T_liste l)
{
    // If the list is empty
    if (listeVide(l))
    {
        return l;
    }
    else
    {
        // If the list has one cell
        if(l->suiv == NULL)
        {
            free(l->pdata);
            free(l);

            return NULL;
        }

        // Else, the list has more than one cell

        T_liste lastCell = l;

        while(lastCell->suiv != NULL)
        {
            lastCell = lastCell->suiv;
        }

        free(lastCell->pdata);
        free(lastCell);

        return l;
    }
}

T_liste suppEnN(T_liste l, int pos)
{
    // If the list is empty
    if(listeVide(l))
    {
        return NULL;
    }

    // If the list has only one cell
    if(l->suiv == NULL)
    {
        free(l->pdata);
        free(l);
        return NULL;
    }

    // Else, the list must have more than one cell

    // Find the desired cell (at position "pos")
    T_liste desiredCell = l;
    T_liste desiredCellPrec = l;
    for(int i = 0; i < pos; i++)
    {
        if(desiredCell->suiv != NULL)
        {
            desiredCell = desiredCell->suiv;
        }
        if(desiredCellPrec->suiv->suiv != NULL || i < pos - 1)
        {
            desiredCellPrec = desiredCellPrec->suiv;
        }
    }

    // If the desired cell is the last
    if(desiredCell->suiv == NULL) {
        desiredCellPrec->suiv = NULL;

        free(desiredCell->pdata);
        free(desiredCell);

        return l;
    }
    // If the desired cell is somewhere in the middle
    else
    {
        desiredCellPrec->suiv = desiredCell->suiv;

        free(desiredCell->pdata);
        free(desiredCell);

        return l;
    }
}

void swapPtrData(T_liste source, T_liste destination)
{
    Tunite* oldSourceData = source->pdata;

    source->pdata = destination->pdata;
    destination->pdata = oldSourceData;

}

int getNbreCell(T_liste l)
{
    if(listeVide(l))
    {
        return 0;
    }

    else
    {
        int i = 1;

        while(l->suiv != NULL)
        {
            l = l->suiv;
            i++;
        }

        return i;
    }
}

int getSizeBytes(T_liste l)
{
    return getNbreCell(l) * (sizeof(struct T_cell) * sizeof(int));
}
