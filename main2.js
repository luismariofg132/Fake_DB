const fs = require('fs');
const readline = require('readline');
const filePath = 'database2.txt';
const delimiter = '|'; // Separador de datos en el archivo

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function askQuestion(query) {
    return new Promise(resolve => {
        rl.question(query, answer => resolve(answer));
    });
}

// Crear un nuevo registro de aula
async function createRecord() {
    try {
        const codigo = await askQuestion('Ingrese el código del aula: ');
        const ancho = await askQuestion('Ingrese el ancho del aula: ');
        const largo = await askQuestion('Ingrese el largo del aula: ');
        const capacidad = await askQuestion('Ingrese la capacidad del aula: ');
        const color = await askQuestion('Ingrese el color del aula: ');
        const tipoAula = await askQuestion('Ingrese el tipo de aula: ');

        const db = readDatabase();
        const id = db.length ? db[db.length - 1].id + 1 : 1;
        const record = `${id}${delimiter}${codigo}${delimiter}${ancho}${delimiter}${largo}${delimiter}${capacidad}${delimiter}${color}${delimiter}${tipoAula}`;

        fs.appendFileSync(filePath, record + '\n', 'utf-8');
        console.log('Registro agregado:', record);
    } catch (error) {
        console.error('Error al crear el registro:', error);
    } finally {
        rl.close();
    }
}

// Modificar un aula existente
async function updateRecord() {
    try {
        const id = await askQuestion('Ingrese el ID del aula a modificar: ');
        let db = readDatabase();
        const index = db.findIndex(record => record.id === Number(id));
        if (index === -1) return console.log('Registro no encontrado');

        const codigo = await askQuestion('Ingrese el nuevo código del aula: ');
        const ancho = await askQuestion('Ingrese el nuevo ancho del aula: ');
        const largo = await askQuestion('Ingrese el nuevo largo del aula: ');
        const capacidad = await askQuestion('Ingrese la nueva capacidad del aula: ');
        const color = await askQuestion('Ingrese el nuevo color del aula: ');
        const tipoAula = await askQuestion('Ingrese el nuevo tipo de aula: ');

        db[index] = `${id}${delimiter}${codigo}${delimiter}${ancho}${delimiter}${largo}${delimiter}${capacidad}${delimiter}${color}${delimiter}${tipoAula}`;
        writeDatabase(db);
        console.log('Registro actualizado:', db[index]);
    } catch (error) {
        console.error('Error al actualizar el registro:', error);
    } finally {
        rl.close();
    }
}

// Eliminar un aula por ID
async function deleteRecord() {
    try {
        const id = await askQuestion('Ingrese el ID del aula a eliminar: ');
        let db = readDatabase();
        const newDb = db.filter(record => record.id !== Number(id));
        if (db.length === newDb.length) return console.log('Registro no encontrado');
        writeDatabase(newDb);
        console.log(`Registro con ID ${id} eliminado`);
    } catch (error) {
        console.error('Error al eliminar el registro:', error);
    } finally {
        rl.close();
    }
}

// Buscar un aula por su ID
async function getRecordById() {
    try {
        const id = await askQuestion('Ingrese el ID del aula a buscar: ');
        const db = readDatabase();
        const record = db.find(record => record.id === Number(id));
        console.log(record ? record : 'Registro no encontrado');
    } catch (error) {
        console.error('Error al obtener el registro:', error);
    } finally {
        rl.close();
    }
}

// Leer la base de datos desde el archivo (procesando longitud variable)
function readDatabase() {
    if (!fs.existsSync(filePath)) return [];
    const data = fs.readFileSync(filePath, 'utf-8').trim();
    return data ? data.split('\n').map(line => {
        const [id, codigo, ancho, largo, capacidad, color, tipoAula] = line.split(delimiter);
        return { id: Number(id), codigo, ancho: Number(ancho), largo: Number(largo), capacidad: Number(capacidad), color, tipoAula };
    }) : [];
}

// Escribir la base de datos en el archivo (reemplazando datos)
function writeDatabase(data) {
    fs.writeFileSync(filePath, data.join('\n') + '\n', 'utf-8');
}

// Menú principal para seleccionar operaciones CRUD
async function mainMenu() {
    console.log('\nSeleccione una opción:');
    console.log('1. Crear un aula');
    console.log('2. Modificar un aula');
    console.log('3. Eliminar un aula');
    console.log('4. Buscar un aula por ID');
    console.log('5. Mostrar todas las aulas');
    console.log('6. Salir');

    const option = await askQuestion('Ingrese el número de la opción: ');

    switch (option) {
        case '1':
            await createRecord();
            break;
        case '2':
            await updateRecord();
            break;
        case '3':
            await deleteRecord();
            break;
        case '4':
            await getRecordById();
            break;
        case '5':
            console.log(readDatabase());
            rl.close();
            break;
        case '6':
            rl.close();
            break;
        default:
            console.log('Opción no válida');
            rl.close();
            break;
    }
}

// Iniciar el menú principal
mainMenu();

