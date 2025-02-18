#include "get_next_line.h"

// Declaraciones de las funciones que has implementado
char *get_next_line(int fd);

int main() {
    int fd;
    char *line;

    // Abre el archivo para lectura (reemplaza "archivo.txt" con el nombre de tu archivo de prueba)
    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error al abrir el archivo");
        return 1; // Si no se puede abrir el archivo, salimos con error
    }

    // Llamamos a get_next_line() y leemos línea por línea
    while ((line = get_next_line(fd)) != NULL) {
        // Imprimimos la línea leída
        printf("%s", line);
        
        // Liberamos la memoria de la línea después de imprimirla
        free(line);
    }

    // Cerramos el archivo después de terminar de leer
    close(fd);

    return 0;
}
