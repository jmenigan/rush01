/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testrush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aangrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:51:52 by aangrand          #+#    #+#             */
/*   Updated: 2020/07/12 15:56:13 by aangrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

int verif(char line[], int way) //way 1 pour check le 1er paragraphem check 0 pour check le 2eme paragraphe
{
    int i;
    int count;
    char temp;

    temp = 0;
    if (way == 0)
    { // ce paragraphe permet de realiser le pdv du sudoku,
        i = 0;
        while(i < 4)
        {
            if (line[i] > temp)
            {
                temp = line[i]; // il boucle sur chaque case et il aug de 1 a chqaue foi et compte le nbr de fois ou il est sup a la case d'avant
                count++;
            }
            i++;
        }
    }
    else  // la meme chose que au dessu mais dans le sens inverse
    {
        i = 3;
        while(i >= 0)
        {
            if (line[i] > temp)
            {
                temp = line[i];
                count++;
            }
            i--;
        }
    }
    return (count); //il renvoi le nbr de fois ou il compte les cases
}

void randomize(char **tab, char pos)
{
    int temp;
    int i;
    int j;
    int x;
    char val = (tab[x][0] + tab[x][1]) * (tab[x][2] + tab[x][3]) + pos; // prend les 4 cases du tab et sa fait le calcule et ajoute la position de la ligne

    i = 0;
    j = 0;
    while(i < val)
    {
        while (j < val)
        {
            temp = tab[x][i]; //fait un swap x fois selon le char val
            tab[x][i] = tab[x][j];
            tab[x][j] = temp;
        }
    }
}

int find(char colup[4], char [4], char rowright[4], char rowleft[4])
{
    char tab[4][4] = {"1234", "1234", "1234", "1234"}; // creer un tableau avec tout les nums
    int verif_tab[] = {0, 0, 0, 0}; // tableau pour verif si les lignes sont ok, si 1, ok si 0, non
    int i;
    int n;
    int check;
    char tab_temp[4];
    int x;
    int y;

    check = 1;
    i = 0;
    while(check != 0)
    {
        if (verif_tab[i] == 0)
        {
            while(n < 4)
            {
                randomize(tab_temp[i],i);
                x = verif(tab[i],0); // chiffres auon attends de l'examinateur. dans les parametres de verif on va mettre une seule ligne du tableau qu'on veut verifier. le 0 ou 1 est pour check la valeur soit de droite soit de gauche
                y = verif(tab[i],1); // chiffres qu'on att de l'examinateur
                if (x == rowleft[n] && y == rowright[n]) // verifie si x = a ce aue lexaminateur a mis en rowL rowR
                {
                    verif_tab[n] = 1; // Si cest bon, ca met un 1 dans le verif_tab
                }
            }
        }
        if ((verif_tab[0] == 1 && verif_tab[1] == 1 && verif_tab[2] == 1 && verif_tab[3] == 1) || i == 1000) // ligne qui sert a verif si tout est a 1
        {
            check = 0;
        }
    }
}

 int main(int argc, char *argv[]) // argc nombre d'argument, ex : ./aout "1 2 3 5 4 6 5", y en a seuleent 2
                                    
{
    if (argc != 2) // si + de 2, sa fini
    {
        return(0);
    }

    int i;
    int n;
    char colup[4];
    char coldown[4];
    char rowright[4];
    char rowleft[4];

    i = 0;
    n = 0;
    while(argv[1][n] != '\0') // argv [ 1] pour tout les arguemnts situe dan le 1 (1 2 3 4 5 6 )
    {
        if (argv[1][n] >= '0' && argv[1][n] <= '9') // si ce sont des lettre et pas des chiffre, sa s'arette
        {
            if (i < 4)
                colup[i] = argv[1][n];
            else if (i < 8)
                coldown[i - 4] = argv[1][n];
            else if (i < 12)
                rowright[i - 8] = argv[1][n];
            else
                rowleft[i - 12] = argv[1][n];
            i++;
        }
        n++;
    }
    find(colup, coldown, rowleft, rowright); // lancer fnct find avec les tableaux en parametre
}
