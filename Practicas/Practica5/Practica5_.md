  
  
  
  
Tabla de contenidos
===
  
  
- [Tabla de contenidos](#tabla-de-contenidos)
- [Parte 1 – Sistemas de archivos](#parte-1--sistemas-de-archivos)
  - [Ejercicio 1 :star:](#ejercicio-1-star)
  - [Ejercicio 2 :star:](#ejercicio-2-star)
  - [Ejercicio 3 :star:](#ejercicio-3-star)
  - [Ejercicio 4 :star:](#ejercicio-4-star)
- [Parte 2 – Redundancia de disco y resguardo de datos](#parte-2--redundancia-de-disco-y-resguardo-de-datos)
  - [Ejercicio 5 :star:](#ejercicio-5-star)
  - [Ejercicio 6 :star:](#ejercicio-6-star)
  - [Ejercicio 7 :star:](#ejercicio-7-star)
  - [Ejercicio 8 :star:](#ejercicio-8-star)
  
#  Parte 1 – Sistemas de archivos
  
##  Ejercicio 1 :star:
  
- Suponer una computadora cuyo disco se accede sin memoria cache y un sistema de archivos FAT. Además, en este sistema, la FAT no queda almacenada en la memoria (recordar que lo normal es que la FAT se cargue en memoria). ¿Cuántos accesos al disco son necesarios para llegar hasta el último bloque de un archivo de N bloques?
  
---
  
Ya que la FAT no esta en memoria significa que se encuentra almacenada en disco, por lo que seguramente para acceder a la tabla se tenga que hacer un acceso al disco, y luego para llegar al EOF del archivo necesite N accesos.
Por lo que obtendriamos un total de N+1 accesos al disco
  
  
##  Ejercicio 2 :star:
  
- Suponer que se cuenta con un sistema de archivos basado en inodos y bloques de 4 KB
  1. Si se tiene un archivo de 40 KB, ¿cuántos bloques es necesario leer para procesarlo completamente?
  2. ¿Cuántos bloques es necesario leer si el archivo tiene 80 KB?
  
---
  
1. Al tener 12 bloques directos en el inodo, esto le permite tener hasta 12*4KB=48KB directos. Por lo que para un archivo de 40KB es necesario leer solo 10 bloques (10 bloques = 40KB) del disco (suponiendo que el inodo del archivo ya esta en memoria).
2. Seguramente un archivo de 80KB necesite de la indireccion simple del inodo, lo cual conduce a tener que leer 20 bloques (20 bloques = 80KB) mas un bloque extra que seria el bloque de indireccion. Por lo tanto necesita leer 21 bloques en total.
  
##  Ejercicio 3 :star:
  
- Una compañía que fabrica discos rígidos decide, como parte de cierta estrategia comercial, emprender la creación de un nuevo *filesystem*. Durante la fase de diseño preliminar los ingenieros a cargo del proyecto discuten acaloradamente la conveniencia de adoptar un enfoque inspirado en FAT o la de uno basado en inodos. 
Indicar cuál de las dos opciones recomendaría, y por qué, para cada uno de los siguientes requerimientos:
  1. Es importante que puedan crearse enlaces simbólicos.
  2. Es importante que la cantidad de sectores utilizados para guardar estructuras auxiliares sea acotada, independientemente del tamaño del disco.
  3. Es importante que el tamaño máximo de archivo sólo esté limitado por el tamaño del disco.
  4. Es importante que la cantidad de memoria principal ocupada por estructuras del filesystem en un instante dado sea (a lo sumo) lineal en la cantidad de archivos abiertos en ese momento.
  
---
  
1. Es importante que puedan crearse enlaces simbólicos.
   - Inodos: ya que FAT no soporta enlaces simbolicos
  
2. Es importante que la cantidad de sectores utilizados para guardar estructuras auxiliares sea acotada, independientemente del tamaño del disco.
   - FAT: Ya que solo tiene una tabla de archivos (y su duplicado) la cual solo va a crecer en funcion de la cantidad de archivos que contenga el disco. Un sistema de inodos no funcionaria muy bien ya que todos los bloques de datos del disco tienen estructuras auxiliares que crecen segun el tamaño del disco
  
3. Es importante que el tamaño máximo de archivo sólo esté limitado por el tamaño del disco.
   - Inodos: ya que FAT limita el tamaño de archivo a 4GB
  
4. Es importante que la cantidad de memoria principal ocupada por estructuras del filesystem en un instante dado sea (a lo sumo) lineal en la cantidad de archivos abiertos en ese momento.
   - Inodos: ya que FAT mantiene toda la FAT cargada en memoria desde el comienzo al final. En cambio con Inodos se levanta solo los inodos que se requieren.
  
##  Ejercicio 4 :star:
  
- Se tiene un disco rígido de 16 GB de espacio con sectores de 1 KB. Se desea dar formato al disco usando un sistema de archivos de uso específico llamado *HashFS*, basado en FAT. La idea es que no existen directorios ni archivos. Dado un path, se calcula el hash del nombre y éste indica cuál es el archivo buscado. En resumen, este sistema de archivo cuentas con dos tablas:
  - Una única FAT que guarda las entradas correspondientes al próximo bloque, indicando el final de un archivo cuando estos valores coinciden.
  - Una única tabla de hash que contiene, para cada hash posible, el identificador del bloque inicial y el tamaño en bytes del archivo correspondiente a dicho hash.
- La novedad es que este sistema de archivos permite configurar los siguientes elementos:
  - Tamaño del bloque: 2, 4 u 8 sectores.
  - Tamaño de identificadores de bloque: 8, 16, 24 o 32bits.
  - Tamaño del hash: 8, 16, 24 o 32bits.
  
1. Suponiendo que se configura con 2 sectores por bloque, identificadores de bloque de 24bits, y hash de 16bits. ¿Cuál es el tamaño que ocupa la FAT? ¿Cuál es el tamaño de la tabla de archivos?¿Cuál es el espacio que queda en disco para archivos?
2. Sabiendo que se desea maximizar la cantidad de archivos que el sistema soporta y que, además, en promedio los archivos tendrán un tamaño de 1 KB, ¿cuál sería la configuración óptima del sistema de archivos? Justificar.
3. ¿Cómo lo configuraría si el promedio de tamaño de archivos es de 16 MB? Justificar.
  
---
  
1. 
- Si tiene dos sectores por bloque significa que el disco de 16GB esta granularizado en bloques de 2KB, por lo que la cantidad de bloques en 16GB es igual a 
  
  <p align="center"><img src="https://latex.codecogs.com/png.latex?\frac{16GB}{2KB}%20=%20\frac{16*(2^{30})B}{2*(2^{10})B}%20=%208%20*%20(2^{20})\%20bloques."/></p>  
  
  
  Y como los identificadores de bloque son de 24 bits = 3 Bytes, entonces:
  
  <p align="center"><img src="https://latex.codecogs.com/png.latex?8%20*%20(2^{20})\%20bloques%20*%203%20\frac{B}{bloques}%20=%2024*(2^{20})%20B%20=%2024%20MB"/></p>  
  
  
  Por lo tanto la FAT ocupara **24 MB**
  
- La tabla de archivos se calculara de forma similar con la cantidad de bloques pero con 16 bits = 2 Bytes representando a cada bloque:
  <p align="center"><img src="https://latex.codecogs.com/png.latex?8%20*%20(2^{20})\%20bloques%20*%202%20\frac{B}{bloques}%20=%2016*(2^{20})%20B%20=%2016%20MB"/></p>  
  
  
  Por lo tanto la tabla de hashes tiene **16 MB**
  
- En disco quedaria:
  <p align="center"><img src="https://latex.codecogs.com/png.latex?16GB%20-%2024%20MB%20-%2016%20MB%20=%2015%20GB%20+%20984%20MB"/></p>  
  
  
  de espacio libre para el resto de los archivos.
  
2. 
Si en promedio tenemos archivos de 1 KB en el disco queremos primero que al menos los identificadores de bloque lleguen a poder referenciar a todos los archivos
  
Veamos cuantos archivos de 1KB entran en un disco: 
<p align="center"><img src="https://latex.codecogs.com/png.latex?\frac{16GB}{1KB}%20=%20\frac{16*2^{30}B}{1*2^{10}B}%20=%2016*2^{20}%20archivos"/></p>  
 por lo que debo poder referenciar a **casi** todos ellos (ya que era solo el promedio 1KB y ademas debo contar que va a haber un gasto de espacio en la estructura del FS).
  
- Con 8 bits puedo referencia hasta <img src="https://latex.codecogs.com/png.latex?2^{8}"/> archivos, por lo que no me sirve
- Con 16 bits puedo referenciar <img src="https://latex.codecogs.com/png.latex?2^{16}"/> archivos, por lo que tampoco me sirve
- Con 24 bits puedo referenciar <img src="https://latex.codecogs.com/png.latex?2^{24}"/> archivos, lo cual es suficiente para referenciar la cantidad aproximada de archivos y ademas no elijo 32 bits para que ocupen el menor espacio dentro de la FAT.
  
Me queda ver cual es el tamaño del bloque pero eso es mas trivial ya que se que van a ser archivos de aproximadamente 1KB por lo que debo elegir el menor tamaño de bloque que es 2 sectores por bloque
  
Por lo que hasta ahora tenemos que la mejor configuracion es: **2 sectores por bloque para identificadores de 24bits**
  
Para la tabla de hash podriamos a apuntar a las mismas especificaciones de la FAT ya que nos gustaria minimizar los bits que necesita cada hash pero sabemos que en promedio los archivos tienen 1KB y esto implica que cada archivo va a tener en promedio solo 1 bloque, y como la tabla de hash debe referenciar al primer bloque de cada archivo vamos a terminar teniendo una tabla de hash que deba referenciar a casi todos los bloques. por lo que necesitaremos una **hashes de 24bits**
  
  
  
  
3.
  
En este caso ahi que comenzar el razonamiento al reves, para los bloques podemos utilizar la mayor cantidad de sectores en un bloque ya que sabemos que los archivos son bastante grandes, y ademas eso minimiza la cantidad de referencias en la FAT. Por lo tanto necesitamos **8 sectores por bloque**.
  
Ya que entonces tendriamos un almacenamiento granularizado en bloques de 8KB tenemos que hay:
<p align="center"><img src="https://latex.codecogs.com/png.latex?\frac{16GB}{\frac{8KB}{bloque}}%20=%20\frac{16*2^{30}}{8*2^{10}}%20=%202*%202^{20}%20bloques"/></p>  
 exactamente en el disco. Por lo que necesitamos al menos **24 bits para identificar** cada bloque del disco.
  
En cuanto el tamaño de hash hay que tener en cuenta que cada hash apunta al comienzo de un archivo, entonces con archivos de 16MB podriamos almacenar:
<p align="center"><img src="https://latex.codecogs.com/png.latex?\frac{16GB}{16MB}%20=%20\frac{16*2^{30}B}{16*2^{20}B}%20=%202^{10}%20archivos"/></p>  
  
  
Por lo tanto necesitamos al menos **16 bits de hash**, para poder referenciar a todos esos archivos.
  
---
  
#  Parte 2 – Redundancia de disco y resguardo de datos
  
  
##  Ejercicio 5 :star:
  
- ¿Podría en algún contexto un esquema de organización de RAID nivel 1 proporcionar un mejor rendimiento para las solicitudes de lectura que un esquema RAID nivel 0?
  
En general tienen un rendimiento muy similar RAID 0 y RAID 1, pero RAID 1 tendra una mejor disponibilidad cuando se trata de dos computadoras que requieren de hacer una lectura, ya que ambas podran hacerlo simultaneamente (mientras solo sea lectura). Aca RAID 0 se ve desventajada ya que no podra tener la misma ventaja ya que la computadora que llegue ultima debera esperar.
  
##  Ejercicio 6 :star:
  
- Considerar un esquema de organización RAID nivel 5 compuesto por 5 discos; es decir, que cada 4 bloques almacenados en 4 discos, el disco restante almacena la información de paridad. ¿A cuántos bloques hay que acceder para llevar a cabo las siguientes operaciones?
  1. Una escritura de un bloque de datos
  2. Una escritura de siete bloques contiguos de datos.
  
La estructura del disco es la siguiente:
```
                RAID 5
   ++=====++=====++=====++=====++
   ||     ||     ||     ||     ||        
|  A1  |  A2  |  A3  |  A4  |  A*  |                           
|  B1  |  B2  |  B3  |  B*  |  B5  |                           
|  C1  |  C2  |  C*  |  C4  |  C5  |                           
|  D1  |  D*  |  D3  |  D4  |  D5  |                           
|  E*  |  E2  |  E3  |  E4  |  E5  |                           
|  F1  |  F2  |  F3  |  F4  |  F*  |                           
|  G1  |  G2  |  G3  |  G*  |  G5  |                           
|  H1  |  H2  |  H*  |  H4  |  H5  |                           
|  I1  |  I*  |  I3  |  I4  |  I5  |                           
|  J*  |  J2  |  J3  |  J4  |  J5  |                           
|  ..  |  ..  |  ..  |  ..  |  ..  |                           
  
```
1. Para escribir necesita leer el bloque deseado, leer el bloque de paridad (para generar la nueva info de recuperacion en el bloque de paridad) y recien puede escribir en el bloque deseado y por ultimo escribe en el bloque de paridad, lo cual resulta en **4 accesos** para una modificacion de un bloque
  
2. Repitiendo la misma formula del punto 1 se tiene 4 accesos por cada bloque que se quiere escribir, por lo que la formula dictaria que se necesitan de 28 accesos - 2 (o 4) accesos de lectura y escritura ya que si se hizo la modificacion de 7 bloques contiguos, al menos uno de ellos es solo un bloque de paridad. Por lo tanto tendriamos **26 o 24 accesos** segun el caso.
  
##  Ejercicio 7 :star:
  
- Una estrategia de copias de seguridad (“backup”) en cintas utiliza 5 cintas que va rotando. Responder y justificar cuántas cintas puede llegar a ser necesario utilizar para restaurar un archivo en cada uno de los siguientes casos:
  1. Total.
  2. Diferencial.
  3. Incremental.
  
???
  
##  Ejercicio 8 :star:
  
- Un sistema cuenta con almacenamiento basado en RAID 5. Responda verdadero o falso justificando:
  1. Realizar copias de seguridad a cinta es innecesario ya que no incrementa el nivel de protección.
  2. Desde el punto de vista de la seguridad informática, realizar copias de seguridad a cintas aumenta la exposición a riesgos de los datos.
  
1. Falso, pero discutible, porque es cierto que las cintas duran mucho mas que un disco en general, pero tambien se tiene que no son inmortales ya que pueden sufrir de problemas mecanicos los cuales pueden no ser facilmente solucionables si las cintas son de muchos años atras. Tambien son susceptibles al calor y a la humedad por sus caracteristicas magneticas. A pesar de eso lo lo mas probable es que para RAID 5 (como para otros sistemas) resulte mas seguro usar cintas, pero depende muchisimo de lo que tenga que hacer. 
2. Falso, y tambien discutible, ya que no se presenta demasiado contexto. En general ambos metodos son igual de inseguros si alguien tiene acceso a ellos, pero en el caso de las cintas se tiene la diferencia que los mecanismos para acceder a ellas son mucho mas costosos y complejos, por lo que parecer ser mas dificil de exponer a riesgos los datos.
  