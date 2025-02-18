/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:54:43 by beade-va          #+#    #+#             */
/*   Updated: 2025/02/18 23:23:58 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Por defecto, las variables son locales al scope (alcance) en el cual son definidas. Las variables pueden ser 
// declaradas como estáticas para incrementar el alcance (scope) en el archivo que las contenga. Como resultado, 
// estas variables pueden ser accedidas en cualquier lugar dentro del archivo.

// 1	Leer datos en buffer	read() -> Como read() solo lee bloques fijos de BUFFER_SIZE bytes, no podemos garantizar que obtendremos la línea completa en una sola lectura.
// 2	Acumular en static_buffer	ft_strjoin()
// 3	Buscar \n en static_buffer	ft_strchr()
// 4	Extraer línea hasta \n	ft_strdup()
// 5	Guardar lo que sobra para la próxima llamada	ft_substr()

//BUFFER_SIZE es una constante que define cuántos bytes vamos a leer en cada llamada a read()

// Usa read() para leer datos en bloques de BUFFER_SIZE.
// Acumula el contenido en buffer usando ft_strjoin().
// Se detiene cuando encuentra \n o se acaba el archivo.
static char	*read_and_accumulate(int fd, char *buffer)
{
    char *buffer_temporary;
    int bytes_read;
    
    buffer_temporary = malloc(BUFFER_SIZE + 1); //Lo reservamos para leer datos en bloques
    if (!buffer_temporary)
    return (NULL);
    while (!ft_strchr(buffer, '\n') && bytes_read > 0) //Se segurirá leyendo mientras que buffer no tenga \n y read() devuelva datos
    {
        bytes_read = read(fd, buffer_temporary, BUFFER_SIZE); // Lee hasta BUFFER_SIZE bytes desde fd
        if (bytes_read == -1) //Liberamos memoria y salimos (-1 -> ERROR, 0 -> no hay más para leer, >0 -> bytes leídos)
		{
			free(buffer_temporary);
			return (NULL);
		}
        buffer_temporary[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, buffer_temporary); //Acumulamos los datos del buffer
    }
    free(buffer_temporary);
    return (buffer);
}

static char	*extract_line(char *buffer)
{
    char *newline;
    int line_length;
    char    *extracted_line;
    if (!buffer || *buffer == '\0')
    return (NULL);
    newline = ft_strchr(buffer, '\n'); //Buscamos el salto de línea en el buffer y guardamos la posición del caracter
    if (newline) 
        line_length = newline - buffer + 1; //Calculamos la longitud de la línea hasta el salto de línea (termina justo antes) + \n
    else //La cadena es una línea completa (o es todo lo que queda por leer)
        line_length = ft_strlen(buffer);
    extracted_line = ft_substr(buffer, 0, line_length); //Extraemos la línea desde el inicio
    return (extracted_line);
}
// Cuando get_next_line() extrae una línea, lo que sobra en buffer después del \n debe guardarse para la próxima llamada.
// 📌 update_buffer() se encarga de eliminar la parte ya leída y actualizar buffer para empezar desde el siguiente carácter después de \n.
static char	*update_buffer(char *buffer)
{
	char	*new_buffer; //Guarda el contenido que sobra después de la línea extraída
	int		line_length;
	char	*line_position;
    line_position = ft_strchr(buffer, '\n'); //El buffer tiene los datos acumulados hasta el momento
    if (line_position) 
        line_length = line_position - buffer + 1; //Calculamos la longitud de la línea hasta el salto de línea (termina justo antes) + \n
    else //La cadena es una línea completa (o es todo lo que queda por leer)
    line_length = ft_strlen(buffer);
    new_buffer = ft_substr(buffer, line_length, ft_strlen(buffer) - line_length); //Creamos un nuevo buffer con el contenido restante (le pasa-
    //mos el buffer, comenzamos a partir de donde hemos encontrado el salto de línea, y pasamos como argumento la longitud de la cadena a extraer, es decir,
    //el contenido restante después de la línea extraída)
    free(buffer); //Liberamos el buffer original porque el contenido se ha copiado en el nuevo buffer
    return (new_buffer);
}

//Guardamos lo que nos queda por leer después de extraer cada línea (si no lo implementamos perdemos información y fallarían las llamadas
//sucesivas)
char	*get_next_line(int fd) //Lee un archivo línea por línea, devolviendo una línea completa en cada llamada.
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_accumulate(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}



