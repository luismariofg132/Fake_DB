# CRUD en Node.js con almacenamiento en archivo TXT

Este proyecto implementa un sistema de CRUD (Crear, Leer, Actualizar y Eliminar) en Node.js utilizando archivos de texto como base de datos.

## Requisitos

- Node.js instalado en tu sistema

## Instalación y Uso

1. Clona este repositorio o copia el código en un archivo `index.js`.
2. Ejecuta el siguiente comando en la terminal para instalar Node.js si aún no lo tienes:
   ```sh
   npm init -y
   ```
3. Ejecuta el archivo con:
   ```sh
   node index.js
   ```
4. Aparecerá un menú interactivo donde podrás elegir qué acción realizar.

## Funcionalidades

### 1. Crear un aula
Permite registrar una nueva aula con los siguientes datos:
- Código
- Ancho
- Largo
- Capacidad
- Color
- Tipo de aula

### 2. Modificar un aula
Solicita el ID de un aula y permite modificar sus datos.

### 3. Eliminar un aula
Elimina un aula con un ID específico de la base de datos.

### 4. Buscar un aula por ID
Permite obtener la información de un aula ingresando su ID.

### 5. Mostrar todas las aulas
Muestra la lista de todas las aulas almacenadas en el archivo `database.txt`.

### 6. Salir
Cierra la aplicación.

## Estructura del Archivo de Base de Datos
Los datos se almacenan en un archivo `database.txt` en formato JSON, por ejemplo:
```json
[
  {
    "id": 1,
    "codigo": "A101",
    "ancho": 5.5,
    "largo": 7.0,
    "capacidad": 30,
    "color": "Blanco",
    "tipoAula": "Laboratorio"
  }
]
```

## Tecnologías Usadas
- Node.js
- Módulo `fs` para manipulación de archivos
- Módulo `readline` para entrada interactiva por consola
