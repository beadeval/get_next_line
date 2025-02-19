/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:54:45 by beade-va          #+#    #+#             */
/*   Updated: 2025/02/19 21:16:37 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ft_strlen()	Calcular longitud de una cadena.
// ft_strchr()	Buscar \n en la cadena.
// ft_strjoin()	Concatenar fragmentos leídos.
// ft_strdup()	Duplicar una línea extraída.
// ft_substr()	Extraer la parte restante después de \n.

//Calcular la longitud para manejar la memoria cuando queremos unir o copiar datos (reservar memoria)
size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}
//Para encontrar un caracter (en este caso \n y verificar si ya tenemos la línea completa)
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		else
			s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
//Es necesario para evitar perder datos de lectura. En C no hay una función que concatene cadenas dinámicamente
//sin perder memoria. Cada vez que leemos datos con read(), tenemos que agregar lo nuevo a lo que ya habíamos leído antes.
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	total_len;
	char	*result;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	total_len = lens1 + lens2 + 1;
	result = malloc(total_len);
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}
//Al extraer una línea (con read), debemos crear una copia exacta de la parte que queremos devolver. Así, no modificamos
//el buffer original (se corrompe el contenido original y perdemos información importante).
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dest;

	if (!s)
		return (NULL);
	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// Nos permite dividir el buffer entre "parte a devolver" y "parte pendiente". Cuando extraemos una línea,
// necesitamos guardar la parte restante en el buffer estático.
// Esta función extrae una parte de una cadena (s), comenzando en la posición start y copiando hasta len caracteres.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_length;
	size_t	i;
	char	*substring;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		return (ft_strdup("")); // Retorna una cadena vacía en caso de out-of-bounds
	if (len > s_length - start) //Este paso asegura que no copiemos más caracteres de los que realmente existen en la cadena.
		len = s_length - start;
	substring = malloc(len + 1);
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len) //Mientras no hayamos comparado todos los caracteres
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
