---
output: 
    pdf_document:
        highlight: zenburn
# header-includes:
#  - \usepackage{fvextra}
#  - \DefineVerbatimEnvironment{Highlighting}{Verbatim}{breaklines,commandchars=\\\{\}}
# geometry: margin=2cm
html:
    highlight: tango
    toc: true
---

# Ejercicio 2

Tenemos estos dos casos de manejo de dispositivos de E/S. Indique cuál convendría usar según el que tenga menor *overhead*.

1. Se cuenta con un procesador de 400 MHz, y cada solicitud de polling consume 300 ciclos de reloj, calcule el *overhead* de un disco duro (HDD), que transfiere 16 bytes a la vez, a 4MB/s.
   
2. Se cuenta con un procesador de 400 MHz, y cada interrupción consume 500 ciclos de reloj, calcule el *overhead* de un disco duro (HDD), que transfiere 32 bytes a la vez, a 4MB/s.


1) 

La frecuencia del procesador es igual a $400 MHz = \frac{1}{(400*10^6)s}$, por lo que si cada solicitud de polling consume 300 ciclos el cual tranfiere 16 bytes a la vez, a $4MB/s = 4*10^{6} B/s$ (usando que 1 MB = 1000 KB = $10^6$ Bytes), entonces el *overhead* sera de:
$$ \frac{4*10^{6}}{16}*\frac{300}{400*10^{6}} = 18.75\% $$

2)

No vamos a tener en cuenta el tiempo activo por lo que solo tendre en cuenta los datos que dice el enunciado. 
La frecuencia del procesador es igual a $400 MHz = \frac{1}{(400*10^6)s}$, por lo que si cada interrupción consume 500 ciclos el cual tranfiere 32 bytes a la vez, a $4MB/s = 4*10^{6} B/s$ (usando la misma equivalencia anterior para 1MB), entonces el *overhead* sera de:

$$ \frac{4*10^{6}}{32} * \frac{500}{400*10^{6}} = 15.625\% $$


Por lo que se puede concluir facilmente que usando el **segundo caso** con interrupciones tiene un menor *overhead* de uso, por lo que seria mas factible usarlo.