#include "get_next_line.h"

// Declaraciones de las funciones que has implementado
char *get_next_line(int fd);

int main() {
    int fd;
    int fd2;
    char *line;

    // Abre el archivo para lectura (reemplaza "archivo.txt" con el nombre de tu archivo de prueba)
    fd = open("test.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);


    if (fd < 0) {
        perror("Error al abrir el archivo");
        return 1; // Si no se puede abrir el archivo, salimos con error
    }


    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));

    //Llamamos a get_next_line() y leemos línea por línea
    while ((line = get_next_line(fd)) != NULL) {
        // Imprimimos la línea leída
        printf("%s", line);
        
        // Liberamos la memoria de la línea después de imprimirla
        free(line);
    }

    // Cerramos el archivo después de terminar de leer
    close(fd);
    close(fd2);

    return 0;
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include "get_next_line.h"

// #define NUM_FILES 3

// int	main(void)
// {
// 	int		fd[NUM_FILES];
// 	char	*line;
// 	int		i;
// 	int		open_files = NUM_FILES;

// 	fd[0] = open("file1.txt", O_RDONLY);
// 	fd[1] = open("file2.txt", O_RDONLY);
// 	fd[2] = open("file3.txt", O_RDONLY);

// 	for (i = 0; i < NUM_FILES; i++)
// 	{
// 		if (fd[i] == -1)
// 		{
// 			perror("Error al abrir archivo");
// 			return (1);
// 		}
// 	}

// 	// Bucle que lee de los archivos alternando entre ellos
// 	while (open_files > 0)
// 	{
// 		open_files = 0;
// 		for (i = 0; i < NUM_FILES; i++)
// 		{
// 			if (fd[i] != -1)
// 			{
// 				line = get_next_line(fd[i]);
// 				if (line)
// 				{
// 					printf("file%d: %s", i + 1, line);
// 					free(line);
// 					open_files++;
// 				}
// 				else
// 				{
// 					close(fd[i]);
// 					fd[i] = -1;
// 				}
// 			}
// 		}
// 	}
// 	return (0);
// }
