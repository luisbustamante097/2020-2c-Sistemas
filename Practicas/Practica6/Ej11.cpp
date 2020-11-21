#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define DOR_IO 1
#define ARM 2
#define SEEK_SECTOR 3
#define DOR_STATUS 4
#define ARM_STATUS 5
#define DATA_READY 6

#define IRQ_ERROR -1

// Sacado de Stackoverflow
class Semaphore
{
private:
    std::mutex mutex_;
    std::condition_variable condition_;
    unsigned long count_ = 0; // Initialized as locked.

public:
    void notify() {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        ++count_;
        condition_.notify_one();
    }

    void wait() {
        std::unique_lock<decltype(mutex_)> lock(mutex_);
        while(!count_) // Handle spurious wake-ups.
            condition_.wait(lock);
        --count_;
    }

    bool try_wait() {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        if(count_) {
            --count_;
            return true;
        }
        return false;
    }
};

// Devuelve la cantidad de sectores por cada pista del disco. El sector 0 es el primer sector de la pista.
int cantidad_sectores_por_pista();
// Escribe los datos apuntados por `src` en el último sector seleccionado.
void escribir_datos(void *src); 
// Espera durante `ms` milisegundos.
void sleep(int ms); 

// Escribe data en el registro de E/S.
void OUT(int IO_address, int data);
// Devuelve el valor almacenado en el registro de E/S.
int IN(int IO_address);
// Permite asociar el procedimiento handler a la interrupción IRQ. Devuelve `IRQ_ERROR` si ya está asociada a otro handler.
int request_irq(int irq, void *handler);
// Libera la interrupción IRQ del procedimiento asociado.
int free_irq(int irq);


//Obtengo el sector donde escribir
int obtener_sector();


// Handlers para parte 2 del ejercicio
void *handler_ready (){
    // Doy el paso a quien lo necesite
    ready.notify();
}

void *handler_chrono (){
    // Esta interrupcion ocurre cada 50ms
    // Por lo que solo quiero usarla cuando sea necesario
    if (chrono_enabled){
        chrono.notify();
    }
}

Semaphore ready;
Semaphore chrono;
std::atomic<bool> chrono_enabled;

int driver_init(){
    // Pido los IRQ correspondientes (Parte 2)
    if (request_irq(6,handler_ready)==IRQ_ERROR){
        return -1;
    }
    if (request_irq(7,handler_chrono)==IRQ_ERROR){
        return -1;
    }
    
    // Declaro dos semaforos para usar con las IRQs
    Semaphore ready;
    Semaphore chrono;
    std::atomic<bool> chrono_enabled;
    
}
int driver_open(){
    
}
int driver_close(){
    free_irq(6);
    free_irq(7);
}
int driver_read(int *data){}
int driver_write(int *data){
    write(obtener_sector(),(void*)data);
}
int driver_remove(){}

void write(int sector,void *data){
    // Verifico que el motor este encendido
    if (IN(DOR_STATUS) == 0){
        OUT(DOR_STATUS, 1);
    }
    // Espero 50 ms para estabilizar
    sleep(50);
    
    // Comienzo con el proceso de escritura
    // Calculo a que pista debo moverme
    int sects_por_pista = cantidad_sectores_por_pista();
    int pista = (int)floor(sector / sects_por_pista);
    // Calculo el sector relativo a la pista
    int sector_pista = sector % sects_por_pista; 
    // Me muevo a la pista
    OUT(ARM, pista);
    // Espero a que el brazo llegue a la pista
    while(!(IN(ARM_STATUS)==1)){}
    // Selecciono el sector de la pista correspondiente
    OUT(SEEK_SECTOR, sector_pista);
    sleep(50);
    //Escribo el dato en el sector seleccionado
    escribir_datos(data);
    // Espero a que se termine de grabar
    while(!(IN(DATA_READY)==1)){}
    
    // Apago motor ya que termine
    OUT(DOR_STATUS, 0);
    // Para apagarse correctamente debo esperar 200ms
    sleep(200);
}

void write_INTs(int sector,void *data){
    // Verifico que el motor este encendido
    if (IN(DOR_STATUS) == 0){
        OUT(DOR_STATUS, 1);
    }
    chrono_enabled = true;
    // Espero 50 ms para estabilizar (por IRQ)
    chrono.wait();
    // Es buena idea esperar uno mas porque
    // si no en el mejor caso espere solo 1ms
    chrono.wait();
    chrono_enabled = false;
        
    // Comienzo con el proceso de escritura
    // Calculo a que pista debo moverme
    int sects_por_pista = cantidad_sectores_por_pista();
    int pista = (int)floor(sector / sects_por_pista);
    // Calculo el sector relativo a la pista
    int sector_pista = sector % sects_por_pista; 
    // Me muevo a la pista
    OUT(ARM, pista);
    // Espero a que el brazo llegue a la pista
    ready.wait();
    // Selecciono el sector de la pista correspondiente
    OUT(SEEK_SECTOR, sector_pista);
    
    chrono_enabled = true;
    chrono.wait();
    chrono.wait();
    chrono_enabled = false;
    
    //Escribo el dato en el sector seleccionado
    escribir_datos(data);
    // Espero a que se termine de grabar
    ready.wait();
    
    // Apago motor ya que termine
    OUT(DOR_STATUS, 0);
    // Para apagarse correctamente debo esperar 200ms
    sleep(200);
}