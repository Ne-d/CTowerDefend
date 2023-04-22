#include <stdlib.h>
#include <stdio.h>
#include "listeSimple.h"
#include "towerDefendTypes.h"

//Initialise une liste
void initListe(T_liste *l)
{
    *l = NULL;
}

//V�rifie si une liste est vide
bool listeVide(T_liste l)
{
    return (l == NULL);
}

//Affiche la liste en param�tres
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

// M�me chose, mais affiche juste les noms
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

            courant = getPtrNextCell(courant);
            i++;
        }
        printf("\n");
    }
}

//Retourne le dernier pointeur d'une liste
T_liste getPtrLastCell(T_liste l)
{
    while(l->suiv != NULL)
    {
        l = l->suiv;
    }

    return l;
}

//Retourne le prochain pointeur de la liste
T_liste getPtrNextCell(T_liste l)
{
    return l->suiv;
}

//Retourne les informations du pointeur actuel
Tunite* getPtrData(T_liste l)
{
    return l->pdata;
}

//Ajoute � la t�te de la liste un nouvel �l�ment
T_liste ajoutEnTete(T_liste l, Tunite mydata)
{
    // Cr�er une nouvelle cellule et le pointeur vers une unit�.
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

//Ajoute � la fin de la liste un nouvel �l�ment
T_liste ajoutEnFin(T_liste l, Tunite mydata)
{
    // Si la liste est vide, initialise le pointeur � NULL et r�gler pdata � une nouvelle valeur
    if(listeVide(l))
    {
        l = malloc(sizeof(struct T_cell));
        l->pdata = malloc(sizeof(Tunite));
        l->suiv = NULL;
        *(l->pdata) = mydata;
    }
    else // Si la liste n'est pas vide
    {
        // Cr�e une nouvelle cellule.
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));

        // Assigne la nouvelle valeur � un champ de donn�es d'une nouvelle cellule
        *(newCell->pdata) = mydata;

        // Cela va garder un pointeur vers la derni�re cellule de la liste
        T_liste lastCell = l;

        // Cherche la derni�re cellule de la liste
        while(lastCell->suiv != NULL)
        {
            lastCell = lastCell->suiv;
        }

        newCell->suiv = NULL;
        lastCell->suiv = newCell;
    }

    return l;
}

//Ajoute un nouvel �l�ment dans la liste � l'indice N
T_liste ajoutEnN(T_liste l, int pos, Tunite mydata)
{
    if(listeVide(l)) // Si c'est vide
    {
        ajoutEnTete(l, mydata);
    }
    else if(pos == 0)
    {
        // Cr�e une nouvelle cellule
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));
        *(newCell->pdata) = mydata;

        newCell->suiv = l;

        return newCell;
    }
    // Si c'est pas vide et que la position n'est pas 0
    else
    {
        // Cr�e une nouvelle cellule
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));
        *(newCell->pdata) = mydata;

        // Cela va garder un pointeur vers la cellule d�sir� de la liste

        // Cherche la cellule avant l'indice d�sir�
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

//Enl�ve la cellule en t�te de la liste
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

//Enl�ve la cellule en fin de la liste
T_liste suppEnFin(T_liste l)
{
    // Si liste vide
    if (listeVide(l))
    {
        return l;
    }
    else
    {
        // Si liste � un �l�ment
        if(l->suiv == NULL)
        {
            free(l->pdata);
            free(l);

            return NULL;
        }

        // Sinon, elle en a plusieurs

        T_liste secondToLastCell = l;

        while(secondToLastCell->suiv->suiv != NULL)
        {
            secondToLastCell = secondToLastCell->suiv;
        }

        free(secondToLastCell->suiv->pdata);
        free(secondToLastCell->suiv);
        secondToLastCell->suiv = NULL;

        return l;
    }
}

//Enl�ve la cellule en n-i�me position de la liste
T_liste suppEnN(T_liste l, int pos)
{
    // Si liste vide
    if(listeVide(l))
    {
        return NULL;
    }

    // Si liste � un �l�ment
    if(l->suiv == NULL)
    {
        free(l->pdata);
        free(l);
        return NULL;
    }

    // Si la cellule d�sir�e est la premi�re
    if(pos == 0)
    {
        l = suppEnTete(l);

        return l;
    }

    // Cherche la cellule avant la cellule voulue (at position "pos")
    T_liste desiredCellPrev = l;
    for(int i = 1; i < pos; i++)
    {
        if(desiredCellPrev->suiv->suiv != NULL)
        {
            desiredCellPrev = desiredCellPrev->suiv;
        }
    }

    // Si la cellule d�sir�e est la derni�re
    if(desiredCellPrev->suiv->suiv == NULL) {
        l = suppEnFin(l);

        return l;
    }

    // Si la cellule d�sir�e est dans le milieu
    else
    {
        // Garde le pointeur de la cellule apr�s celle supp
        T_liste newSuiv = desiredCellPrev->suiv->suiv;

        // Free les cellules qu'on a retir�
        free(desiredCellPrev->suiv->pdata);
        free(desiredCellPrev->suiv);

        desiredCellPrev->suiv = newSuiv;

        return l;
    }
}

//Fonction fun inutilis� mais qui permet d'�changer les donn�es de deux cellules de listes
void swapPtrData(T_liste source, T_liste destination)
{
    Tunite* oldSourceData = source->pdata;

    source->pdata = destination->pdata;
    destination->pdata = oldSourceData;

}

//Donne le nb de cellules
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

//Donne la taille d'une cellule
int getSizeBytes(T_liste l)
{
    return getNbreCell(l) * (sizeof(struct T_cell) * sizeof(int));
}

//Supprime une liste
TListePlayer deleteList(TListePlayer l)
{
    TListePlayer firstCell = l;
    TListePlayer temp;
    for (temp = firstCell; !listeVide(temp);)
    {
        temp = suppEnFin(temp);
    }
    return temp;
}
