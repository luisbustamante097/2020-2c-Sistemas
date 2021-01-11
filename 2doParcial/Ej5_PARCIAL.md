# Ejercicio 5
Proponga una variante del algoritmo de selección de líder en anillo para que pueda seleccionar tres posiciones de liderazgo: primer, segundo y tercer lugar. Suponga que no existen problemas bizantinos, ni fallas en el sistema. También debe considerar qué hacer en casos de empate. Debe proponer un algoritmo escrito en pseudocódigo o a través de un conjunto secuencial y finito de reglas. Asuma también que el anillo no está conformado por lo que debe indicar cómo se constituye.

Queremos definir un conjunto secuencial y finito de reglas para la eleccion de los 3 lideres.
- Si todos los nodos estan numerados del 1 a N quiero formar un anillo tal que el nodo i solo este conectado con el nodo i-1 y el nodo i+1, salvo el nodo N que estara conectado con el N-1 y el 1.

- Supongo que la eleccion del los lideres estara dada por quienes tengan el mayor valor de un *stat* relevante (por ejemplo: almacenamiento libre), y en caso de empate se desempatara con otro stat por el estilo (por ejemplo: mayor memoria RAM libre o mayor tiempo despierto).

- La idea principal del algoritmo seria replicar el algoritmo original de *token passing*, en el cual se pasa un token (en este caso sera un struct con todos los stats relevantes para resolver posibles empates y el ID suyo), donde comienza un nodo cualquiera a pasar su token y el de al lado debera ver si tiene stats mayores. Si esto es cierto debera reemplazar el token pasado con sus propio token, si no debera pasar al nodo contiguo el mismo token pasado anteriormente.

- Esta idea se repetira hasta que el que haya comenzado reciba de vuelta un token, el cual tendra el ID del nodo con mayores stats. Luego el mismo nodo que acaba de recibir esto empezara un nuevo pase a todo el anillo informando quien es el nodo lider.

- Hasta aca el comportamiento es el mismo que el modelo clasico. La diferencia sera que luego de que todos los nodos sepan quien es el lider, el nodo iniciante de todo debera pasar nuevamente su token con los stats suyos al nodo que tenga a lado (como en la primer vuelta).

- En este caso el nodo que reciba el token debera primero preguntarse si es el lider, y si no lo es recien debera verificar si sus stats son mayores. Esto permite que el lider del anillo no pueda volver a participar de la selección.

- Cuando el primer nodo reciba nuevamente un token vera de quien es el ID con mayores stats (sabiendo que no participo el lider actual), por lo que proseguira a comunicar a todos los nodos mediante un pase del mismo estilo quien es el segundo lider.

- Una vez que el primer nodo reciba su mensaje por el extremo opuesto al que lo mando, y comenzara una tercer ronda con la misma modalidad donde el primer y segundo lider no podran ser seleccionados.

- Cuando el primer nodo reciba el token del tercer lider procedera a avisarle a todos los demas acerca de quien es el tercer lider.

- Finalmente cuando el primer nodo reciba su mensaje por el extremo opuesto al que lo envio se terminara el proceso de elección de lider.