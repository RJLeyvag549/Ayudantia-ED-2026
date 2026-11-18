# Ejemplos con SFML

Ejemplos separados para crear ventanas, dibujar figuras, mover un objeto y
mostrar un mapa.

## Requisitos

Se necesita `g++` y SFML 2.x.

## Compilar

Compila un archivo por vez. Por ejemplo:

```bash
g++ movimiento.cpp -o movimiento -lsfml-graphics -lsfml-window -lsfml-system
./movimiento
```

`figuras.cpp` usa `DejaVuSans-Bold.ttf` y `sans.png`. Ejecuta ese programa
desde esta carpeta para que pueda encontrar esos archivos.

