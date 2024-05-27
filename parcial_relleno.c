#include "./parcial_relleno.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

void inicializar_multiples(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 700.0, 0.0, 700.0);

}

//Funcion para dibujar lineas

void Bresenham(int x1, int y1, int x2, int y2) {
    //glColor3f(1.0, 0.843, 0.0);
    //glPointSize(3);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int pasos;
    if (dy > dx) {
        pasos = 1;
    } else {
        pasos = 0;
    }

    if (pasos) {
        int temp = x1;
        x1 = y1;
        y1 = temp;

        temp = x2;
        x2 = y2;
        y2 = temp;
    }

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    dx = x2 - x1;
    dy = abs(y2 - y1);
    int error = dx / 2;
    int ypasos = (y1 < y2) ? 1 : -1;
    int y = y1;

    for (int x = x1; x <= x2; x++) {
        if (pasos) {
            glBegin(GL_POINTS);
            glVertex2i(y, x);
            glEnd();
        } else {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }

        error -= dy;

        if (error < 0) {
            y += ypasos;
            error += dx;
        }
    }
}


// Función para dibujar un punto en la pantalla

void puntear(int x, int y) {
    //glColor3f(1.0, 0.843, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Función para dibujar el círculo utilizando el algoritmo de punto central

void circunferencia(int xcentro, int ycentro, int radio) {
    int x = 0;
    int y = radio;
    int p = 1 - radio;

    // Dibuja los puntos del círculo en los octantes correspondientes
    while (x <= y) {
        puntear(xcentro + x, ycentro + y);
        puntear(xcentro + y, ycentro + x);
        puntear(xcentro + y, ycentro - x);
        puntear(xcentro + x, ycentro - y);
        puntear(xcentro - x, ycentro - y);
        puntear(xcentro - y, ycentro - x);
        puntear(xcentro - y, ycentro + x);
        puntear(xcentro - x, ycentro + y);

        if (p < 0) {
            p += 2 * x + 3;
        } else {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

// Función para dibujar los octantes 7, 8, 1 y 2 de una elipse utilizando el algoritmo de punto central

void OctantefinalElipse(int a, int b, int xcentro, int ycentro) {
    int x = 0;
    int y = b;
    long a2 = a * a;
    long b2 = b * b;
    long fa2 = 4 * a2, fb2 = 4 * b2;
    long sigma = 2 * b2 + a2 * (1 - 2 * b);

    while (b2 * x <= a2 * y) {
        puntear(xcentro + x, ycentro + y);
        puntear(xcentro - x, ycentro + y);
        puntear(xcentro + x, ycentro - y);
        puntear(xcentro - x, ycentro - y);

        x++;
        if (sigma >= 0) {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    x = a;
    y = 0;
    sigma = 2 * a2 + b2 * (1 - 2 * a);

    while (a2 * y <= b2 * x) {
        puntear(xcentro + x, ycentro + y);
        puntear(xcentro - x, ycentro + y);
        puntear(xcentro + x, ycentro - y);
        puntear(xcentro - x, ycentro - y);

        y++;
        if (sigma >= 0) {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
}

void dibujar_multiples() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0); // Color de la frontera (blanco)

    //Contorno
    Bresenham(41, 250, 660, 250);
    Bresenham(660, 250, 642, 450);

    Bresenham(41, 250, 52, 450);
    Bresenham(52, 450, 642, 450);

    //Parte Interna
    
    //Derecha
    Bresenham(465, 250, 455, 450);
    
    Bresenham(606,250,590,437);
    Bresenham(456,437,590,437);
    
    //Ventanas
    //Contorno Arriba
    Bresenham(457,414,545,414);
    Bresenham(545,414,547,383);
    Bresenham(547,383,458,383);
    
    //Vidrios
    Bresenham(469,413,469,383);
    
    //Contorno Medio
    Bresenham(459,364,549,364);
    Bresenham(459,354,549,354);
    Bresenham(549,364, 551,326);
    Bresenham(551,325, 461, 325);
    
    //Vidrios
    circunferencia(503,340,8);
    
    
    //Contorno Bajo
    Bresenham(462,306, 552, 306);
    Bresenham(462,295, 552, 295);
    Bresenham(552, 306, 552, 268);
    Bresenham(552, 268, 463, 268);
    
    //Vidrios 
    
    
    
    //OctantefinalElipse(200,100, 350,175);


    
   

    //puntear(350,400);




    glFlush();
}

const char* get_carnet(void) {
    return "ZE17002";
}