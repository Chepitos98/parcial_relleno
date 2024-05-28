#include "./usos_multiples.h"
#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include <math.h>

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Usos multiples");
    glClearColor(0.8, 0, 0, 1);
    inicializar_usos_multiples();
    glutDisplayFunc(dibujar_usos_multiples);
    glutMainLoop();
    printf("=== fin ===");
    return (EXIT_SUCCESS);
}