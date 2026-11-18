#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_CATALOGO  = 110;
const int MAX_INVENTARIO = 27;

struct ItemCatalogo {
    int id;
    string nombre;       // Nombre en inglés
    string nombre_es;    // Nombre en español
    string categoria;    // bloque, material, arma, herramienta, comida
    string rareza;       // comun, raro, epico
    int apilable;        // 1, 16 o 64
};

struct SlotInventario {
    int  id_item;
    string nombre_es;
    string nombre;
    string categoria;
    string rareza;
    int  cantidad;
};

void limpiarString(string& s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' ')) {
        s.pop_back();
    }
}

int cargarCatalogo(const string& archivo, ItemCatalogo* catalogo) {
    ifstream f(archivo);
    if (!f.is_open()) {
        cout << "Error: No se pudo abrir " << archivo << endl;
        return 0;
    }
    string linea;
    getline(f, linea); // Saltar encabezado
    int count = 0;
    while (getline(f, linea) && count < MAX_CATALOGO) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string campo;
        ItemCatalogo item;

        getline(ss, campo, ','); limpiarString(campo); item.id = stoi(campo);
        getline(ss, item.nombre, ','); limpiarString(item.nombre);
        getline(ss, item.nombre_es, ','); limpiarString(item.nombre_es);
        getline(ss, item.categoria, ','); limpiarString(item.categoria);
        getline(ss, item.rareza, ','); limpiarString(item.rareza);
        getline(ss, campo, ','); item.apilable = stoi(campo);

        catalogo[count++] = item;
    }
    f.close();
    return count;
}

bool cargarInventario(const string& archivo, SlotInventario* inventario, int& totalInventario) {
    ifstream f(archivo);
    if (!f.is_open()) return false;

    string linea;
    getline(f, linea); // Saltar encabezado
    int count = 0;
    while (getline(f, linea) && count < MAX_INVENTARIO) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string campo;
        SlotInventario s;

        getline(ss, campo, ','); // slot (se reasigna al guardar, se ignora al leer)
        getline(ss, campo, ','); limpiarString(campo); s.id_item = stoi(campo);
        getline(ss, s.nombre_es, ','); limpiarString(s.nombre_es);
        getline(ss, s.nombre, ','); limpiarString(s.nombre);
        getline(ss, s.categoria, ','); limpiarString(s.categoria);
        getline(ss, s.rareza, ','); limpiarString(s.rareza);
        getline(ss, campo, ','); limpiarString(campo); s.cantidad = stoi(campo);

        inventario[count++] = s;
    }
    f.close();
    totalInventario = count;
    return true;
}

void guardarInventario(const string& archivo, const SlotInventario* inventario, int totalInventario) {
    ofstream f(archivo);
    f << "slot,id,nombre_es,nombre,categoria,rareza,cantidad\n";
    for (int i = 0; i < totalInventario; i++) {
        f << (i + 1)                  << ","
          << inventario[i].id_item    << ","
          << inventario[i].nombre_es  << ","
          << inventario[i].nombre     << ","
          << inventario[i].categoria  << ","
          << inventario[i].rareza     << ","
          << inventario[i].cantidad   << endl;
    }
    f.close();
    cout << "Inventario guardado en " << archivo << endl;
}

int buscarEnCatalogo(int id, const ItemCatalogo* catalogo, int totalCatalogo) {
    for (int i = 0; i < totalCatalogo; i++) {
        if (catalogo[i].id == id) return i;
    }
    return -1;
}

int seleccionarCategoria(const char* const* categorias, int numCategorias) {
    cout << "\n--- Filtrar por categoria ---\n";
    cout << "0. Todas" << endl;
    for (int i = 0; i < numCategorias; i++) {
        cout << (i + 1) << ". " << categorias[i] << endl;
    }
    int op = -1;
    while (op < 0 || op > numCategorias) {
        cout << "Seleccion: ";
        cin >> op;
        if (op < 0 || op > numCategorias)
            cout << "Opcion invalida. Intente de nuevo." << endl;
    }
    return op;
}

void mostrarCatalogo(int filtro, const ItemCatalogo* catalogo, int totalCatalogo,
                     const char* const* categorias) {
    cout << "\n";
    cout << "ID | Nombre (ES) | Nombre (EN) | Categoria | Rareza | Apilable\n";
    cout << string(100, '-') << "\n";

    int encontrados = 0;
    for (int i = 0; i < totalCatalogo; i++) {
        bool mostrar = (filtro == 0) ||
                       (catalogo[i].categoria == categorias[filtro - 1]);
        if (mostrar) {
            cout << catalogo[i].id << " | "
                 << catalogo[i].nombre_es << " | "
                 << catalogo[i].nombre << " | "
                 << catalogo[i].categoria << " | "
                 << catalogo[i].rareza << " | "
                 << catalogo[i].apilable << "\n";
            encontrados++;
        }
    }
    if (encontrados == 0)
        cout << "(Sin resultados para esta categoria)" << endl;
    cout << encontrados << " items mostrados" << endl;
}

void verCatalogo(const ItemCatalogo* catalogo, int totalCatalogo,
                 const char* const* categorias, int numCategorias) {
    int filtro = seleccionarCategoria(categorias, numCategorias);
    mostrarCatalogo(filtro, catalogo, totalCatalogo, categorias);
}

void verInventario(const SlotInventario* inventario, int totalInventario) {
    if (totalInventario == 0) {
        cout << "\nInventario vacio.\n";
        return;
    }
    cout << "\n--- INVENTARIO (" << totalInventario << "/27 slots) ---\n";
    cout << "Slot | ID | Nombre (ES) | Nombre (EN) | Categoria | Rareza | Cantidad\n";
    cout << string(105, '-') << "\n";
    for (int i = 0; i < totalInventario; i++) {
                cout << i + 1 << " | "
                         << inventario[i].id_item << " | "
                         << inventario[i].nombre_es << " | "
                         << inventario[i].nombre << " | "
                         << inventario[i].categoria << " | "
                         << inventario[i].rareza << " | "
                         << inventario[i].cantidad << endl;
    }
}

void insertarItem(ItemCatalogo* catalogo, int totalCatalogo,
                  SlotInventario* inventario, int& totalInventario,
                  const char* const* categorias, int numCategorias) {
    if (totalInventario >= MAX_INVENTARIO) {
        cout << "\nInventario lleno (27/27 slots). Elimina un item antes de insertar" << endl;
        return;
    }

    // Mostrar catálogo filtrado para elegir
    int filtro = seleccionarCategoria(categorias, numCategorias);
    mostrarCatalogo(filtro, catalogo, totalCatalogo, categorias);

    cout << "\nIngrese el ID del item a insertar (0 para cancelar): ";
    int id;
    cin >> id;
    if (id == 0) return;

    int idx = buscarEnCatalogo(id, catalogo, totalCatalogo);
    if (idx == -1) {
        cout << "ID " << id << " no encontrado en el catalogo" << endl;
        return;
    }

    ItemCatalogo& item = catalogo[idx];
    int cantidad = 1;

    if (item.apilable > 1) {
        cout << "Cantidad a ingresar (1 - " << item.apilable << "): ";
        cin >> cantidad;
        if (cantidad < 1 || cantidad > item.apilable) {
            cout << "Cantidad invalida (debe ser entre 1 y " << item.apilable << "). Operacion cancelada" << endl;
            return;
        }
    }

    SlotInventario& nuevo = inventario[totalInventario];
    nuevo.id_item = item.id;
    nuevo.nombre_es = item.nombre_es;
    nuevo.nombre = item.nombre;
    nuevo.categoria = item.categoria;
    nuevo.rareza = item.rareza;
    nuevo.cantidad = cantidad;
    totalInventario++;

    cout << "[+] Agregado: " << item.nombre_es
         << " x" << cantidad
         << " --> Slot " << totalInventario << endl;
}

void eliminarItem(SlotInventario* inventario, int& totalInventario) {
    if (totalInventario == 0) {
        cout << "\nInventario vacio. No hay items que eliminar" << endl;
        return;
    }

    verInventario(inventario, totalInventario);

    int slot = -1;
    while (slot < 0 || slot > totalInventario) {
        cout << "\nIngrese el numero de slot a eliminar (0 para cancelar): ";
        cin >> slot;
        if (slot == 0) return;
        if (slot < 1 || slot > totalInventario)
            cout << "Slot invalido. Debe ser entre 1 y " << totalInventario << endl;
    }

    cout << "[-] Eliminado: " << inventario[slot - 1].nombre_es
         << " x" << inventario[slot - 1].cantidad
         << " (Slot " << slot << ")\n";

    // Compactar: desplazar elementos hacia arriba
    for (int i = slot - 1; i < totalInventario - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    totalInventario--;
    cout << "Slots restantes: " << totalInventario << "/27" << endl;
}

int main() {
    ItemCatalogo catalogo[MAX_CATALOGO];
    SlotInventario inventario[MAX_INVENTARIO];
    const char* categorias[] = {"bloque", "material", "arma", "herramienta", "comida"};
    const int numCategorias = 5;
    int totalCatalogo = cargarCatalogo("catalogo_minecraft_100_es.csv", catalogo);
    int totalInventario = 0;
    if (totalCatalogo == 0) {
        cout << "No se pudo cargar el catalogo. Saliendo." << endl;
        return 1;
    }
    cout << "Catalogo cargado: " << totalCatalogo << " items." << endl;

    if (cargarInventario("inventario.csv", inventario, totalInventario)) {
        cout << "Inventario cargado: " << totalInventario << " items." << endl;
    } else {
        cout << "Sin inventario previo. Comenzando vacio." << endl;
    }

    int opcion = 0;
    while (opcion != 5) {
        cout << "\n==============================\n";
        cout << "  INVENTARIO MINECRAFT\n";
        cout << "  Slots: " << totalInventario << "/27\n";
        cout << "==============================\n";
        cout << "1. Ver catalogo\n";
        cout << "2. Insertar item\n";
        cout << "3. Ver inventario\n";
        cout << "4. Eliminar item\n";
        cout << "5. Guardar y salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: verCatalogo(catalogo, totalCatalogo, categorias, numCategorias);  break;
            case 2: insertarItem(catalogo, totalCatalogo, inventario, totalInventario,
                                 categorias, numCategorias); break;
            case 3: verInventario(inventario, totalInventario); break;
            case 4: eliminarItem(inventario, totalInventario); break;
            case 5:
                guardarInventario("inventario.csv", inventario, totalInventario);
                cout << "Chao pescao!\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    }

    return 0;
}
