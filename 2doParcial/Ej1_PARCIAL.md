# Ejercicio 1

A.
Es incorrecta porque nunca se hizo uso de la función `cdev_init(&mi_modulo_device, &fops);` la cual (segun la documentación de linux) es la que inicializa la variable `mi_modulo_device` de tipo `cdev` recordandno `fops` y la deja lista para ser añadida al sistema por la funcion `cdev_add`.

B. IDEM, ya que falta la funcion `cdev_init(&modulo_cdev, &fops);`.

C.
Es incorrecto porque en la primer y segunda linea del driver se esta usando la variable `data` pasada por parametro sin antes ser pasada por la función `copy_from_user` a un buffer. Esto esta mal desde el punto de vista de un driver porque estas funciones verifican que no se esten pasando puntero de memoria que no sean del usuario que esta usando el driver.

