# SimulacionFisicaVideojuegos
Repositorio de las prácticas de la asignatura de Simulación Física de Videojuegos

En la carpeta skeleton estará vuestro código fuente

Necesitaréis además descomprimir el archivo que se indica a continuación en la raíz del repositorio:

Carpetas bin y common https://ucomplutense-my.sharepoint.com/:f:/g/personal/liagar05_ucm_es/ElNxHPmZVj9Ni9-8FKTKp7cBJHAarnL3vvEvG50z0QMrzg

---

# Controles del Juego

Este documento describe todas las teclas de entrada disponibles en el proyecto de simulación física y videojuegos. Los controles varían según la escena activa. Usa las teclas para interactuar con el juego, mover al jugador, activar efectos y navegar entre escenas.

## Navegación General
- **G / g**: Regresar al menú principal desde cualquier escena.

## GameScene (Escena Principal del Juego)
En esta escena, controlas al jugador (un cuerpo rígido) en un entorno con vientos, obstáculos y explosiones. El objetivo es llegar al final del nivel.

- **A / a**: Mover al jugador hacia la izquierda (aplica fuerza lateral negativa).
- **D / d**: Mover al jugador hacia la derecha (aplica fuerza lateral positiva).
- **W / w**: Activar/desactivar la zona de viento 0 (primer viento horizontal).
- **E / e**: Activar/desactivar la zona de viento 1 (segundo viento horizontal).
- **R / r**: Activar/desactivar la zona de viento 2 (tercer viento horizontal).
- **T / t**: Activar/desactivar la zona de viento 3 (cuarto viento horizontal).
- **Y / y**: Crear una explosión manual en la posición del jugador (genera partículas y fuerza radial).

### Notas Adicionales en GameScene:
- El jugador se mueve automáticamente con la gravedad y los vientos activos.
- Las explosiones afectan al movimiento del jugador.
- Si sales de los límites laterales, vas a Game Over. Si caes demasiado bajo, también Game Over. Alcanzar el marcador rojo lleva a la escena de victoria.

## Scene6 (Escena de Partículas y Resortes)
Escena de demostración con partículas conectadas por resortes y cuerpos rígidos.

- **P / p**: Generar cuerpos rígidos aleatorios en la escena (usando UniformRigidGen).
- **G / g**: Regresar al menú principal.

### Notas Adicionales en Scene6:
- Los cuerpos rígidos caen con gravedad y colisionan.
- Incluye resortes entre partículas para simular conexiones elásticas.

## Scene7 (Escena de Cuerpos Rígidos)
Escena de demostración con generación masiva de cuerpos rígidos.

- **P / p**: Generar cuerpos rígidos aleatorios en la escena (usando UniformRigidGen).
- **G / g**: Regresar al menú principal.

### Notas Adicionales en Scene7:
- Similar a Scene6, pero enfocada en simulación de PhysX con múltiples cuerpos rígidos.
- Los cuerpos tienen vida útil limitada y se eliminan automáticamente.

## Otras Escenas
- **StartScene / Main Menu / WinScene / GameOverScene**:
- **G / g**: Regresar al menú principal.
- **P / p**: Para iniciar el juego.

## Instrucciones Generales
- Presiona las teclas en minúscula o mayúscula (ambas funcionan).
- Para salir del programa, cierra la ventana o usa el menú del sistema.
