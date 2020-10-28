
## Un sistema de archivos de UNIX - Ext2, tiene bloques de tamaño 512 B y el direccionamiento a bloques de disco (LBA) es de 4 bytes. A su vez, cada inodo cuenta con 12 entradas directas a bloques de datos, una indirecta, una doble - indirecta y una triple - indirecta.

- ¿Cuál es el tamaño máximo de archivo que soporta?
  Cada bloque puede tener 512/4 = 128 punteros
    punteros = 12 * 512
    punteros_ind_simple = 128 * 512
    punteros_ind_doble = 128^2 * 512
    punteros_ind_triple = 128^3 * 512
  
  Total = 12 * 512 + 128 * 512 + 128^2 * 512 + 128^3 * 512
        = 1082202112 B = 1056838 KB = 1032 MB = 1GB + 8 MB

- ¿Cuántos bloques hace falta acceder para procesar completo un archivo de 8 GB?
  1 bloque para acceder al inodo
  bloques = 12 bloques
  bloques_ind_simple = 128 + 1
  bloques_ind_doble = 128^2 + 128 + 1
  bloques_ind_triple = 128^3 + 128^2 + 128 + 1
  
  Total un archivo (1 GB)= 128^3 + 128^2 + 128 + 1 + 128^2 + 128 + 1 + 128 + 1 + 12 + 1 = 2130320 Bloques
  
  Total 8 archivos = 2130320 * 8 = 17042560
   (8*8) = 64MB -> 64 * 1024 * 1024 / 512 = 131072
   
   Total final para 8 Gb = 17042560 - 131072 = 16911488 bloques