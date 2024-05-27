/* 
 * File:   parcial_relleno.h
 * Author: jose
 *
 * Created on 26 de mayo de 2024, 20:27
 */

#ifndef PARCIAL_RELLENO_H
#define PARCIAL_RELLENO_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
/**
* Se encarga de inicializar (si es necesario) su invocacion
* esta llamada se realizara una sola vez al inicio de la ejecucion
*/
void inicializar_multiples(void);
/**
* Dibuja su entrega de la mierva usando unicamente lineas rectas mediante la invocacion del callback
de glut tal y como se mostro en clase.
*/
void dibujar_multiples();

/**
* retorne su numero de carnet en la invocacion, en base a esto se asignara su nota de forma automatica
*/
const char* get_carnet(void);


#endif /* PARCIAL_RELLENO_H */

