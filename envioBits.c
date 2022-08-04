/* Librerías requeridas para la lectura del nombre del archivo, manejo de arrays y strings, apertura de archivos, 
   control de pines de GPIO en raspberry pi 4 (mediante bcm2835), tiempo y threads para controlar la frecuencia de operación.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <bcm2835.h>
#include <time.h>
#include <unistd.h>
#include <threads.h>

// Se setea el pin 11 (GPIO07) para usarlo en la transmisión 
#define PIN RPI_GPIO_P1_07

int main(int argc, char const *argv[]){
    // Lectura del nombre del archivo que contiene los bits (posteriormente se automatizará usando bash
    const char* filename = argv[1];

    // Se abre el archivo que ha sido indicado previamente
    FILE* input_file = fopen(filename, "r");
    // Se verifica que se pueda abrir y exista
    if (!input_file)
        exit(EXIT_FAILURE);
    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    // Se crea un arreglo con asignación dinámica del tamaño del contenido del archivo
    char* file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, input_file);
  
    // Se crea un array modificable para manipular los datos leídos
    char modificable[sb.st_size];
    // Se copia el contenido del char* file_contents (contenido del archivo), al array modificable
    strcpy(modificable, file_contents);

    // Verificar la inicialización
    if(!bcm2835_init())
        return 1;
    // Seleccionar el pin a usar
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
  
    // Iterar en el arreglo de bits y enviar un valor HIGH (1 lógico) o LOW (0 lógico) a la RPi
    for(size_t i =0; i< sb.st_size-1; i++){
        int bit = modificable[i] -48;
        if(bit==1){
             bcm2835_gpio_write(PIN, HIGH);
             thrd_sleep(&(struct timespec){.tv_sec=10}, NULL);
        }else{
             bcm2835_gpio_write(PIN, LOW);
             thrd_sleep(&(struct timespec){.tv_sec=10}, NULL);
        }       
    }
    // Cerrar el archivo y liberar la memoria utilizada por el arreglo file_contents
    fclose(input_file);
    free(file_contents);
    exit(EXIT_SUCCESS);
}

