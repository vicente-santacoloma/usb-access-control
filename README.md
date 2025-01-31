# usb-access-control
Universidad Simón Bolívar - CI6352 - Cryptography and Data Security - Access Control

## Descripción

El ejercicio se basa en programar una versión segura y una insegura de una aplicación cliente-servidor que solicita datos privados por la red, y verificar el funcionamiento de cada una con un analizador de tráfico. Los programas se desarrollarán en C.

Cuando un cliente se conecta al servidor, éste retorna un mensaje solicitando 'nombre de usuario', espera la respuesta, y luego envía 'clave'. El servidor debe tener un archivo con los usuarios y sus claves para poder verificarlo.
	
Si el usuario existe en el sistema y la clave es correcta, el servidor responde con un mensaje 'Usuario autorizado'; en caso contrario debe responder 'Acceso denegado'.

Las claves de los usuarios deben guardarse utilizando algoritmos criptográficos con el fin de disminuir las posibilidades de violación de seguridad.

## Estructura

| Archivo           | Descripción                                                           |
|-------------------|-----------------------------------------------------------------------|
| add_users.c       | Ejecutable para añadir nuevos usuarios a la base de datos             |
| certificate.crt   | Certificado auto-firmado del servidor                                 |
| client.h          | Header del archivo client.c                                           |
| client.c          | Funciones comunes de ambas versiones del cliente                      |
| common.h          | Header del archivo common.c                                           |
| common.c          | Funciones comunes para todos los archivos                             |
| insecure_client.c | Versión insegura del cliente, utilizando la librería sockets con TCP  |
| insecure_server.c | Versión insegura del servidor, utilizando la librería sockets con TCP |
| Makefile          | Makefile de la aplicación                                             |
| privateKey.key    | Clave privada del servidor                                            |
| secure_client.c   | Versión segura del cliente, utilizando la librería OpenSSL con TLS    |
| secure_server.c   | Versión segura del servidor, utilizando la librería OpenSSL con TLS   |
| server.h          | Header del archivo server.c                                           |
| server.c          | Funciones comunes de ambas versiones del servidor                     |
| users_db          | Base de datos de usuarios con sus respectivas contraseñas             |
| user_management.h | Header del archivo user_management.c                                  |
| user_management.c | Funciones para la gestión de usuarios                                 |

## Instrucciones de Instalación

Para instalar el software primero debemos descomprimir el archivo en formato `.tar.gz` mediante:

```bash
tar -xvf ProyectoOpenSSL.tar.gz
```

Para compilar el código en OS basado en linux, deberemos posicionarnos en la carpeta ProyectoOpenSSl y luego ejecutar el comando:

```bash
make
```

Luego se producirán cuatro ejecutables correspondientes a las versiones seguras e inseguras tanto del cliente como del servidor:

* `insecure_client`
* `secure_client`
* `insecure_server`
* `secure_server`

El comando utilizado para generar el certificado autofirmado es:

```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout privateKey.key -out certificate.crt
```

Donde:
* **-x509:** Tipo de certificado solicitado.
* **-nodes:** La clave privada generada para este certificado no se guardara cifrada.
* **-days:** Número de días de validez del certificado.
* **-newkey:** Algoritmo de clave pública utilizado, así como la longitud de la clave generada.
* **-keyout:** Especifica el nombre del archivo donde se guardara la clave.
* **-out:** Especifica el nombre del archivo donde se guardara el certificado.

## Instrucciones de Ejecución

Los comandos para ejecutar cliente y servidor, son:

#### Cliente

##### Versión Segura con OpenSSL

```bash
acceso-rem-seg -s [ip-servidor] -p [puerto-servidor]
```

##### Versión Insegura

```bash
acceso-rem -s [ip-servidor] -p [puerto-servidor]
```

Donde `ip-servidor` es el IP de la máquina y `puerto-servidor` el puerto donde está conectacdo el servidor.

#### Servidor

##### Versión Segura con OpenSSL

```bash
serv-acceso-seg -p [puerto]
```

##### Versión Insegura

```bash
serv_acceso -p [puerto]
```

Donde `puerto` es el número del puerto por el que atiende peticiones el servidor.

## Detalles Adicionales:

* La elaboración del código se nutrió de la información presentada en los siguientes enlaces:
  * [http://simplestcodings.blogspot.com/2010/08/secure-server-client-using-openssl-in-c.html](http://simplestcodings.blogspot.com/2010/08/secure-server-client-using-openssl-in-c.html)
  * [http://www.rtfm.com/openssl-examples](http://www.rtfm.com/openssl-examples)
* Si la opción está habilitada, en la base de datos de los usuarios, se almacena el resumen criptografico de sus respectivas contraseñas en vez de lo contraseña per se. Así, cuando se desea autenticar a un usuario, se calcula el resumen criptográfico de la contraseña recien introducida con aquel almacenado en la base de datos. Si coincide, entonces, se concede acceso. Si no, se deniega el acceso. La función utilizada para calcular tales resúmenes es SHA512.
