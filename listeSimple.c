#include <stdlib.h>
#include <stdio.h>
#include "listeSimple.h"
#include "towerDefendTypes.h"

//Initialise une liste
void initListe(T_liste *l)
{
    *l = NULL;
}

//Vérifie si une liste est vide
bool listeVide(T_liste l)
{
    return (l == NULL);
}

//Affiche la liste en paramètres
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

// Affiche les noms des unités dans la liste en paramètre
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

//Retourne un pointeur vers la prochaine cellule de la liste
T_liste getPtrNextCell(T_liste l)
{
    return l->suiv;
}

// Retourne le pointeur vers les données de la case de la liste
Tunite* getPtrData(T_liste l)
{
    return l->pdata;
}

// Ajoute un élément au début d'une liste
T_liste ajoutEnTete(T_liste l, Tunite mydata)
{
    // Créer une nouvelle cellule et le pointeur vers une unité.
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

// Ajoute au début de la liste un nouvel élément en passant un pointeur
T_liste ajoutEnTeteParPtr(T_liste l, Tunite *mydata)
{
    // Créez une nouvelle cellule avec laquelle travailler et attribuer le pointeur pdata au pointeur donné mydata.
    T_liste newLst = malloc(sizeof(struct T_cell));
    newLst->pdata = mydata;

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

// Ajoute un élément à la fin d'une liste
T_liste ajoutEnFin(T_liste l, Tunite mydata)
{
    // Si c'est vide, initialise le pointeur a NULL et set pdata a la nouvelle valeur
    if(listeVide(l))
    {
        l = malloc(sizeof(struct T_cell));
        l->pdata = malloc(sizeof(Tunite));
        l->suiv = NULL;
        *(l->pdata) = mydata;
    }
    else // Si liste pas vide
    {
        // Cree une nouvelle cellule
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));

        // Assigne la nouvelle valeur au champ data de la nouvelle cellule
        *(newCell->pdata) = mydata;

        // Cela garde le pointeur a la dernière cellule de la liste
        T_liste lastCell = l;

        // Cherche la derniere cellule de la liste
        while(lastCell->suiv != NULL)
        {
            lastCell = lastCell->suiv;
        }

        newCell->suiv = NULL;
        lastCell->suiv = newCell;
    }

    return l;
}

// Ajoute un élément à la fin d'une liste en passant un pointeur
T_liste ajoutEnFinParPtr(T_liste l, Tunite *mydata)
{
    // Si c'est vide, initialise le pointeur a NULL et set pdata au nouveau pointeur
    if(listeVide(l))
    {
        l = malloc(sizeof(struct T_cell));
        l->suiv = NULL;
        l->pdata = mydata;
    }
    else //Si liste pas vide
    {
        // Cree une nouvelle cellule
        T_liste newCell = malloc(sizeof(struct T_cell));

        // Assigne la nouvelle valeur au champ data de la nouvelle cellule
        newCell->pdata = mydata;

        // Cela garde le pointeur a la dernière cellule de la liste
        T_liste lastCell = l;

        // Cherche la derniere cellule de la liste
        while(lastCell->suiv != NULL)
        {
            lastCell = lastCell->suiv;
        }

        newCell->suiv = NULL;
        lastCell->suiv = newCell;
    }

    return l;
}

// Ajoute un élément à une case de la liste, choisie par le paramètre pos.
T_liste ajoutEnN(T_liste l, int pos, Tunite mydata)
{
    if(listeVide(l)) // Si liste vide
    {
        ajoutEnTete(l, mydata);
    }
    else if(pos == 0)
    {
        // Crée une nouvelle cellule
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));
        *(newCell->pdata) = mydata;

        newCell->suiv = l;

        return newCell;
    }
    // Si liste pas vide et pos pas a 0
    else
    {
        // Crée une nouvelle cellule
        T_liste newCell = malloc(sizeof(struct T_cell));
        newCell->pdata = malloc(sizeof(Tunite));
        *(newCell->pdata) = mydata;

        // Cela garde le pointeur a la cellule désirée de la liste
        T_liste desiredCellPrev = l;

        // Cherche la cellule avant la position desirée
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
            // ajoutEnFin, sans boilerplate
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

// Supprime la cellule en tete de liste
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

//Supprime la cellule a la fin de la liste
T_liste suppEnFin(T_liste l)
{
    // Si liste vide
    if (listeVide(l))
    {
        return l;
    }
    else
    {
        // Si il y a qu'une cellule
        if(l->suiv == NULL)
        {
            free(l->pdata);
            free(l);

            return NULL;
        }

        // Sinon, plusieurs cellules

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

//Supprime la cellule à l'indice n
T_liste suppEnN(T_liste l, int pos)
{
    // Si liste vide
    if(listeVide(l))
    {
        return NULL;
    }

    // Si liste a une cellule
    if(l->suiv == NULL)
    {
        free(l->pdata);
        free(l);
        return NULL;
    }

    // Si la cellule voulue est en premier
    if(pos == 0)
    {
        l = suppEnTete(l);

        return l;
    }

    // Cherche la cellule avant celle désirée (a la position "pos")
    T_liste desiredCellPrev = l;
    for(int i = 1; i < pos; i++)
    {
        if(desiredCellPrev->suiv->suiv != NULL)
        {
            desiredCellPrev = desiredCellPrev->suiv;
        }
    }

    // Si la cellule désirée est la dernière
    if(desiredCellPrev->suiv->suiv == NULL) {
        l = suppEnFin(l);

        return l;
    }

    // Si la cellule est dans le milieu
    else
    {
        // Garde le pointeur vers la cellule suivante de celle supprimé
        T_liste newSuiv = desiredCellPrev->suiv->suiv;

        // Free de la cellule qu'on retire
        free(desiredCellPrev->suiv->pdata);
        free(desiredCellPrev->suiv);

        desiredCellPrev->suiv = newSuiv;

        return l;
    }
}

// Echange deux cases dans la liste sans toucher aux données, mais en échangeant les pointeurs
void swapPtrData(T_liste source, T_liste destination)
{
    Tunite* oldSourceData = source->pdata;

    source->pdata = destination->pdata;
    destination->pdata = oldSourceData;

}

// Retourne le nombre de cellules dans la liste
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

// Retourne la taille totale en mémoire d'une liste
int getSizeBytes(T_liste l)
{
    return getNbreCell(l) * (sizeof(struct T_cell) * sizeof(int));
}

// Supprime une liste
T_liste supprimeListe(TListePlayer l)
{
    TListePlayer temp;
    for (temp = l; !listeVide(temp);)
    {
        temp = suppEnTete(temp);
    }
    return temp;
}

// Retourne un tableau qui contient toutes les données de la liste l, bout à bout.
Tunite* listToArray(TListePlayer l, int *length)
{
    Tunite* ptr = malloc(getSizeBytes(l));

    int i = 0;
    while(l != NULL)
    {
        ptr[i] = *getPtrData(l);
        l = getPtrNextCell(l);
        i++;
    }

    *length = i;

    return ptr;
}

// Retourne une liste qui contient toutes les données du tableau arr.
T_liste arrayToList(Tunite* arr, int length)
{
    TListePlayer l;
    initListe(&l);

    for(int i = 0; i < length; i++)
    {
        l = ajoutEnFin(l, arr[i]);
    }

    return l;
}
