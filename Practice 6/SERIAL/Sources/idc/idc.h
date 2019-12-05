#ifndef idc_H_
#define idc_H_

void clear_flag_IIC(void);
	// Limpia el bit acosiado con la bandera IICIF del modulo

void init_IIC(void);
	// Esta funcion inicializa el módulo de IIC

void IIC_send_byte(unsigned char data);
	// Mandamos un dato por el bus 

void IIC_start_condition(void);
	// Generamos un startbit para comenzar la comunicación 

void IIC_stop_condition(void);
	// Generamos un stopbit para cerrar la comunicación

// Definimos la estructura I2C_t con sus variables de inicializacion
typedef struct{
	unsigned char baudrate;
	unsigned char control;
	unsigned char ports;
} I2C_t;

void init_IIC_STRUCT(I2C_t p); //funcion de inicializacio de IIC

#endif
