# Ejercicio 3
Las aplicaciones se comunican con el nucleo a traves de llamadas al sistema.
Una aplicación generalmente llama a funciones en una biblioteca (por ejemplo, biblioteca C) que se basan en
la interfaz de llamada del sistema para indicar al núcleo que realice tareas en nombre de la aplicación.

Las diferencias entre las llamadas a la biblioteca y al sistema son:
Llamadas a la biblioteca
- Las funciones que forman parte de la biblioteca estándar de C.
- Ejecutar en modo de usuario.
- No tiene mucho privilegio.
- Ejecución más rápida ya que no implica cambio de contexto.

Llamadas al sistema
- Las funciones que forman parte de Kernel.
- Ejecutar en modo kernel.
- Se ejecuta en el modo de supervisión, por lo que tiene todos los privilegios.
- Las llamadas al sistema son lentas ya que hay un cambio de contexto involucrado.