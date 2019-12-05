#ifndef idc_H_
#define idc_H_

/*D7 D6 D5 D4 Backlight Enable RW RS  */
void assemblyDelay(void);
	/* Genera un pequeño delay durante el procesamiento de instrucciones */

void clear_flag_IIC(void);
	/* Limpia el bit acosiado con la bandera IICIF del modulo */

void init_IIC(void);
	/* Esta funcion inicializa el módulo de IIC */

void IIC_send_byte(unsigned char data);
	/* Mandamos un dato por el bus */

void IIC_start_condition(void);
	/* Generamos un startbit para comenzar la comunicación */

void IIC_stop_condition(void);
	/* Generamos un stopbit para cerrar la comunicación */

void start_communication(unsigned char salve);

#endif
