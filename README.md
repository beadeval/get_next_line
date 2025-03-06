El objetivo o función de get_next_line() es leer una línea completa desde un descriptor de archivo, devolviendo esa línea como una cadena o string. Se lee desde un archivo o entrada estándar (parámetro de entrada), devuelve una sola línea cada vez que se le llama (útil para procesas archivos de texto) y, si la función se llama de nuevo, continúa leyendo desde donde se quedó sin perder datos. Además, respeta buffers internos y no desperdicia memoria.

La función get_next_line necesita: 
✅ Leer bloques de datos (normalmente con read).
✅ Acumular esos datos hasta formar una línea completa.
✅ Detectar el salto de línea (\n) para saber cuándo devolver una línea.
✅ Conservar lo que sobra (si lees más de una línea) para la siguiente llamada.

Funciones auxiliares necesarias para get_next_line
1️⃣ ft_strchr: Buscar un \n dentro de un string
    • Esta función es clave porque necesitamos saber si ya hemos leído una línea completa.
    • Cada vez que leemos un bloque de datos, comprobamos si dentro de ese bloque hay un salto de línea (\n).
    • Si lo encontramos, significa que tenemos una línea lista para devolver.
    • Sin esta función, get_next_line no sabría cuándo detenerse.

2️⃣ ft_strjoin: Unir strings (concatenar)
    • En cada llamada a read(), obtenemos un nuevo bloque de texto.
    • Necesitamos acumularlo junto con lo que ya habíamos leído antes (si es que aún no tenemos una línea completa).
    • Esta función nos permite juntar el "buffer acumulado" con lo nuevo que acabamos de leer.

3️⃣ ft_strdup: Crear una copia de un string
    • Cuando devolvemos una línea, es necesario copiar solo esa línea y almacenarla en un nuevo string.
    • También se usa para copiar lo que sobra después de un \n, para tenerlo listo en la siguiente llamada a get_next_line.
    • Así nos aseguramos de no perder datos.

4️⃣ ft_substr: Extraer una subcadena de un string
    • Después de encontrar un \n, tenemos un string completo como línea.
    • Pero el buffer puede contener más datos después de esa línea.
    • Con ft_substr, podemos cortar la línea justo donde termina y guardar el resto para la siguiente llamada.

5️⃣ ft_strlen: Calcular la longitud de un string
    • Necesario para asignar memoria correctamente al crear copias, unir strings o extraer subcadenas.
    • Sin esta función, no podríamos reservar el tamaño adecuado de cada nuevo string.

En resumen
Estas funciones forman la base técnica que permite que get_next_line funcione correctamente. Sin ellas, sería imposible:
✅ Detectar el final de cada línea (ft_strchr).
✅ Acumular datos leídos (ft_strjoin).
✅ Preparar y devolver una línea completa (ft_strdup y ft_substr).
✅ Calcular tamaños al reservar memoria (ft_strlen).
Por eso, aunque get_next_line es una sola función "grande", en realidad es como un pequeño equipo de funciones que trabajan juntas para resolver el problema de leer archivos línea por línea de forma eficiente.

🔄 1. read_and_accumulate
¿Qué hace?
Esta función se encarga de leer datos desde el archivo (con read) y de acumularlos en un buffer dinámico. Este buffer es donde vamos guardando todo lo que hemos leído hasta el momento, porque una línea puede venir dividida en varios read() si es muy larga.
Paso a paso:
    1. Prepara un buffer temporal (buffer_temporary) del tamaño BUFFER_SIZE para cada lectura.
    2. Si el buffer es NULL (es la primera vez que se llama), crea un string vacío para empezar.
    3. Entra en un bucle:
        ◦ Si todavía no encontramos un \n, sigue leyendo.
        ◦ Cada read añade datos al buffer_temporary, que se concatenan al buffer ya acumulado.
    4. Cuando encuentra un \n o cuando ya no hay nada más para leer, sale del bucle.

Funciones auxiliares usadas:
✅ ft_strdup: Para inicializar el buffer.
✅ ft_strchr: Para ver si ya hay un salto de línea.
✅ ft_strjoin: Para acumular lo leído.

💥 Posibles errores manejados:
❌ Si malloc falla.
❌ Si read devuelve -1 (error de lectura).

✂️ 2. extract_line
¿Qué hace?
Una vez que el buffer tiene al menos una línea completa, esta función extrae esa línea.
Paso a paso:
    1. Busca el primer \n en el buffer.
    2. Calcula cuántos caracteres forman la línea (desde el inicio hasta el \n, incluido).
    3. Extrae exactamente esa porción usando ft_substr.
    4. Devuelve la línea lista para ser utilizada por el programa principal.

Funciones auxiliares usadas:
✅ ft_strchr: Para encontrar el \n.
✅ ft_strlen: Por si no hay \n, para devolver lo que haya.
✅ ft_substr: Para cortar justo la parte de la línea.

📦 3. update_buffer
¿Qué hace?
Después de devolver la línea, el buffer todavía puede tener datos sobrantes (lo que viene después del \n). Esta función:
    • Elimina la línea ya entregada.
    • Deja solo lo que sobra, preparado para la próxima llamada a get_next_line.

Paso a paso:
    1. Busca el \n (donde termina la línea devuelta).
    2. Si hay datos después, crea un nuevo buffer solo con esos datos.
    3. Libera el buffer viejo.
    4. Devuelve el nuevo buffer actualizado.

Funciones auxiliares usadas:
✅ ft_strchr: Para encontrar el \n.
✅ ft_strlen: Para calcular cuánto sobra.
✅ ft_substr: Para cortar justo la parte que sobra.

🚀 4. get_next_line
¿Qué hace?
Este es el corazón del programa. Es la función principal que el usuario llama, y que coordina todo el flujo:
Paso a paso:
    1. Si el fd es inválido o el BUFFER_SIZE es incorrecto, devuelve NULL.
    2. Llama a read_and_accumulate para leer y preparar el buffer.
    3. Si el buffer es NULL (por error o porque ya terminó el archivo), devuelve NULL.
    4. Si el buffer está vacío, libera y devuelve NULL (caso archivo vacío o EOF).
    5. Extrae la primera línea completa (con extract_line).
    6. Actualiza el buffer para la siguiente llamada (con update_buffer).
    7. Si después de actualizar el buffer queda vacío, lo libera (EOF alcanzado después de esta línea).

Funciones auxiliares usadas:
✅ read_and_accumulate: Lee y acumula el texto.
✅ extract_line: Extrae una línea lista para devolver.
✅ update_buffer: Prepara el buffer para la próxima llamada.

Manejo de errores:
❌ Si read_and_accumulate falla, devuelve NULL.
❌ Si hay un malloc fallido en cualquier momento, limpia y sale.

🔗 BUFFER_SIZE pequeño = read() más veces = más lento.
💨 BUFFER_SIZE grande = read() menos veces = más rápido.
❗️ Pero no afecta la funcionalidad: get_next_line es robusto y seguirá devolviendo cada línea correctamente, aunque el rendimiento se degrade con un BUFFER_SIZE demasiado pequeño.

🔍 Caso 1: BUFFER_SIZE = 9999
✅ Funciona correctamente.
    • Lo único que cambia es que read() leerá hasta 9999 bytes de una vez.
    • Si hay líneas muy largas (o pocas líneas muy separadas por \n), este tamaño es eficiente porque se reduce la cantidad de read().
    • get_next_line no tiene un límite máximo de BUFFER_SIZE, más allá de lo que el sistema operativo y read() permitan.

🔍 Caso 2: BUFFER_SIZE = 1
✅ Funciona correctamente, pero es muy ineficiente.
    • read() leerá solo un byte cada vez.
    • Esto hace que para leer una línea completa haya muchísimas llamadas a read() y muchas operaciones de copia y concatenación.
    • Pero desde un punto de vista funcional, get_next_line sigue devolviendo cada línea correctamente.
    • Solo que será extremadamente lento, sobre todo con archivos grandes o líneas largas.

🔍 Caso 3: BUFFER_SIZE = 10000000 (diez millones)
✅ Funciona, pero puede ser peligroso.
    • El read() intentará leer 10 millones de bytes de golpe.
    • Si el archivo es más pequeño o hay poca RAM disponible, es posible que:
        ◦ El sistema operativo devuelva menos datos (esto es normal y get_next_line debería manejarlo bien).
        ◦ Pero si hay un problema de memoria (por ejemplo, malloc falla al reservar un buffer tan grande), get_next_line fallará.
    • Sin embargo, en condiciones normales, get_next_line está preparado para manejar cualquier tamaño de buffer.
🗃️ ¿Qué es un buffer?
Un buffer es un bloque de memoria (generalmente un array o string) que se usa para almacenar temporalmente datos. En el caso de get_next_line, el buffer es donde guardamos los datos leídos del archivo, para luego procesarlos y devolver las líneas.
Ejemplo práctico:
Imagina que estás llenando un vaso de agua desde un grifo. El vaso es el buffer. El agua que entra es lo que read() lee desde el archivo. Cuando el vaso está lleno, lo usas (procesas o devuelves la línea) y luego vuelves a llenarlo.

¿Por qué usamos buffers?
✅ Leer grandes bloques es más eficiente que leer carácter por carácter.
✅ Permite acumular datos hasta que tengamos una línea completa.

💥 ¿Qué es un leak de memoria?
Un leak de memoria (fuga de memoria) ocurre cuando reservas memoria con malloc, pero nunca la liberas con free. Esa memoria queda "perdida": el programa ya no puede acceder a ella, pero el sistema operativo aún la tiene marcada como ocupada.

Ejemplo práctico:
Es como si alquilas un almacén, guardas cosas dentro, pero pierdes la llave. El almacén sigue ocupado, pero tú ya no puedes entrar ni liberar ese espacio. Si haces esto muchas veces, te quedas sin almacenes disponibles (sin memoria libre).

En get_next_line, un leak ocurre si:
    • Reservas un buffer con malloc, pero te olvidas de hacer free.
    • Sales de la función por algún error o condición especial, sin liberar lo que ya habías reservado.

📦 ¿Qué es malloc?
malloc significa "memory allocation", o sea, "asignación de memoria".
Es una función que reserva un bloque de memoria del tamaño que le digas. Pero no lo inicializa: el contenido de la memoria es basura (bytes aleatorios que estaban ahí antes).
size es el número de bytes que quieres reservar.

💧 ¿Qué es calloc?
calloc significa "clear allocation", o sea, "asignación limpia".
Hace lo mismo que malloc (reserva memoria), pero además pone todo a cero.
nmemb: número de elementos.
size: tamaño de cada elemento (en bytes).

💣 Casos peligrosos (leaks y double free)
Caso	Ejemplo	Problema
Leak	Te olvidas de free()	Pierdes memoria
Double Free	Haces free() dos veces	Comportamiento indefinido
Use After Free	Accedes a memoria después de free()	Crash o datos corruptos


📦 ¿Qué es la memoria de un programa?
Cuando ejecutas un programa en C, el sistema operativo le asigna un espacio de memoria. Ese espacio está dividido en varias zonas, cada una con su propósito. Las dos más importantes para nosotros son:

🧵 La Pila (Stack)
📍 Qué es
La pila es una zona de memoria que funciona como una torre de cajas apiladas. Cada vez que llamas a una función, el programa pone una caja en la cima de la pila.
Esa caja contiene:
    • Variables locales de la función.
    • Los parámetros que le pasaste a la función.
    • La dirección a la que debe volver cuando la función termine.

🚀 Cómo funciona
    • Cada vez que llamas a una función, se apila una caja nueva (stack frame).
    • Cuando la función termina, esa caja se quita (desapila) automáticamente.
    • No tienes que preocuparte por liberar esta memoria, lo hace el sistema solo.

✅ Ventajas
✔️ Súper rápida (apilar y desapilar es instantáneo).
✔️ Automática, no hay que hacer malloc ni free.
✔️ Ideal para variables temporales.

⚠️ Problemas
❌ La pila es pequeña (normalmente unos 2-8 MB).
❌ Si intentas guardar algo gigante (como un array de 1 millón de enteros), te da un stack overflow.


📦 El Heap (Montón)
📍 Qué es
El heap es una zona mucho más grande que la pila.
Es un almacén gigante y desordenado donde puedes pedir memoria dinámicamente usando malloc, calloc o realloc.

🚀 Cómo funciona
    • Cuando llamas a malloc, el programa busca un trozo libre en el heap y te lo da.
    • Esa memoria no desaparece sola. Sigue existiendo hasta que tú decidas liberarla con free.

✅ Ventajas
✔️ Mucho más grande que la pila (puedes pedir gigabytes).
✔️ Ideal para datos grandes o estructuras que deben sobrevivir entre funciones.

⚠️ Problemas
❌ Más lento que la pila (buscar espacio libre es caro).
❌ Si te olvidas de hacer free, creas un memory leak (fuga de memoria).
❌ Si liberas dos veces o accedes a memoria ya liberada, tienes un segmentation fault.

🧵 La pila es rápida y automática.
📦 El heap es grande pero manual.
💣 Cada malloc sin free es un leak.
💥 Cada free doble es una bomba.

📌 ¿Qué es una variable estática?
Una variable estática en C se declara con la palabra clave static. La principal característica de estas variables es que su valor persiste entre las llamadas a una función (a diferencia de las variables locales, que se reinician cada vez que la función se llama).

🧵 Características de las variables estáticas
1. Persistencia de datos
Las variables estáticas conservan su valor incluso después de que la función donde se declararon termine su ejecución. Esto es diferente de las variables locales, que se destruyen cuando la función termina.
2. Alcance limitado
Aunque las variables estáticas conservan su valor, solo son accesibles dentro de la función donde se declaran (si son locales) o dentro del archivo (si son globales). Es decir, su alcance está limitado al bloque donde se encuentran, pero su valor persiste entre llamadas.
3. Ubicación en memoria
Las variables estáticas se almacenan en una zona especial de memoria: el segmento de datos estáticos. Esto es diferente de las variables locales, que se almacenan en la pila.

🛠️ ¿Cuándo usar variables estáticas?
    • Contadores: Para mantener el estado entre múltiples invocaciones de una función sin tener que pasar el valor por argumento o usar variables globales.
    • Memoria persistente: Cuando quieres que un valor persista, pero no quieres hacer que sea accesible globalmente.
    • Evitar errores por variables globales: Usar variables estáticas locales para evitar que la variable se manipule fuera de la función y cause efectos secundarios inesperados.

💡 ¿Por qué se usan las variables estáticas?
Las variables estáticas se usan para mantener el estado local a una función sin tener que usar variables globales, lo que mejora la encapsulación y evita posibles errores.
