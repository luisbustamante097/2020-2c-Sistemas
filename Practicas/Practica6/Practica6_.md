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
- [Parte 3 – API para escritura de drivers](#parte-3-api-para-escritura-de-drivers )
  
#  Parte 1 – Métodos de acceso
  
##  Ejercicio 1 :star:
  
- Esperar la finalización de una operación de E/S utilizando polling desperdicia muchos ciclos de reloj (busy waiting). Sin embargo, si el dispositivo está listo para la operación, esta técnica puede ser mucho más eficiente que una estrategia basada en interrupciones.
Describir una estrategia híbrida, que combine polling e interrupciones para acceder a dispositivos de E/S. Mostrar tres escenarios, uno donde polling sea el más conveniente, otro donde interrupciones sea el método de acceso más favorable y un tercero donde convenga utilizar la estrategia híbrida.
  
Un dispositivo como un mouse puede incorporar un mecanismo hibrido de polling e interrupciones, ya que mientras este en uso debe enviar la informacion del movimiento mediante polling, luego cuando deje de detectar movimiento entre en un estado de reposo donde deje de hacer polling para pasar a ser un dispositivo que se vuelva a activar por una interrupcion al momento de que se detecte un nuevo movimiento. 
  
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
3. Falso: Es el intermediario entre el SO y el dispositivo.
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
|`int driver_close()`|Al solicitarse unclose.|
|`int driver_read(int *data)`|Al solicitarse un read.|
|`int driver_write(int *data)`|Al solicitarse un write.
|`int driver_remove()`|Durante la descarga del SO.|
  
Para la programación de un driver, se dispone de las siguientes syscalls:
|Syscalls|Descripción|
|------------------|---|
|`void OUT(int IO_address, int data)`| Escribe data en el registro de E/S.
|`int IN(int IO_address)`|Devuelve el valor almacenado en el registro de E/S.|
|`int request_irq(int irq, void *handler)`| Permite asociar el procedimiento handler a la interrupción IRQ. Devuelve `IRQ_ERROR` si ya está asociada a otro handler.
|`int free_irq(int irq)`|Libera la interrupción IRQ del procedimiento asociado.|
  