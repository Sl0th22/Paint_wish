#include "Commande.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "area.h"


Command* create_command() {
    Command* cmd = (Command*)malloc(sizeof(Command));
    cmd->int_size = 0;
    cmd->str_size = 0;
    return cmd;
}

void add_str_param(Command* cmd, char* p) {
    cmd->str_params[cmd->str_size] = p;
    cmd->str_size++;
}

void add_int_param(Command* cmd, int p) {
    cmd->int_params[cmd->int_size] = p;
    cmd->int_size++;
}

void free_cmd(Command* cmd) {
    free(cmd);
}

int read_exec_command(Command* cmd, Area * draw_zone) {
    if (strcmp(cmd->name, "clear") == 0) {
        printf("Effacage de l'ecran\n");
        // Code pour effacer l'écran
        system("cls");
        return 1;

    } else if (strcmp(cmd->name, "exit") == 0) {
        printf("Quitter le programme\n");
        delete_area(draw_zone);
        return 0;
    } else if (strcmp(cmd->name, "point") == 0) {
        if (cmd->int_size != 2) {
            printf("Erreur: Nombre de parametres incorrect pour la commande 'point'.\n");
            return 1;
        }

        int x = cmd->int_params[0];
        int y = cmd->int_params[1];

        printf("Ajout du point: (%d, %d)\n", x, y);
        // Code pour ajouter un point
        Shape *shape1 = create_point_shape(x, y);
        add_shape_to_area(draw_zone, shape1);
        return 1;

    } else if (strcmp(cmd->name, "line") == 0) {
        if (cmd->int_size != 4) {
            printf("Erreur: Nombre de parametres incorrect pour la commande 'line'.\n");
            return 1;
        }

        int x1 = cmd->int_params[0];
        int y1 = cmd->int_params[1];
        int x2 = cmd->int_params[2];
        int y2 = cmd->int_params[3];

        printf("Ajout du segment reliant les points (%d, %d) et (%d, %d)\n", x1, y1, x2, y2);
        // Code pour ajouter un segment
        Shape *shape1 = create_line_shape(x1, y1, x2, y2);
        add_shape_to_area(draw_zone, shape1);
    } else if (strcmp(cmd->name, "circle") == 0) {
        if (cmd->int_size != 3) {
            printf("Erreur: Nombre de parametres incorrect pour la commande 'circle'.\n");
            return 1;
        }

        int x = cmd->int_params[0];
        int y = cmd->int_params[1];
        int radius = cmd->int_params[2];

        printf("Ajout du cercle de centre (%d, %d) et de rayon %d\n", x, y, radius);
        // Code pour ajouter un cercle
        Shape *shape1 = create_circle_shape(x, y, radius);
        add_shape_to_area(draw_zone, shape1);
        return 1;
    } else if (strcmp(cmd->name, "square") == 0) {
        if (cmd->int_size != 3) {
            printf("Erreur: Nombre de parametres incorrect pour la commande 'square'.\n");
            return 1;
        }

        int x = cmd->int_params[0];
        int y = cmd->int_params[1];
        int length = cmd->int_params[2] - 1;

        printf("Ajout du carré ayant comme coin superieur gauche (%d, %d) et de cote %d\n", x, y, cmd->int_params[2]);
        //code
        Shape *shape1 = create_square_shape(x, y, length);
        add_shape_to_area(draw_zone, shape1);
        return 1;
    } else if (strcmp(cmd->name, "rectangle") == 0) {
        if (cmd-> int_size != 4) {
            printf("Erreur : Nombre de parametres incorrect pour la commande 'rectangle'.\n");
            return 1;
        }

        int x = cmd->int_params[0];
        int y = cmd->int_params[1];
        int width = cmd->int_params[2] - 1;
        int height = cmd->int_params[3] - 1;

        printf("Ajout du rectangle ayant comme coin superieur gauche (%d, %d) de largeur %d et de longueur %d\n",
               x, y, cmd->int_params[2], cmd->int_params[3]);
        //code
        Shape *shape1 = create_rectangle_shape(x, y, width, height);
        add_shape_to_area(draw_zone, shape1);
        return 1;
    }
        else if (strcmp(cmd->name, "polygon")==0) {
            for (int i = 0; i < cmd->int_size;i++){
            }
            if (cmd->int_size %2 != 0) {
                printf("Erreur : Nombre de parametres incorrect pour la commande 'polygon'.\n");
                return 1;
            }
            Shape * shape1 = create_polygon_shape(cmd->int_params,cmd->int_size);
            add_shape_to_area(draw_zone, shape1);
            return 1;
            }
    else if (strcmp(cmd->name, "plot") == 0){
        printf("Rafraichissement de l'ecran \n");
        //code rafraichir l'écran
        draw_area(draw_zone);
        print_area(draw_zone);
    }
    else if (strcmp(cmd->name, "list")==0){
        printf("Affichage de toutes les formes qui composent l'image\n");
        //code
        for (int i = 0; i < draw_zone->nb_shape; i++) {
            print_shape(draw_zone->shapes[i]);
        }
        return 1;
    }
    else if (strcmp(cmd->name, "delete") == 0) {
        if(cmd -> int_size != 1){
            printf("Erreur : Nombre de parametres incorrect pour la commande 'delete'.\n");
            return 1;
        }
        int id = cmd->int_params[0];
        printf("Suppresion de la forme d'id %d\n", id);
        //code supprimer forme
        int cpt = 0;
        for (int i = 0; i < draw_zone->nb_shape; i++){
            if (draw_zone->shapes[i]->id == id){
                cpt ++;
                delete_shape(draw_zone->shapes[i]);
            }
        }
        if (cpt != 1) {
            printf("Aucune forme avec l'identifiant %d trouvée.\n", id);
            return 1;
        }
    }
    else if (strcmp(cmd->name, "erase") == 0) {
        printf("Suppresion de toutes les formes de l'image.\n");
        //code
        erase_area(draw_zone);
        clear_area(draw_zone);
        print_area(draw_zone);
        return 1;
    }
     else if (strcmp(cmd->name, "help") == 0) {
        printf("Liste des commandes : \n");
        printf("- clear : effacer l’ecran \n");
        printf("- exit : quitter le programme \n");
        printf("- point x y : ajouter un point \n");
        printf("- line x1 y1 x2 y2 : ajouter un segment reliant deux points (x1, y1) et (x2, y2)\n");
        printf("- circle x y radius : ajouter un cercle de centre (x, y) et de rayon radius\n");
        printf("- square x y length : ajouter un carre dont le coin supérieur gauche est (x, y) et de cote length.\n");
        printf("- rectangle x y width height : ajouter un rectangle dont le coin superieur gauche est (x, y), de "
               "largeur width et de longueur height\n");
        printf("- polygon x1 y1 x2 y2 x3 y3 ... ... : ajouter un polygone avec la liste des points donnes \n");
        printf("- plot : affichage de l'image (area)\n");
        printf("- list : affichage d'une liste de l'ensemble des formes crees\n");
        printf("- delete id : apres avoir lancer la commande list, l'id est en partant du haut vers le bas et commence par 1\n");
        printf("- help : :)\n");

        return 1;
    }
}

void read_from_stdin(Command* cmd) {
    char comm[120];
    fgets(comm, sizeof(comm), stdin);

    // Vérifier si la ligne est vide
    if (comm[0] == '\n') {
        return;
    }

    char* token = strtok(comm, " \n");
    strcpy(cmd->name, token);

    token = strtok(NULL, " \n");
    while (token != NULL) {
        if (atoi(token) != 0) {
            add_int_param(cmd, atoi(token));
        } else {
            add_str_param(cmd, token);
        }
        token = strtok(NULL, " \n");
    }
}