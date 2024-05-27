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
    glColor3f(1.0, 1.0, 1.0);
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

void BresenhamLinea(int x1, int y1, int x2, int y2) {
    glColor3f(0.0, 0.0, 1.0);
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

// Función para dibujar un píxel en la pantalla para relleno por frontera

void dibujarPuntofrontera(int x, int y, float *color) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    //Descomentar si se quiere en pantalla el llenado de "bandera" pixel por pixel ES MAS TARDADO
    glFlush();
}

// Función para obtener el color actual del píxel en la posición (x, y) en la pantalla

void pixelAcual(int x, int y, float *color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

// Función de relleno de áreas basada en fronteras de 8 vecinos

void rellenoporFrontera(int x, int y, float *rellenadoColor, float *colorFrontera) {
    float interiorColor[3];
    pixelAcual(x, y, interiorColor);
    if ((interiorColor[0] != colorFrontera[0] || interiorColor[1] != colorFrontera[1] || interiorColor[2] != colorFrontera[2]) &&
            (interiorColor[0] != rellenadoColor[0] || interiorColor[1] != rellenadoColor[1] || interiorColor[2] != rellenadoColor[2])) {
        dibujarPuntofrontera(x, y, rellenadoColor);
        rellenoporFrontera(x + 1, y, rellenadoColor, colorFrontera);
        rellenoporFrontera(x - 1, y, rellenadoColor, colorFrontera);
        rellenoporFrontera(x, y + 1, rellenadoColor, colorFrontera);
        rellenoporFrontera(x, y - 1, rellenadoColor, colorFrontera);
    }
    //Comprueba si se esta ejecutando
    //printf(".");
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

    //glColor3f(1.0, 1.0, 1.0); // Color de la frontera (blanco)

    float rellenoAzul[] = {0.0, 0.0, 1.0}; //Azul
    float rellenoCeleste[] = {0.0, 1.0, 1.0}; //Celeste
    float rellenoAmarillo[] = {1.0, 1.0, 0.0}; //Amarillo
    float borderColor[] = {1.0, 1.0, 1.0}; //color de la frontera
    float borderColor2[] = {0.0, 0.0, 1.0}; //color de la frontera(azul)

    //Contorno
    Bresenham(41, 250, 660, 250);
    Bresenham(660, 250, 660, 450);

    Bresenham(41, 250, 41, 450);
    Bresenham(41, 450, 660, 450);

    //Parte Interna

    //Derecha
    Bresenham(455, 250, 455, 450);
    Bresenham(606, 250, 606, 437);
    Bresenham(456, 437, 606, 437);

    //Ventanas
    //Contorno Arriba
    Bresenham(456, 416, 549, 416);
    Bresenham(549, 416, 549, 381);
    Bresenham(549, 381, 456, 381);

    //Vidrios
    BresenhamLinea(457, 414, 547, 414);
    BresenhamLinea(457, 413, 457, 383);
    BresenhamLinea(469, 413, 469, 383);
    BresenhamLinea(483, 413, 483, 383);
    BresenhamLinea(494, 413, 494, 383);
    BresenhamLinea(509, 413, 509, 383);
    BresenhamLinea(523, 413, 523, 383);
    BresenhamLinea(547, 414, 547, 383);
    BresenhamLinea(547, 383, 458, 383);

    //Contorno Medio
    Bresenham(456, 364, 552, 364);
    BresenhamLinea(457, 354, 550, 354);
    Bresenham(553, 364, 553, 323);
    Bresenham(553, 323, 456, 323);

    //Vidrios
    BresenhamLinea(457, 353, 457, 325);
    BresenhamLinea(471, 353, 471, 325);

    BresenhamLinea(485, 353, 485, 325);
    BresenhamLinea(498, 353, 498, 325);
    BresenhamLinea(514, 353, 514, 325);
    BresenhamLinea(528, 353, 528, 325);
    BresenhamLinea(550, 353, 550, 325);


    BresenhamLinea(550, 325, 457, 325);
    circunferencia(538, 340, 5);


    //Contorno Bajo
    Bresenham(456, 306, 555, 306);
    BresenhamLinea(458, 295, 552, 295);
    Bresenham(555, 306, 555, 266);
    Bresenham(555, 266, 456, 266);

    //Vidrios 
    BresenhamLinea(458, 295, 458, 268);
    BresenhamLinea(474, 295, 474, 268);
    BresenhamLinea(488, 295, 488, 268);



    BresenhamLinea(552, 295, 552, 268);
    BresenhamLinea(552, 268, 459, 268);


    //Parte Interna
    //Izquierda
    Bresenham(90, 250, 90, 437);
    Bresenham(90, 437, 220, 437);
    Bresenham(220, 450, 220, 250);

    //Ventanas


    OctantefinalElipse(175, 75, 350, 185);

    //Edificio
    //rellenoporFrontera(607, 251, rellenoAzul, borderColor);
    //rellenoporFrontera(605, 251, rellenoCeleste, borderColor);

    //Ventanas

    /*
        rellenoporFrontera(468, 384, rellenoAmarillo, borderColor2);
        rellenoporFrontera(470, 384, rellenoAmarillo, borderColor2);
        rellenoporFrontera(482, 384, rellenoAmarillo, borderColor2);
        rellenoporFrontera(484, 384, rellenoAmarillo, borderColor2);
        rellenoporFrontera(495, 384, rellenoAmarillo, borderColor2);
        rellenoporFrontera(510, 384, rellenoAmarillo, borderColor2);
        rellenoporFrontera(524, 384, rellenoAmarillo, borderColor2);
     */








    //puntear(350,400);




    glFlush();
    glutSwapBuffers();
}

const char* get_carnet(void) {
    return "ZE17002";
}