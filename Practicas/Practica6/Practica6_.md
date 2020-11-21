Tabla de Contenidos
===================
  
  
- [Parte 1 – Métodos de acceso](#parte-1-métodos-de-acceso )
  - [Ejercicio 1 :star:](#ejercicio-1-star )
  - [Ejercicio 2 :star:](#ejercicio-2-star )
  - [Ejercicio 3 :star:](#ejercicio-3-star )
  - [Ejercicio 4](#ejercicio-4 )
- [Parte 2 – Interfaz de E/S](#parte-2-interfaz-de-es )
  - [Ejercicio 5 :star:](#ejercicio-5-star )
  - [Ejercicio 6](#ejercicio-6 )
  - [Ejercicio 7](#ejercicio-7 )
  - [Ejercicio 8 :star:](#ejercicio-8-star )
  - [Ejercicio 9 (No hice)](#ejercicio-9-no-hice )
  - [Ejercicio 10](#ejercicio-10 )
  - [Ejercicio 11 :star:](#ejercicio-11-star )
- [Parte 3 – API para escritura de drivers](#parte-3-api-para-escritura-de-drivers )
  
#  Parte 1 – Métodos de acceso
  
##  Ejercicio 1 :star:
  
- Esperar la finalización de una operación de E/S utilizando polling desperdicia muchos ciclos de reloj (busy waiting). Sin embargo, si el dispositivo está listo para la operación, esta técnica puede ser mucho más eficiente que una estrategia basada en interrupciones.
Describir una estrategia híbrida, que combine polling e interrupciones para acceder a dispositivos de E/S. Mostrar tres escenarios, uno donde polling sea el más conveniente, otro donde interrupciones sea el método de acceso más favorable y un tercero donde convenga utilizar la estrategia híbrida.
  
El caso de Polling es muy sencillo ya que se debe usar cuando se trata de dispositivos que tienen que mandar una serie de datos continuos sin parar, por ejemplo una camara web.
  
Para el caso de interrupciones es de esperar que sea utilizado por dispositivos los cuales no tengan una espera sincronica, por ejemplo el teclado, ya que la computadora no puede saber cuando se presionara nuevamente una tecla.
  
Un dispositivo como un mouse podria incorporar un mecanismo hibrido de polling e interrupciones, ya que mientras este en uso debe enviar la informacion del movimiento mediante polling, luego cuando deje de detectar movimiento entre en un estado de reposo donde deje de hacer polling para pasar a ser un dispositivo que se vuelva a activar por una interrupcion al momento de que se detecte un nuevo movimiento. 
  
##  Ejercicio 2 :star:
  
- Un sistema informático que incorpora DMA permite una implementación eficiente de la multiprogramación. Suponga que un proceso en promedio usa sólo el 23% de su tiempo la CPU y el resto está en entrada y salida (E/S) y suponiendo que toda operación de E/S se realiza por DMA. Sabiendoque se puede demostrar que <img src="https://latex.codecogs.com/png.latex?U_{CPU}(n)%20=%201-U_{E&#x2F;S}(1)^n"/> y que <img src="https://latex.codecogs.com/png.latex?U_{DMA}(n)%20=%201%20-%20U_{CPU}(1)^n"/>, donde <img src="https://latex.codecogs.com/png.latex?n"/> es la cantidad de procesos, estime qué utilización del procesador y del canal de DMA se logra, si se tiene un grado de multiprogramación de 6 procesos.
  
Definamos quienes son alguno de estos numeros:
- <img src="https://latex.codecogs.com/png.latex?U_{CPU}(1)%20=%200.23"/>
- <img src="https://latex.codecogs.com/png.latex?U_{E&#x2F;S}(1)%20=%200.77"/>
  
Por lo tanto:
- <img src="https://latex.codecogs.com/png.latex?U_{CPU}(6)%20=%201%20-%20(0.77)^6%20=%200,79157762"/>
- <img src="https://latex.codecogs.com/png.latex?U_{E&#x2F;S}(6)%20=%201%20-%20(0.23)^6%20=%200,999851964"/>
  
##  Ejercicio 3 :star:
  
1. ¿Se puede implementar *spooling* sin dispositivos virtuales?
2. ¿Qué métricas mejora o empeora el uso de spooling: latencia,throughput, tiempo de ejecución, liberación de recursos?
3. ¿Por qué no se suele hacer spooling de placas de red y sí de impresoras?
  
1- Suponiendo que el dispositivo virtual es el intermediario entre el usuario y el driver, el spooling no seria posible sin este, ya que el concepto de enviar las cosas sin bloquearse no es un comportamiento nativo al hacer un `write(...)`, si no que el spooling debe ser gestionado por un dispositivo virtual que logre el cometido esperado.
  
2- Metricas:
  - Liberacion de Recursos: El spooling lo mejora ya que no va a generarse *busy waiting* al hacer uso de un dispositivo con spooling.
  - Tiempo de Ejecucion: Tambien mejorara por la misma razon que en el punto anterior, 
  - Throughput: (maximizar el numero de procesos terminados por unidad de tiempo) Esto tambien se ve beneficiado ya que la falta de waiting hace que terminen mas rapido los procesos (a pesar de que puede haber cosas encoladas sin terminar cuando el proceso ya lo haya hecho).
  - Latencia: este probablemente puede no modificarse o empeorar ya que el tiempo del pedido encolado puede terminar en el mismo tiempo que si fuese por interrupcion o polling. Y ademas al haber spooling pueden haber muchos procesos encolando lo cual va hacer que los resultados de los demas procesos tarden mas en terminar.
  
3. Es un tema de que son dos ambitos completamente distintos ya que en el caso de la placa de red imagino que se pasan las cosas en paquetes de forma serial, donde al otro lado del cable debe responder de alguna forma para dar el visto bueno al que este enviando datos. Por lo que el concepto de spooling no podria ser aplicado de forma correcta.
  
##  Ejercicio 4 
  
Se tiene un sistema de impresión que utiliza spooling sobre una impresora virtual y DMA sobre la impresora real. Responder y justificar:
a) ¿De cuál de estas técnicas es importante que esté al tanto el usuario final?
b) ¿El driver de impresión tiene alguna noción de spooling?
  
a) El usuario deberia estar solo al tanto de lo que sucede con el dispositivo virtual, es decir solo sabe que envia las cosas a imprimir y no deberia importarle como lo hace internamente mas alla del sistema de cola que proporciona la impresora.
  
b) El driver posiblemente no tiene nocion del spooling ya que es el dispositivo virtual el que permite que el encolamiento suceda, el driver lo unico que tiene que hacer es darle las instrucciones a la impresora de que hacer ante un nuevo documento y luego avisar al dispositivo virtual que ya acabo para pasar al siguiente documento.
  
---
  
#  Parte 2 – Interfaz de E/S
  
Para todos los ejercicios de esta sección que requieran escribir código deberá utilizarse la API descripta en la parte final de esta práctica. [Link](#parte-3-api-para-escritura-de-drivers )
  
##  Ejercicio 5 :star:
  
- ¿Cuáles de las siguientes opciones describen el concepto de driver? Seleccione las correctas y justifique.
    1. Es una pieza de software.
    2. Es una pieza de hardware.
    3. Es parte del SO.
    4. Dado que el usuario puede cambiarlo, es una aplicación de usuario.
    5. Es un gestor de interrupciones.
    6. Tiene conocimiento del dispositivo que controla pero no del SO en el que corre.
    7. Tiene conocimiento del SO en el que corre y del tipo de dispositivo que controla, pero no de las particularidades del modelo específico.
  
1. Verdadero: Ya que es un algoritmo como cualquier otro.
2. Falso: IDEM
3. Verdadero: Es un modulo del kerner que funciona como intermediario entre el SO y el dispositivo.
4. Falso: No es una aplicacion de usuario ya que trabaja a nivel root y los usuarios no pueden cambiarlo.
5. Falso: Puede funcionar en base a interrupciones pero no es un gestor de estas.
6. Falso: Un driver de windows no funciona en Linux por ejemplo dado que tambien tiene que saber a que SO le esta hablando.
7. 
    - Verdadero: (si se referia al modelo de computadora) ya que es independiente de la computadora en la que este instalado (salvo excepciones)
    - Falso: (si se refiere al modelo del dispositivo) ya que cada modelo de dispositivo puede ser tan distinto como quiera, por lo que el mismo driver puede no funcionar en distintos modelos de un dispositivo.
  
##  Ejercicio 6
  
- Un cronómetro posee 2 registros de E/S:
  - `CHRONO_CURRENT_TIME` que permite leer el tiempo medido,
  - `CHRONO_CTRL` que permite ordenar al dispositivo que reinicie el contador.
- El cronómetro reinicia su contador escribiendo la constante `CHRONO_RESET` en el registro de control.
- Escribir un driver para manejar este cronómetro. Este driver debe devolver el tiempo actual cuando invoca la operación `read()`. Si el usuario invoca la operación `write()`, el cronómetro debe reiniciarse.
  
```c
int driver_init(){}
int driver_open(){}
int driver_close(){}
int driver_read(int *data){
    if (*data = IN(CHRONO_CURRENT_TIME)){
       return IO_OK; 
    };
    return IO_ERROR;
}
int driver_write(int *data){
    if (OUT(CHRONO_CTRL, CHRONO_RESET)){
       return IO_OK; 
    };
    return IO_ERROR;
}
int driver_remove(){}
```
  
##  Ejercicio 7
  
- Una tecla posee un único registro de E/S :`BTN_STATUS`. Solo el bit menos significativo y el segundo bit menos significativo son de interés:
    - `BTN_STATUS_0`: vale 0 si la tecla no fue pulsada, 1 si fue pulsada.
    - `BTN_STATUS_1`: escribir 0 en este bit para limpiar la memoria de la tecla.
- Escribir un driver para manejar este dispositivo de E/S. El driver debe retornar la constante `BTN_PRESSED` cuando se presiona la tecla. Usar *busy waiting*.
  
```c
int driver_init(){}
int driver_open(){}
int driver_close(){}
int driver_read(int *data){
    int aux = IN(BTN_STATUS);
    do{
        aux_0 = (aux << 8*4-1) >> 8*4;
    }while (!(aux_0 == 0));
    OUT(BTN_STATUS, BTN_STATUS || 0x2)
    return BTN_PRESSED;
}
int driver_write(int *data){}
int driver_remove(){}
```
  
##  Ejercicio 8 :star:
  
- Reescribir el driver del ejercicio anterior para que utilice interrupciones en lugar de *busy waiting*. Para ello, aprovechar que la tecla ha sido conectada a la línea de interrupción número 7.
- Para indicar al dispositivo que debe efectuar una nueva interrupción al detectar una nueva pulsación de la tecla, debe guardar la constante `BTN_INT` en el registro de la tecla.
Ayuda: usar *semáforos*.
  
```c
#define IRQ_7 7
  
void *IRQ_handler (){
    // Indico por STATUS que ya fue interrumpido
    OUT(BTN_STATUS, BTN_INT)
    //Escribo en el registro que la tecla fue presionada
    OUT(BTN_STATUS, BTN_STATUS || 0x2)
    //Libero el mutex
    mutex.unlock();
}
  
int driver_init(){
    // Inicializo el semaforo
    std::semaphore mutex;
}
int driver_open(){
    // Hago el pedido del puerto 7 de IRQ
    if (request_irq(IRQ_7, IRQ_handler)==IRQ_ERROR){
        return -1;
    }
    return 0;
}
int driver_close(){
    // Cierro el IRQ 7 
    free_irq(IRQ_7);
    return 0;
}
int driver_read(int *data){
    // Debo esperar a que la interrupcion se lance
    // Agrego un mutex que solo se pasara si el handler fue activado
    mutex.lock();
    return BTN_PRESSED;
}
int driver_write(int *data){}
int driver_remove(){}
```
  
##  Ejercicio 9 (No hice)
  
- Indicar las acciones que debe tomar el administrador de E/S:
    1. cuando se efectúa un `open`.
    2. cuando se efectúa un `write`.
  
##  Ejercicio 10
  
- ¿Cuál debería ser el nivel de acceso para las syscalls `IN` y `OUT`? ¿Por qué?
  
Ya que mediante estas funciones se obtiene/modifica valores de un registro vinculado a un dispositivo, el acceso a estos registros no deberia estar disponible a un usuario, por lo que entonces estas syscalls deben tener nivel de kernel para realizarse.
  
  
##  Ejercicio 11 :star:
  
Se desea implementar el *driver* de una controladora de una vieja unidad de discos ópticos que requiere controlar manualmente el motor de la misma. Esta controladora posee 3 registros de lectura y 3 de escritura. Los registros de escritura son:
  - `DOR_IO`: enciende (escribiendo 1) o apaga (escribiendo 0) el motor de la unidad.
  - `ARM`: número de pista a seleccionar.
  - `SEEK_SECTOR`: número de sector a seleccionar dentro de la pista.
  
Los registros de lectura son:
  - `DOR_STATUS`: contiene el valor 0 si el motor está apagado (o en proceso de apagarse), 1 si está encendido. Un valor 1 en este registro no garantiza que la velocidad rotacional del motor sea la suficiente como para realizar exitosamente una operación en el disco.
  - `ARM_STATUS`: contiene el valor 0 si el brazo se está moviendo, 1 si se ubica en la pista indicada en el registro `ARM`.
  - `DATA_READY`: contiene el valor 1 cuando el dato ya fue enviado.
  
Además, se cuenta con las siguientes funciones auxiliares (ya implementadas):
  - `int cantidad_sectores_por_pista()`: Devuelve la cantidad de sectores por cada pista del disco. El sector 0 es el primer sector de la pista.
  - `void escribir_datos(void *src)`: Escribe los datos apuntados por `src` en el último sector seleccionado.
  - `void sleep(int ms)`: Espera durante `ms` milisegundos.
  
Antes de escribir un sector, el *driver* debe asegurarse que el motor se encuentre encendido. Si no lo está, debe encenderlo, y para garantizar que la velocidad rotacional sea suficiente, debe esperar al menos 50 ms antes de realizar cualquier operación. A su vez, para conservar energía, una vez que finalice una operación en el disco, el motor debe ser apagado. El proceso de apagado demora como máximo 200 ms, tiempo antes del cual no es posible comenzar nuevas operaciones. 
  1. Implementar la función `write(int sector,void *data)` del *driver*, que escriba los datos apuntados por data en el sector en formato LBA indicado por `sector`. Para esta primera implementación, no usar interrupciones.
  2. Modificar la función del inciso anterior utilizando interrupciones. La controladora del disco realiza una interrupción en el `IRQ 6` cada vez que los registros `ARM_STATUS` o `DATA_READY` toman el valor 1. Además, el sistema ofrece un *timer* que realiza una interrupción en el `IRQ 7` una vez cada 50ms. Para este inciso, no se puede utilizar la función `sleep`.
  
```c++
void write(int sector,void *data){
    // Verifico que el motor este encendido
    if (IN(DOR_STATUS) == 0){
        OUT(DOR_STATUS, 1);
    }
    // Espero 50 ms para estabilizar
    sleep(50);
  
    // Comienzo con el proceso de escritura
    // Calculo a que pista debo moverme
    int sects_por_pista = cantidad_sectores_por_pista();
    int pista = (int)floor(sector / sects_por_pista);
    // Calculo el sector relativo a la pista
    int sector_pista = sector % sects_por_pista; 
    // Me muevo a la pista
    OUT(ARM, pista);
    // Espero a que el brazo llegue a la pista
    while(!(IN(ARM_STATUS)==1)){}
    // Selecciono el sector de la pista correspondiente
    OUT(SEEK_SECTOR, sector_pista);
    sleep(50);
    //Escribo el dato en el sector seleccionado
    escribir_datos(data);
    // Espero a que se termine de grabar
    while(!(IN(DATA_READY)==1)){}
  
    // Apago motor ya que termine
    OUT(DOR_STATUS, 0);
    // Para apagarse correctamente debo esperar 200ms
    sleep(200);
}
```
  
```c
void *handler_ready (){
    // Doy el paso a quien lo necesite
    ready.notify();
}
  
void *handler_chrono (){
    // Esta interrupcion ocurre cada 50ms
    // Por lo que solo quiero usarla cuando sea necesario
    if (chrono_enabled){
        chrono.notify();
    }
}
int driver_init(){
    // Pido los IRQ correspondientes (Parte 2)
    if (request_irq(6,handler_ready)==IRQ_ERROR){
        return -1;
    }
    if (request_irq(7,handler_chrono)==IRQ_ERROR){
        return -1;
    }
  
    // Declaro dos semaforos para usar con las IRQs
    Semaphore ready;
    Semaphore chrono;
    std::atomic<bool> chrono_enabled;
  
}
int driver_close(){
    free_irq(6);
    free_irq(7);
}
void write_INTs(int sector,void *data){
    // Verifico que el motor este encendido
    if (IN(DOR_STATUS) == 0){
        OUT(DOR_STATUS, 1);
    }
    chrono_enabled = true;
    // Espero 50 ms para estabilizar (por IRQ)
    chrono.wait();
    // Es buena idea esperar uno mas porque
    // si no en el mejor caso espere solo 1ms
    chrono.wait();
    chrono_enabled = false;
  
    // Comienzo con el proceso de escritura
    // Calculo a que pista debo moverme
    int sects_por_pista = cantidad_sectores_por_pista();
    int pista = (int)floor(sector / sects_por_pista);
    // Calculo el sector relativo a la pista
    int sector_pista = sector % sects_por_pista; 
    // Me muevo a la pista
    OUT(ARM, pista);
    // Espero a que el brazo llegue a la pista
    ready.wait();
    // Selecciono el sector de la pista correspondiente
    OUT(SEEK_SECTOR, sector_pista);
  
    chrono_enabled = true;
    chrono.wait();
    chrono.wait();
    chrono_enabled = false;
  
    //Escribo el dato en el sector seleccionado
    escribir_datos(data);
    // Espero a que se termine de grabar
    ready.wait();
  
    // Apago motor ya que termine
    OUT(DOR_STATUS, 0);
    // Para apagarse correctamente debo esperar 200ms
    chrono_enabled = true;
    chrono.wait();
    chrono.wait();
    chrono.wait();
    chrono.wait();
    chrono.wait();
    chrono_enabled = false;
}
```
  
  
  
#  Parte 3 – API para escritura de drivers
  
Un SO provee la siguiente API para operar con un dispositivo de E/S. Todas las operaciones retornan la constante `IO_OK` si fueron exitosas o la constante `IO_ERROR` si ocurrió algún error.
  
|Función | Descripción |
|---|---|
| `int open(int device_id)`  | Abre el dispositivo.   |
| `int close(int device_id)` | Cierra el dispositivo. |
| `int read(int device_id, int *data)` | Lee el dispositivo `device_id`.|
| `int write(int device_id, int *data)` | Escribe el valor en el dispositivo `device_id`.|
  
Para ser cargado como un driver válido por el sistema operativo, el driver debe implementar los siguientes procedimientos:
  
|Función|Invocación|
|---|---|
|`int driver_init()`|Durante la carga del SO.
|`int driver_open()`|Al solicitarse un open.|
|`int driver_close()`|Al solicitarse un close.|
|`int driver_read(int *data)`|Al solicitarse un read.|
|`int driver_write(int *data)`|Al solicitarse un write.
|`int driver_remove()`|Durante la descarga del SO.|
  
Para la programación de un driver, se dispone de las siguientes syscalls:
|Syscalls|Descripción|
|------------------|---|
|`void OUT(int IO_address, int data)`| Escribe data en el registro de E/S.
|`int IN(int IO_address)`|Devuelve el valor almacenado en el registro de E/S.|
|`int request_irq(int irq, void *handler)` | Permite asociar el procedimiento handler a la interrupción IRQ. Devuelve `IRQ_ERROR` si ya está asociada a otro handler.
|`int free_irq(int irq)`|Libera la interrupción IRQ del procedimiento asociado.|
  