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

/*
void pintarLineaDDA(int x1, int y1, int x2, int y2) {
    glColor3f(0.2, 0.0, 0.6); //Color morado
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;
    float x = x1;
    float y = y1;

    glPointSize(4);
    glBegin(GL_POINTS); // Empezamos a dibujar puntos
    for (float i = 0; i < steps; i++) {
        x += xIncrement;
        y += yIncrement;
        glVertex2f(x, y); // Usamos glVertex2f para dibujar un punto en la posición (x, y)
    }
    glEnd(); // Terminamos de dibujar puntos
}
 */

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

// Función para dibujar un píxel en la pantalla para relleno por frontera

// Función para obtener el color del píxel en las coordenadas (x, y)

void getPixelColor(int x, int y, float* color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

// Función para establecer el color del píxel en las coordenadas (x, y)

void setPixelColor(int x, int y, float* color) {
    glColor3fv(color);
    glPointSize(1);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

// Algoritmo de Relleno por Frontera

void boundaryFill(int x, int y, float* fillColor, float* borderColor) {
    float color[3];
    getPixelColor(x, y, color);

    if ((color[0] != borderColor[0] || color[1] != borderColor[1] || color[2] != borderColor[2]) &&
            (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        setPixelColor(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, borderColor);
        boundaryFill(x - 1, y, fillColor, borderColor);
        boundaryFill(x, y + 1, fillColor, borderColor);
        boundaryFill(x, y - 1, fillColor, borderColor);
    }
}

void Octante1234(int radio, int xcentro, int ycentro) {
    int x = 0;
    int y = radio;
    int p = 1 - radio;

    while (x <= y) {
        // Dibuja los puntos en los octantes deseados
        puntear(xcentro + x, ycentro + y); // Octante 1
        puntear(xcentro + y, ycentro + x); // Octante 2
        puntear(xcentro - x, ycentro + y); // Octante 3
        puntear(xcentro - y, ycentro + x); // Octante 4

        x++;

        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

// Función para dibujar los octantes 7, 8, 1 y 2 del círculo utilizando el algoritmo de punto central

void Octantefinal(int radio, int xcentro, int ycentro) {
    int x = 0;
    int y = radio;
    int p = 1 - radio;

    while (x <= y) {
        puntear(xcentro + x, ycentro + y);
        puntear(xcentro + y, ycentro + x);

        puntear(xcentro + y, ycentro - x);
        puntear(xcentro + x, ycentro - y);

        x++;

        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
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
    /*
        float franjaAzul[] = {0.0, 0.0, 1.0};
        float franjaBlanca[] = {1.0, 1.0, 1.0};
        float borderColor[] = {1.0, 1.0, 0.0}; //color de la frontera
     */

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
    
    glFlush();
    //Octantefinal(150, 350, 150);
    //OctantefinalElipse(200,100, 350,175);


    // Rellenar áreas específicas
    float fillColor1[3] = {0.0, 0.0, 1.0}; // Color de relleno (azul)
    float fillColor2[3] = {0.0, 1.0, 1.0}; // Color de relleno (celeste)
    float fillColor3[3] = {1.0, 0.0, 1.0}; // Color de relleno (rojo)
    float fillColor4[3] = {1.0, 1.0, 0.0}; // Color de relleno (amarillo)
    float borderColor[3] = {1.0, 1.0, 1.0}; // Color de la frontera (blanco)

    // Rellenar el área principal del edificio
    //boundaryFill(456, 449, fillColor1, borderColor);
    boundaryFill(605, 251, fillColor2, borderColor);

    // Rellenar las ventanas
    boundaryFill(459, 398, fillColor3, borderColor); // Ventana superior izquierda
    //boundaryFill(220, 170, fillColor3, borderColor); // Ventana superior derecha
    //boundaryFill(170, 220, fillColor4, borderColor); // Ventana inferior izquierda
    //boundaryFill(220, 220, fillColor1, borderColor); // Ventana inferior derecha
    
    //Circuferencia
    boundaryFill(503, 340, fillColor4, borderColor); // Ventana inferior derecha
    

    //glFlush();

    //puntear(350,400);




    //glFlush();
}

const char* get_carnet(void) {
    return "ZE17002";
}