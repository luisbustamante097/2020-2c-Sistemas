```                                                          
    new                                                      
    |                                                        
    |                                                        
    |       +------------->running-------------------+       
    |       |              |   |                     |       
    |       |              |   |                     |       
    |       |              |   |                     v       
    +--->ready<------------+   |                 terminated  
            ^                  |                             
            |                  |                             
            |                  v                             
            +--------------blocked                           
```

- new -> ready: Un proceso recien creado debe pasa al estado Ready para ser ejecutado,
en este proceso esta involucrado el scheduler.
- ready -> running: Para ser ejecutado por CPU el scheduler debe cambiar a running el proceso.
- running -> ready: Una vez que se agoto el quantum dicho proceso, debe esperar a ser llamado de vuelta
por el scheduler cuando sea su turno.
- running -> blocked: Si el proceso desea ser congelado por X razon, o el SO decide que suceda, el proceso
puede ser blocqueado en ejecucion.
- blocked -> ready: Cuando el proceso deja de estar congelado, o el SO lo decide, el proceso vuelve
a estar ready para que el scheduler pueda tomarlo en su turno.
- running -> terminated: El proceso deberia terminar mientras sea usado por el CPU, por lo que en algun
momento debe salir de la agenda del scheduler. Aunque tambien puede ser el scheduler que termine el proceso.