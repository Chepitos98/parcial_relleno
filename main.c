/* 
 * File:   main.c
 * Author: jose
 *
 * Created on 25 de mayo de 2024, 11:50
 */

#include "./parcial_relleno.h"
#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include <math.h>

int main(int argc, char** argv) {
    printf("Examen parcial de %s \n",get_carnet());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(700, 700);
    glutCreateWindow(get_carnet());
    glClearColor(0.8, 0, 0, 1);
    inicializar_multiples();
    glutDisplayFunc(dibujar_multiples);
    glutMainLoop();
    printf("=== fin ===");
    return (EXIT_SUCCESS);
}

