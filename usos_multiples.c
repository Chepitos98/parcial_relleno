#include "./usos_multiples.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

void inicializar_usos_multiples(void) {
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
    //glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void puntearElipse(int x, int y) {
    glColor3f(0.0, 0.0, 1.0);
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

// Función para dibujar una elipse utilizando el algoritmo de punto central

void Elipse(int a, int b, int xcentro, int ycentro) {
    int x = 0;
    int y = b;
    long a2 = a * a;
    long b2 = b * b;
    long fa2 = 4 * a2, fb2 = 4 * b2;
    long sigma = 2 * b2 + a2 * (1 - 2 * b);

    while (b2 * x <= a2 * y) {
        puntearElipse(xcentro + x, ycentro + y);
        puntearElipse(xcentro - x, ycentro + y);
        puntearElipse(xcentro + x, ycentro - y);
        puntearElipse(xcentro - x, ycentro - y);

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
        puntearElipse(xcentro + x, ycentro + y);
        puntearElipse(xcentro - x, ycentro + y);
        puntearElipse(xcentro + x, ycentro - y);
        puntearElipse(xcentro - x, ycentro - y);

        y++;
        if (sigma >= 0) {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
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

void dibujar_usos_multiples() {
    glClear(GL_COLOR_BUFFER_BIT);

    //glColor3f(1.0, 1.0, 1.0); // Color de la frontera (blanco)

    float rellenoAzul[] = {0.0, 0.0, 1.0}; //Azul
    float rellenoCeleste[] = {0.0, 1.0, 1.0}; //Celeste
    float rellenoAmarillo[] = {0.0, 0.0, 0.0}; //Blanco
    float rellenoRandom[] = {1.0, 1.0, 0.0}; //Amarillo
    float rellenoVerde[] = {0.0, 1.0, 0.0};
    float borderColor[] = {1.0, 1.0, 1.0}; //color de la frontera
    float borderColor2[] = {0.0, 0.0, 1.0}; //color de la frontera(azul)
    float borderColor3[] = {1.0, 1.0, 0.0}; //color de la frontera(amarillo)

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
    //Contorno Derecha Arriba
    Bresenham(456, 416, 549, 416);
    Bresenham(549, 416, 549, 381);
    Bresenham(549, 381, 456, 381);

    //Vidrios Derecha Arriba
    BresenhamLinea(457, 414, 547, 414);
    BresenhamLinea(457, 413, 457, 383);
    BresenhamLinea(469, 413, 469, 383);
    BresenhamLinea(483, 413, 483, 383);
    BresenhamLinea(494, 413, 494, 383);
    BresenhamLinea(509, 413, 509, 383);
    BresenhamLinea(523, 413, 523, 383);
    BresenhamLinea(547, 414, 547, 383);
    BresenhamLinea(547, 383, 458, 383);

    //Contorno Derecha Centro
    Bresenham(456, 364, 552, 364);
    Bresenham(553, 364, 553, 323);
    Bresenham(553, 323, 456, 323);

    //Vidrios Derecha Centro
    BresenhamLinea(457, 354, 550, 354);
    BresenhamLinea(457, 353, 457, 325);
    BresenhamLinea(471, 353, 471, 325);

    BresenhamLinea(485, 353, 485, 325);
    BresenhamLinea(498, 353, 498, 325);
    BresenhamLinea(514, 353, 514, 325);
    BresenhamLinea(528, 353, 528, 325);
    BresenhamLinea(550, 353, 550, 325);

    BresenhamLinea(550, 325, 457, 325);
    circunferencia(538, 340, 5);

    //Contorno Derecha Abajo
    Bresenham(456, 306, 555, 306);
    Bresenham(555, 306, 555, 266);
    Bresenham(555, 266, 456, 266);

    //Vidrios Derecha Abajo
    BresenhamLinea(458, 295, 552, 295);
    BresenhamLinea(458, 295, 458, 268);
    BresenhamLinea(473, 295, 473, 268);
    BresenhamLinea(488, 295, 488, 268);
    BresenhamLinea(501, 295, 501, 268);
    BresenhamLinea(515, 295, 515, 268);
    BresenhamLinea(530, 295, 530, 268);

    BresenhamLinea(552, 295, 552, 268);
    BresenhamLinea(552, 268, 459, 268);

    //Vidrios Centrales(Lado Derecho)
    //Arriba
    BresenhamLinea(447, 414, 447, 363);
    BresenhamLinea(447, 363, 437, 363);
    BresenhamLinea(437, 363, 437, 414);
    BresenhamLinea(437, 414, 447, 414);

    BresenhamLinea(425, 414, 425, 363);
    BresenhamLinea(425, 363, 415, 363);
    BresenhamLinea(415, 363, 415, 414);
    BresenhamLinea(415, 414, 425, 414);

    BresenhamLinea(404, 414, 404, 363);
    BresenhamLinea(404, 363, 393, 363);
    BresenhamLinea(393, 363, 393, 414);
    BresenhamLinea(393, 414, 404, 414);

    //Vidrios Medios
    BresenhamLinea(447, 356, 447, 304);
    BresenhamLinea(447, 304, 437, 304);
    BresenhamLinea(437, 304, 437, 356);
    BresenhamLinea(437, 356, 447, 356);

    BresenhamLinea(425, 356, 425, 304);
    BresenhamLinea(425, 304, 415, 304);
    BresenhamLinea(415, 304, 415, 356);
    BresenhamLinea(415, 356, 425, 356);

    BresenhamLinea(404, 356, 404, 304);
    BresenhamLinea(404, 304, 393, 304);
    BresenhamLinea(393, 304, 393, 356);
    BresenhamLinea(393, 356, 404, 356);

    //Vidrios bajos
    BresenhamLinea(447, 296, 447, 263);
    BresenhamLinea(447, 263, 437, 263);
    BresenhamLinea(437, 263, 437, 296);
    BresenhamLinea(437, 296, 447, 296);

    BresenhamLinea(425, 296, 425, 263);
    BresenhamLinea(425, 263, 415, 263);
    BresenhamLinea(415, 263, 415, 296);
    BresenhamLinea(415, 296, 425, 296);

    BresenhamLinea(404, 296, 404, 263);
    BresenhamLinea(404, 263, 393, 263);
    BresenhamLinea(393, 263, 393, 296);
    BresenhamLinea(393, 296, 404, 296);

    //Vidrio Grande Arriba
    BresenhamLinea(384, 398, 384, 357);
    BresenhamLinea(384, 357, 314, 357);
    BresenhamLinea(314, 357, 314, 398);
    BresenhamLinea(314, 398, 384, 398);

    //Divisiones
    BresenhamLinea(368, 398, 368, 357);
    BresenhamLinea(355, 398, 355, 357);
    BresenhamLinea(341, 398, 341, 357);
    BresenhamLinea(329, 398, 329, 357);

    //Vidrio Grande Medio
    BresenhamLinea(384, 351, 384, 305);
    BresenhamLinea(384, 305, 314, 305);
    BresenhamLinea(314, 305, 314, 351);
    BresenhamLinea(314, 351, 384, 351);

    //Divisiones
    BresenhamLinea(368, 351, 368, 305);
    BresenhamLinea(355, 351, 355, 305);
    BresenhamLinea(341, 351, 341, 305);
    BresenhamLinea(329, 351, 329, 305);

    //Vidrio Grande Bajo
    BresenhamLinea(384, 295, 384, 251);
    BresenhamLinea(384, 251, 314, 251);
    BresenhamLinea(314, 251, 314, 295);
    BresenhamLinea(314, 295, 384, 295);

    //Divisiones
    BresenhamLinea(368, 295, 368, 251);
    BresenhamLinea(355, 295, 355, 251);
    BresenhamLinea(341, 295, 341, 251);
    BresenhamLinea(329, 295, 329, 251);

    //Vidrios Centrales(Lado Izquierdo)
    //Arriba
    BresenhamLinea(304, 414, 304, 363);
    BresenhamLinea(304, 363, 294, 363);
    BresenhamLinea(294, 363, 294, 414);
    BresenhamLinea(294, 414, 304, 414);

    BresenhamLinea(282, 414, 282, 363);
    BresenhamLinea(282, 363, 272, 363);
    BresenhamLinea(272, 363, 272, 414);
    BresenhamLinea(272, 414, 282, 414);

    BresenhamLinea(260, 414, 260, 363);
    BresenhamLinea(260, 363, 250, 363);
    BresenhamLinea(250, 363, 250, 414);
    BresenhamLinea(250, 414, 260, 414);

    //Vidrios Medios
    BresenhamLinea(304, 356, 304, 304);
    BresenhamLinea(304, 304, 294, 304);
    BresenhamLinea(294, 304, 294, 356);
    BresenhamLinea(294, 356, 304, 356);

    BresenhamLinea(282, 356, 282, 304);
    BresenhamLinea(282, 304, 272, 304);
    BresenhamLinea(272, 304, 272, 356);
    BresenhamLinea(272, 356, 282, 356);

    BresenhamLinea(260, 356, 260, 304);
    BresenhamLinea(260, 304, 250, 304);
    BresenhamLinea(250, 304, 250, 356);
    BresenhamLinea(250, 356, 260, 356);

    //Vidrios Bajos
    BresenhamLinea(304, 296, 304, 263);
    BresenhamLinea(304, 263, 294, 263);
    BresenhamLinea(294, 263, 294, 296);
    BresenhamLinea(294, 296, 304, 296);

    BresenhamLinea(282, 296, 282, 263);
    BresenhamLinea(282, 263, 272, 263);
    BresenhamLinea(272, 263, 272, 296);
    BresenhamLinea(272, 296, 282, 296);

    BresenhamLinea(260, 296, 260, 263);
    BresenhamLinea(260, 263, 250, 263);
    BresenhamLinea(250, 263, 250, 296);
    BresenhamLinea(250, 296, 260, 296);

    //Lado Izquierdo
    //Contorno Izquierda (opuesto)
    Bresenham(245, 250, 245, 450);
    Bresenham(94, 250, 94, 437);
    Bresenham(244, 437, 94, 437);

    //Contorno Izquierda Arriba (lado izquierdo opuesto)
    Bresenham(245, 416, 151, 416);
    Bresenham(151, 416, 151, 381);
    Bresenham(151, 381, 245, 381);

    //Vidrios Izquierda Arriba(lado izquierdo) 
    BresenhamLinea(154, 414, 244, 414);
    BresenhamLinea(244, 413, 244, 383);
    BresenhamLinea(232, 413, 232, 383);
    BresenhamLinea(218, 413, 218, 383);
    BresenhamLinea(207, 413, 207, 383);
    BresenhamLinea(192, 413, 192, 383);
    BresenhamLinea(178, 413, 178, 383);
    BresenhamLinea(154, 414, 154, 383);
    BresenhamLinea(154, 383, 243, 383);


    // Contorno Izquierda Centro (izquierdo)
    Bresenham(148, 364, 244, 364);
    Bresenham(147, 364, 147, 323);
    Bresenham(147, 323, 244, 323);


    //Vidrios Izquierda Centro(lado izquierdo opuesto)
    BresenhamLinea(151, 354, 244, 354);
    BresenhamLinea(244, 353, 244, 325);
    BresenhamLinea(230, 353, 230, 325);
    BresenhamLinea(216, 353, 216, 325);
    BresenhamLinea(203, 353, 203, 325);
    BresenhamLinea(187, 353, 187, 325);
    BresenhamLinea(173, 353, 173, 325);
    BresenhamLinea(151, 353, 151, 325);

    BresenhamLinea(152, 325, 244, 325);
    circunferencia(164, 340, 5);

    //Contorno Izquierda Abajo ( izquierda)
    Bresenham(144, 306, 245, 306);
    Bresenham(144, 306, 144, 266);
    Bresenham(144, 266, 245, 266);

    //Vidrios Izquieda Abajo(Lado Izquierdo Opuesto)
    BresenhamLinea(147, 295, 242, 295);
    BresenhamLinea(147, 295, 147, 268);


    BresenhamLinea(167, 295, 167, 268);
    BresenhamLinea(182, 295, 182, 268);
    BresenhamLinea(197, 295, 197, 268);
    BresenhamLinea(212, 295, 212, 268);
    BresenhamLinea(227, 295, 227, 268);
    BresenhamLinea(242, 295, 242, 268);
    BresenhamLinea(242, 268, 147, 268);

    Elipse(175, 75, 350, 180);

    //Rellenado de las fronteras
    //Edificio
    //Lado Derecho
    rellenoporFrontera(607, 251, rellenoAzul, borderColor);
    rellenoporFrontera(605, 251, rellenoCeleste, borderColor);

    //Ventanas

    //Lado Derecho
    //Abajo
    rellenoporFrontera(531, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(529, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(514, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(500, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(487, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(459, 269, rellenoAmarillo, borderColor2);

    //Medio
    rellenoporFrontera(458, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(472, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(486, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(499, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(515, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(549, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(539, 340, rellenoRandom, borderColor2);

    //Arriba
    rellenoporFrontera(468, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(470, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(482, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(484, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(495, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(510, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(524, 384, rellenoAmarillo, borderColor2);

    //Ventanas Centrales(Lado Derecho)
    //Abajo
    rellenoporFrontera(446, 264, rellenoAmarillo, borderColor2);
    rellenoporFrontera(424, 264, rellenoAmarillo, borderColor2);
    rellenoporFrontera(403, 264, rellenoAmarillo, borderColor2);

    //Medio
    rellenoporFrontera(446, 305, rellenoAmarillo, borderColor2);
    rellenoporFrontera(424, 305, rellenoAmarillo, borderColor2);
    rellenoporFrontera(403, 305, rellenoAmarillo, borderColor2);

    //Arriba
    rellenoporFrontera(446, 364, rellenoAmarillo, borderColor2);
    rellenoporFrontera(424, 364, rellenoAmarillo, borderColor2);
    rellenoporFrontera(403, 364, rellenoAmarillo, borderColor2);

    //Centro del Edificio
    //Ventana Grande 
    //Abajo(a reparar)
    rellenoporFrontera(369, 294, rellenoAmarillo, borderColor2);
    rellenoporFrontera(367, 294, rellenoAmarillo, borderColor2);
    rellenoporFrontera(354, 294, rellenoAmarillo, borderColor2);
    rellenoporFrontera(340, 294, rellenoAmarillo, borderColor2);
    rellenoporFrontera(328, 294, rellenoAmarillo, borderColor2);

    //Medio
    rellenoporFrontera(369, 306, rellenoAmarillo, borderColor2);
    rellenoporFrontera(367, 306, rellenoAmarillo, borderColor2);
    rellenoporFrontera(354, 306, rellenoAmarillo, borderColor2);
    rellenoporFrontera(340, 306, rellenoAmarillo, borderColor2);
    rellenoporFrontera(328, 306, rellenoAmarillo, borderColor2);

    //Arriba
    rellenoporFrontera(369, 358, rellenoAmarillo, borderColor2);
    rellenoporFrontera(367, 358, rellenoAmarillo, borderColor2);
    rellenoporFrontera(354, 358, rellenoAmarillo, borderColor2);
    rellenoporFrontera(340, 358, rellenoAmarillo, borderColor2);
    rellenoporFrontera(328, 358, rellenoAmarillo, borderColor2);

    //Lado Izquierdo
    //Ventanas Centrales(Lado Izquierdo) 
    //Abajo
    rellenoporFrontera(303, 264, rellenoAmarillo, borderColor2);
    rellenoporFrontera(281, 264, rellenoAmarillo, borderColor2);
    rellenoporFrontera(259, 264, rellenoAmarillo, borderColor2);

    //Medio
    rellenoporFrontera(303, 305, rellenoAmarillo, borderColor2);
    rellenoporFrontera(281, 305, rellenoAmarillo, borderColor2);
    rellenoporFrontera(259, 305, rellenoAmarillo, borderColor2);

    //Arriba
    rellenoporFrontera(303, 364, rellenoAmarillo, borderColor2);
    rellenoporFrontera(281, 364, rellenoAmarillo, borderColor2);
    rellenoporFrontera(259, 364, rellenoAmarillo, borderColor2);

    //Abajo
    rellenoporFrontera(166, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(181, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(196, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(211, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(226, 269, rellenoAmarillo, borderColor2);
    rellenoporFrontera(241, 269, rellenoAmarillo, borderColor2);

    //Centro
    rellenoporFrontera(243, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(229, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(215, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(202, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(186, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(172, 326, rellenoAmarillo, borderColor2);
    rellenoporFrontera(164, 340, rellenoRandom, borderColor2);

    //Arriba
    rellenoporFrontera(243, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(231, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(217, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(206, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(191, 384, rellenoAmarillo, borderColor2);
    rellenoporFrontera(177, 384, rellenoAmarillo, borderColor2);

    rellenoporFrontera(95, 251, rellenoCeleste, borderColor);
    rellenoporFrontera(93, 251, rellenoAzul, borderColor);

    //Elipse
    rellenoporFrontera(350, 175, rellenoVerde, borderColor2);

    glFlush();
    glutSwapBuffers();
}