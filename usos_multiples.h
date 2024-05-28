#ifndef USOS_MULTIPLES_H
#define USOS_MULTIPLES_H

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
void inicializar_usos_multiples(void);
/**
* Dibuja su entrega mediante la invocacion del callback
de glut tal y como se mostro en clase.
*/
void dibujar_usos_multiples();



#endif /* USOS_MULTIPLES_H */