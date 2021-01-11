En este codigo se presentan 3 vulnerabilidades:
- Vulnerabilidad del `setuid`: Esta no es una vulnerabilidad como tal, pero si puede ser usada a favor del atacante ya que como el flag *setuid* esta activado, el binario será ejecutado con permisos de *root* (ya que el *owner* es el *root*), con lo cual pueden ser explotadas de mejor manera las dos siguiente vulnerabilidades.
- Vulnerabilidad al usar `gets`: Esta función del lenguaje C es muy insegura ya que no le pone un limite al valor que ingresa por `stdin`, por lo que si un usuario malicioso superara el valor del buffer establecido (80 bytes) de la variable `nombre`, puede ocasionar un **buffer overflow**. Esto se producente intruciendo un string bien calculado que pueda sobrescribir la *dirección de retorno* del stack, para saltar a un codigo maligno. Por ejemplo, como el binario se esta ejecutando como *root* el codigo al que salte puede ser un `system("/bin/bash")`, con lo cual se obtendra una terminal con permisos de *root*. Esto ultimo puede ser realizado agregando este comando (escrito en hexadecimal) en el stack, antes de muchos comandos `NOP` (para saltarnos problemas con la alineación del stack), y sobrescribir la direccion de retorno tal que apunte a alguno de estos `NOP`, ya que el comando `NOP` de *assembler* hace que el `IP` del CPU apunte a la siguiente instrucción, y esto se repetira sucesivamente hasta llegar al codigo malicioso.
- Vulnerabilidad de `echo`: Esta es otra vulnerabilidad poco relacionada con la anterior, ya que se basa en el hecho de que el comando `echo` se ejecutara con lo que `/usr/bin/env/` le indique, por lo que si nosotromos modificamos el `PATH` de ejecucion, podemos hacerlo apuntar a un `echo` falso. Por ejemplo la forma de explotarlo seria:
    - Crear un archivo en `/tmp`, con el nombre `echo` que contenga el siguiente codigo:
        ```sh
        #!/bin/bash
        /bin/bash
        ```
    - Darle los permisos necesarios para poder ejecutarse:
        ```sh
        chmod 755 /tmp/echo
        ```
    - Agregar `/tmp` al comienzo del `PATH` para poder ejecutar el `echo` falso:
        ```sh
        export PATH=/tmp:$PATH
        ```
    - Y por ultimo ejecutar el binario `inicioSistema` resultara en obtener una terminal del usuario *root*.

Ambas vulnerabilidades pueden combinarse en el sentido de intentar una y luego la otra, ya que por un lado los pasos a seguir para explotarlas son muy distintos, pero tal vez la segunda resulte mejor ya que si se protegio el stack con canarios (o con la tecnica de *stack randomization*), la primer vulnerabilidad no podra ser explotada.
Un *stack canary* es un valor al azar elegido al momento de comenzar el programa, el cual es colocado en el stack y revisado antes de usar la *dirección de retorno* ya que si este es modificado (como en el proceso que describi al describir la vulnerabilidad del `gets`), se puede detectar un *buffer overflow* y cortar la ejecución del programa antes de que pueda ser ejecutado el codigo intruso. 