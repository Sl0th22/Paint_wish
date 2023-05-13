#include <stdio.h>
#include "Fonction_projet.h"
#include "area.h"
#include "Commande.h"
int main(){
    Command* cmd;
    int a, b;
    printf("Entrez la longueur du plateau : \n>>");
    scanf(" %d", &a);
    printf("\nEntrez la largeur du plateau : \n>>");
    scanf(" %d", &b);
    Area * draw_zone = create_area(a, b);
    int arret = 1;
    while (arret) {
        cmd = create_command();
        printf(">>");
        read_from_stdin(cmd);
        int num = read_exec_command(cmd, draw_zone);
        if (num == 0)
        {
            arret = 0;
        }
        free_cmd(cmd);
    }
    return 0;
}
