---
output:
    pdf_document: {highlight: zenburn}
header-includes:
    - '\usepackage{fvextra}'
    - '\DefineVerbatimEnvironment{Highlighting}{Verbatim}{breaklines,commandchars=\\\{\}}'
geometry: margin=2cm
html:
    highlight: tango
    toc: true
---  
  
  
  
Tabla de contenidos
===
  
  
- [Ejercicio 1](#ejercicio-1 )
- [Ejercicio 2](#ejercicio-2 )
- [Ejercicio 3](#ejercicio-3 )
- [Ejercicio 4](#ejercicio-4 )
  
#  Ejercicio 1 
  
- Suponer una computadora cuyo disco se accede sin memoria cache y un sistema de archivos FAT. Además, en este sistema, la FAT no queda almacenada en la memoria (recordar que lo normal es que la FAT se cargue en memoria). ¿Cuántos accesos al disco son necesarios para llegar hasta el último bloque de un archivo de N bloques?
  
---
  
Ya que la FAT no esta en memoria significa que se encuentra almacenada en disco, por lo que seguramente para acceder a la tabla se tenga que hacer un acceso al disco, y luego para llegar al EOF del archivo necesite N accesos.
Por lo que obtendriamos un total de N+1 accesos al disco
  
  
#  Ejercicio 2
  
- Suponer que se cuenta con un sistema de archivos basado en inodos y bloques de 4 KB
  1. Si se tiene un archivo de 40 KB, ¿cuántos bloques es necesario leer para procesarlo completamente?
  2. ¿Cuántos bloques es necesario leer si el archivo tiene 80 KB?
  
---
  
1. Al tener 12 bloques directos en el inodo, esto le permite tener hasta 12*4KB=48KB directos. Por lo que para un archivo de 40KB es necesario leer solo 10 bloques (10 bloques = 40KB) del disco (suponiendo que el inodo del archivo ya esta en memoria).
2. Seguramente un archivo de 80KB necesite de la indireccion simple del inodo, lo cual conduce a tener que leer 20 bloques (20 bloques = 80KB) mas un bloque extra que seria el bloque de indireccion. Por lo tanto necesita leer 21 bloques en total.
  
#  Ejercicio 3
  
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
  
#  Ejercicio 4
  
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
  
  <p align="center"><img src="https://latex.codecogs.com/png.latex?&#x5C;frac{16GB}{2KB}%20=%20&#x5C;frac{16*(2^{30})B}{2*(2^{10})B}%20=%208%20*%20(2^{20})&#x5C;%20bloques."/></p>  
  
  
  Y como los identificadores de bloque son de 24 bits = 3 Bytes, entonces:
  
  <p align="center"><img src="https://latex.codecogs.com/png.latex?8%20*%20(2^{20})&#x5C;%20bloques%20*%203%20&#x5C;frac{B}{bloques}%20=%2024*(2^{20})%20B%20=%2024%20MB"/></p>  
  
  
  Por lo tanto la FAT ocupara **24 MB**
  
- La tabla de archivos se calculara de forma similar con la cantidad de bloques pero con 16 bits = 2 Bytes representando a cada bloque:
  <p align="center"><img src="https://latex.codecogs.com/png.latex?8%20*%20(2^{20})&#x5C;%20bloques%20*%202%20&#x5C;frac{B}{bloques}%20=%2016*(2^{20})%20B%20=%2016%20MB"/></p>  
  
  
  Por lo tanto la tabla de hashes tiene **16 MB**
  
- En disco quedaria:
  <p align="center"><img src="https://latex.codecogs.com/png.latex?16GB%20-%2024%20MB%20-%2016%20MB%20=%2015%20GB%20+%20984%20MB"/></p>  
  
  
  de espacio libre para el resto de los archivos.
  
2. 
Si en promedio tenemos archivos de 1 KB en el disco queremos primero que al menos los identificadores de bloque lleguen a poder referenciar a todos los archivos
  
Veamos cuantos archivos de 1KB entran en un disco: 
<p align="center"><img src="https://latex.codecogs.com/png.latex?&#x5C;frac{16GB}{1KB}%20=%20&#x5C;frac{16*2^{30}B}{1*2^{10}B}%20=%2016*2^{20}%20archivos"/></p>  
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
<p align="center"><img src="https://latex.codecogs.com/png.latex?&#x5C;frac{16GB}{&#x5C;frac{8KB}{bloque}}%20=%20&#x5C;frac{16*2^{30}}{8*2^{10}}%20=%202*%202^{20}%20bloques"/></p>  
 exactamente en el disco. Por lo que necesitamos al menos **24 bits para identificar** cada bloque del disco.
  
En cuanto el tamaño de hash hay que tener en cuenta que cada hash apunta al comienzo de un archivo, entonces con archivos de 16MB podriamos almacenar:
<p align="center"><img src="https://latex.codecogs.com/png.latex?&#x5C;frac{16GB}{16MB}%20=%20&#x5C;frac{16*2^{30}B}{16*2^{20}B}%20=%202^{10}%20archivos"/></p>  
  
  
Por lo tanto necesitamos al menos **16 bits de hash**, para poder referenciar a todos esos archivos.
  
  