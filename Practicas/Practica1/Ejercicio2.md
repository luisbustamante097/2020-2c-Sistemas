# Ejercicio 2
El PCB (Process Control Block) de un sistema operativo para una arquitectura de 16 bits es
```c
struct PCB {
    int STAT;       // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
    int P_ID;       // process ID
    int PC;         // valor del PC del proceso al ser desalojado
    int RO;         // valor del registro R0 al ser desalojado
    ...
    int R15;        // valor del registro R15 al ser desalojado
    int CPU_TIME    // tiempo de ejecución del proceso
    }
```

1. Implementar la rutina `Ke_context_switch(PCB* pcb_0, PCB* pcb_1)` encargada de realizar el cambio de 
contexto entre dos procesos (cuyos programas ya han sido cargados en memoria) debido a que el primero ha 
consumido su quantum. `pcb_0` es el puntero al PCB del proceso a ser desalojado y `pcb_1` al PCB del
proceso a ser ejecutado a continuación. Para implementarla se cuenta con un lenguaje que posee acceso a los
registros del procesador R0, R1, ..., R15, y las siguientes operaciones:

```c
·=·;                                // asignación entre registros y memoria
int ke_currrent_user_time();        // devuelve el valor del cronómetro
void ke_reset_current_user_time();  // resetea el cronómetro
void ret();                         // desapila el tope de la pila y reemplaza el PC
void set_current_process(int pid);  // asigna al proceso con el pid como el siguiente a ejecutarse
```

```c
void Ke_context_switch(PCB* pcb_0, PCB* pcb_1){
    pcb_0->CPU_TIME = ke_currrent_user_time();
    pcb_0->R0 = R0;
    //...
    pcb_0->R15 = R15;
    // ME FALTA GUARDAR EL IP, pero no tengo forma de hacerlo
    
    // Dejo en estado Ready al proceso
    pcb_0->STAT = KE_READY;
    
    // Reseto el cronometro
    ke_reset_current_user_time();
    
    // reemplazo el PC
    ret();
    
    // Marco al nuevo proceso como Running
    pcb_1->STAT = KE_RUNNING;
    
    //Marco al pid para que se ejecute el nuevo proceso
    set_current_process(pcb_1->PC);
    
    return;
}
```