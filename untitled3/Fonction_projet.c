#include "Fonction_projet.h"
#include <stdio.h>
#include <stdlib.h>
#include "Id.h"
/* -----------------------------------Debut Point--------------------------*/
Point *create_point(int px, int py)
{
    Point *forme = (Point*)malloc(sizeof(Point));
    forme->pos_x = px;
    forme->pos_y = py;
    return forme;
}

void delete_point(Point * point)
{
    free(point);
}

void print_point(Point * p)
{
    printf("POINT %d %d \n", p->pos_x, p->pos_y );
}
/* -----------------------------------Fin Point--------------------------*/
/* -----------------------------------Debut Line--------------------------*/

Line *create_line(Point * p1, Point * p2)
{
    Line *forme = (Line*)malloc(sizeof(Line));
    forme->p1 = p1;
    forme->p2 = p2;
    return forme;
}

void delete_line(Line * line)
{
    free(line->p1);
    free(line->p2);
    free(line);


}

void print_line(Line * line)
{
    printf("LINE %d %d %d %d \n", line->p1->pos_x, line->p1->pos_y, line->p2->pos_x, line->p2->pos_y);
}

/* -----------------------------------Fin Line--------------------------*/
/* -------------------------------Debut Square--------------------------*/
Square *create_square(Point * point, int length)
{
    Square * forme = (Square*)malloc(sizeof(Square));
    forme->p1 = point;
    forme->largeur = length;
    return forme;
}

void delete_square(Square * square)
{
    delete_point(square->p1);
    free(square);
}

void print_square(Square * square)
{
    printf("SQUARE (%d;%d) (%d;%d) (%d;%d) (%d;%d)\n", square->p1->pos_x, square->p1->pos_y, square->p1->pos_x, square->p1->pos_y + square->largeur, square->p1->pos_x + square->largeur, square->p1->pos_y + square->largeur, square->p1->pos_x + square->largeur, square->p1->pos_y);

}
/* -----------------------------------Fin Square--------------------------*/
/* -----------------------------------Debut Rectangle--------------------------*/

Rectangle *create_rectangle(Point * point, int width, int height)
{
    Rectangle * forme = (Rectangle *)malloc(sizeof(Rectangle));
    forme->p1 = point;
    forme->width = width;
    forme->height = height;

    return forme;
}

void delete_rectangle(Rectangle * rectangle)
{
    delete_point(rectangle->p1);
    free(rectangle);
}

void print_rectangle(Rectangle * rectangle)
{
    printf("RECTANGLE (%d;%d) (%d;%d) (%d;%d) (%d;%d)\n", rectangle->p1->pos_x, rectangle->p1->pos_y,
           rectangle->p1->pos_x, rectangle->p1->pos_y +rectangle->height,
           rectangle->p1->pos_x + rectangle->width, rectangle->p1->pos_y+ rectangle->height,
           rectangle->p1->pos_x + rectangle->width, rectangle->p1->pos_y);
}

/* -----------------------------------Fin Rectangle--------------------------*/
/* -----------------------------------Debut Cercle--------------------------*/

Circle *create_circle(Point * center, int radius)
{
    Circle *forme = (Circle *) malloc(sizeof (Circle));
    forme->p1 = center;
    forme->radius = radius;
    return forme;

}

void delete_circle(Circle * circle)
{
    delete_point(circle->p1);
    free(circle);
}

void print_circle(Circle * circle)
{
    printf("CIRCLE (%d;%d) radius : %d \n",circle->p1->pos_x,circle->p1->pos_y,circle->radius);
}
/* -----------------------------------Fin Cercle--------------------------*/
/* -----------------------------------Debut Polygon--------------------------*/
int are_same_points(Point* a, Point* b)
    {
    if ( (a->pos_x == b->pos_x) && (a->pos_y == b->pos_y))
        {
        return 1;
        }
    return 0;
    }
Polygon* create_polygon(int sommets, Point** pts)
{
    Polygon* forme = (Polygon*)malloc(sizeof(Polygon));
    forme->sommets = sommets;
    forme->points = (Point **)malloc(sommets * sizeof(Point *));
    for (int i = 0; i < sommets; i++)
        {
        forme->points[i] = pts[i];
        }
    if (!are_same_points(forme->points[0], forme->points[sommets - 1])) {
        Point* pts2 = create_point(forme->points[0]->pos_x, forme->points[0]->pos_y);
        forme->points = (Point**)realloc(forme->points, (sommets + 1) * sizeof(Point*));
        forme->points[sommets] = pts2;
        forme->sommets++;
    }

    return forme;
}


void delete_polygon(Polygon * polygon)
{
    for (int i = 0; i < polygon->sommets; i++)
        {
        delete_point(polygon->points[i]);
        }
    free(polygon->points);
    free(polygon);
}

void print_polygon(Polygon *polygon)
{
    printf("Polygone : ");
    for (int i = 0; i < polygon->sommets; i++)
    {
        printf("Point %d : ", i+1);
        print_point(polygon->points[i]);
    }
    printf("\n");
}
/*-------------------------Fin Polygon----------------------------*/
/*-------------------------Debut Shape----------------------------*/

Shape *create_empty_shape(SHAPE_TYPE shape_type) {
    Shape *shp = (Shape *) malloc(sizeof(Shape));
    shp->ptrShape = NULL;
    shp->id = 1; // plus tard on appelera get_next_id();
    shp->shape_type = shape_type;
    return shp;
}

Shape *create_point_shape(int px, int py) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(px, py);
    shp->ptrShape = p;
    shp->id = get_next_id();
    return shp;
}

Shape *create_line_shape(int px1, int py1, int px2, int py2){
    Shape *shp = create_empty_shape(LINE);
    Point * p1 = create_point(px1, py1);
    Point * p2 = create_point(px2, py2);
    Line *l1 = create_line(p1, p2);
    shp->ptrShape = l1;
    shp->id = get_next_id();
    return shp;

}

Shape *create_square_shape(int px, int py, int length){
    Shape *shp = create_empty_shape(SQUARE);
    Point * p = create_point(px, py);
    Square *s1 = create_square(p,length);
    shp -> ptrShape = s1;
    shp->id = get_next_id();
    return shp;
}

Shape *create_rectangle_shape(int px, int py, int width, int height){
    Shape *shp = create_empty_shape(RECTANGLE);
    Point * p = create_point(px, py);
    Rectangle *r1 = create_rectangle(p, width, height);
    shp -> ptrShape = r1;
    shp->id = get_next_id();
    return shp;

}

Shape *create_circle_shape(int px, int py, int radius){
    Shape *shp = create_empty_shape(CIRCLE);
    Point * p = create_point(px, py);
    Circle * c1 = create_circle(p, radius);
    shp -> ptrShape = c1;
    shp->id = get_next_id();
    return shp;
}

Shape *create_polygon_shape(int coordonnees[], int n)
{
    Shape *shp = create_empty_shape(POLYGON);
    if (n % 2 != 0) return NULL;
    Point **pts = (Point**)malloc(n / 2 * sizeof(Point *));
    for (int i = 0; i < n / 2; i++) {
        pts[i] = create_point(coordonnees[i * 2], coordonnees[i * 2 + 1]);
    }
    Polygon *p1 = create_polygon(n / 2, pts);
    shp->ptrShape = p1;
    shp->id = get_next_id();
    return shp;
}


void delete_shape(Shape * shape) {
    switch (shape->shape_type) {
        case POINT:
            delete_point(shape->ptrShape);
            break;
        case LINE:
            delete_line(shape->ptrShape);
            break;
        case CIRCLE:
            delete_circle(shape->ptrShape);
            break;
        case SQUARE:
            delete_square(shape->ptrShape);
            break;
        case RECTANGLE:
            delete_rectangle(shape->ptrShape);
            break;
        case POLYGON:
            delete_polygon(shape->ptrShape);
            break;
    }
    free(shape);
}
void print_shape(Shape *shape){
    switch (shape->shape_type) {
        case POINT:
            print_point((Point*) shape->ptrShape);
            break;
        case LINE:
            print_line((Line*) shape->ptrShape);
            break;
        case SQUARE:
            print_square((Square*) shape->ptrShape);
            break;
        case RECTANGLE:
            print_rectangle((Rectangle*) shape->ptrShape);
            break;
        case CIRCLE:
            print_circle((Circle*) shape->ptrShape);
            break;
        case POLYGON:
            print_polygon((Polygon*) shape->ptrShape);
            break;
    }
}








