EJERCICIO DE PROGRAMACIÓN CON OPENSSL

Integrantes:

	- Jesús Martínez, 08-10704.
	- Vicente Santacoloma, 08-11044.

Descripción del proyecto:

	El ejercicio se basa en programar una versión segura y una insegura de una aplicación (cliente-servidor) que solicita datos privados por la red, y verificar el funcionamiento de cada una con un analizador de tráfico. Los programas se desarrollarán en C.

 	Cuando un cliente se conecta al servidor, éste retorna un mensaje solicitando "nombre de usuario", espera la respuesta, y luego envía "clave". El servidor debe tener un archivo con los usuarios y sus claves para poder verificarlo.
	
	Si el usuario existe en el sistema y la clave es correcta, el servidor responde con un mensaje "Usuario autorizado"; en caso contrario debe responder "Acceso denegado".

	Las claves de los usuarios deben guardarse utilizando algoritmos criptográficos con el fin de disminuir las posibilidades de violación de seguridad.

Contenido del paquete:

	- user_management.h: Header del archivo user_management.c
	- user_management.c: Funciones para la gestión de usuarios.
	- server.h: Header del archivo server.c
	- server.c: Funciones comunes de ambas versiones del servidor.
	- insecure_server.c: Versión insegura del servidor, utilizando la librería sockets con TCP.
	- secure_server.c: Versión segura del servidor, utilizando la librería OpenSSL con TLS.
	- client.h: Header del archivo client.c
	- client.c: Funciones comunes de ambas versiones del cliente.
	- insecure_client.c: Versión insegura del cliente, utilizando la librería sockets con TCP.
	- secure_client.c: Versión segura del cliente, utilizando la librería OpenSSL con TLS.
	- common.h: Header del archivo common.c
	- common.c: Funciones comunes para todos los archivos.
	- users_db: Base de datos de usuarios con sus respectivas contraseñas.
	- certificate.crt: Certificado auto-firmado del servidor.
	- privateKey.key: Clave privada del servidor.
	- Makefile: Makefile de la aplicación.

Instrucciones de instalación:

	Para instalar el software primero debemos descomprimir el archivo en formato .tar.gz mediante: $ tar -xvf ProyectoOpenSSL.tar.gz

	Para compilar el codigo en OS basado en linux, deberemos posicionarnos en la carpeta ProyectoOpenSSl y luego ejecutar el comando: $ make

	Luego se produciran cuatro ejecutables correspondientes a las versiones seguras e inseguras tanto del cliente como del servidor:
	"insecure_client", "secure_client", "insecure_server", "secure_server".

Instrucciones de ejecución:

	Los comandos para ejecutar cliente y servidor, son:

	Cliente:
	$> acceso-rem -s ip-servidor -p puerto-servidor (version insegura).
	$> acceso-rem-seg -s ip-servidor -p puerto-servidor (version con OpenSSL).
	donde ip-servidor y puerto servidor son el IP de la maquina y el puerto, respectivamente, donde esta conectado el servidor

	Servidor:
	$> serv_acceso -p puerto (versión insegura).
	$> serv-acceso-seg -p puerto (versión segura).
	Donde puerto es el número del puerto por el que atiende peticiones el servidor.

Estado actual:

	100% funcional.

Detalles adicionales:

	La elaboración del código se nutrió de la información presentada en los siguientes enlaces:
	- http://simplestcodings.blogspot.com/2010/08/secure-server-client-using-openssl-in-c.html
	- http://www.rtfm.com/openssl-examples/