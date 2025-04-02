#include "client.h"
int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	char* keyAsociada;
	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	//log_info(logger,"soy un log");
	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config
	config = iniciar_config();
	if(config_has_property(config,"CLAVE"))
	{

			keyAsociada = config_get_string_value(config,"CLAVE");
			log_info(logger,keyAsociada);
	}
	log_info(logger,"No existe el parametro CLAVE");

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);
	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	log_info(logger,ip);
	log_info(logger,puerto);

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

    enviar_mensaje(keyAsociada, conexion);
	// Armamos y enviamos el paquete

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("/home/utnso/ProyectosUTN/tp0/client/logs/logs.log","Proceso",true,LOG_LEVEL_TRACE);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("cliente.config");


	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	int diferenciaCadenas; 

	do
	{
		leido = readline("> ");
		diferenciaCadenas = strcmp(leido,"");
		log_info(logger,leido);
		free(leido);

	}
	while(diferenciaCadenas);
	
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	t_paquete * paqueteAenviar;
	paqueteAenviar =  crear_paquete();
	char* leido;
	int diferenciaCadenas; 

	do
	{
		leido = readline("> ");
		diferenciaCadenas = strcmp(leido,"");
		agregar_a_paquete(paqueteAenviar, leido, strlen(leido)+1);
		free(leido);
	}
	while(diferenciaCadenas);
	
	enviar_paquete(paqueteAenviar, conexion);
	eliminar_paquete(paqueteAenviar);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{

	log_destroy(logger);
	config_destroy(config);
	close(conexion);

	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
