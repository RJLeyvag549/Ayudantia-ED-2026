#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct PokemonStats {
    int id;
    string nombre;
    string tipo1;
    string tipo2;
    int total;
    int hp;
    int ataque;
    int defensa;
    int ataqueEsp;
    int defensaEsp;
    int velocidad;
    int generacion;
    bool legendario;
};

void limpiarString(string& s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' ')) {
        s.pop_back();
    }
}

bool idYaExiste(const vector<int>& ids, int idBuscado) {
    for (int idActual : ids) {
        if (idActual == idBuscado) {
            return true;
        }
    }
    return false;
}

vector<PokemonStats> cargarPokemonStatsCSV(const string& rutaArchivo) {
    vector<PokemonStats> lista;
    vector<int> idsCargados;

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
        return lista;
    }
    string linea;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;
        PokemonStats p;

        getline(ss, campo, ',');
        if (idYaExiste(idsCargados, stoi(campo))) {
            continue;
        }
        idsCargados.push_back(p.id);
        p.id = stoi(campo);

        getline(ss, p.nombre, ',');
        getline(ss, p.tipo1, ',');
        getline(ss, p.tipo2, ',');
        getline(ss, campo, ',');
        p.total = stoi(campo);
        getline(ss, campo, ',');
        p.hp = stoi(campo);
        getline(ss, campo, ',');
        p.ataque = stoi(campo);
        getline(ss, campo, ',');
        p.defensa = stoi(campo);
        getline(ss, campo, ',');
        p.ataqueEsp = stoi(campo);
        getline(ss, campo, ',');
        p.defensaEsp = stoi(campo);
        getline(ss, campo, ',');
        p.velocidad = stoi(campo);
        getline(ss, campo, ',');
        p.generacion = stoi(campo);
        getline(ss, campo, ',');
        limpiarString(campo);
        p.legendario = (campo == "True" || campo == "true" || campo == "1");
        limpiarString(p.nombre);
        limpiarString(p.tipo1);
        limpiarString(p.tipo2);
        lista.push_back(p);
    }
    archivo.close();
    return lista;
}

void guardarPokemonCSV(const string& rutaArchivo, const vector<PokemonStats>& lista) {
    ofstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo " << rutaArchivo << endl;
        return;
    }
    archivo << "#,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary" << endl;
    for (const auto& p : lista) {
        archivo << p.id << "," << p.nombre << "," << p.tipo1 << "," << p.tipo2 << ","
                << p.total << "," << p.hp << "," << p.ataque << "," << p.defensa << ","
                << p.ataqueEsp << "," << p.defensaEsp << "," << p.velocidad << ","
                << p.generacion << "," << (p.legendario ? "True" : "False") << endl;
    }

    archivo.close();
    cout << "Archivo " << rutaArchivo << " guardado exitosamente con " << lista.size() << " registros." << endl;
}

void buscarTopAtaque(const vector<PokemonStats>& lista) {
    cout << "\n--- Top Pokemon con Mayor Ataque Fisico ---" << endl;
    if (lista.empty()) return;

    int maxAtaque = 0;
    for (const auto& p : lista) {
        if (p.ataque > maxAtaque) maxAtaque = p.ataque;
    }

    for (const auto& p : lista) {
        if (p.ataque == maxAtaque) {
            cout << "- " << p.nombre << " | Ataque: " << p.ataque << " | Total: " << p.total << endl;
        }
    }
}

void procesarLegendarios(const vector<PokemonStats>& lista) {
    cout << "\n--- Procesando Pokemon Legendarios ---" << endl;
    vector<PokemonStats> legendarios;

    for (const auto& p : lista) {
        if (p.legendario) {
            legendarios.push_back(p);
        }
    }

    cout << "Total de Pokemon Legendarios: " << legendarios.size() << endl;
    cout << "Muestra de los primeros 5 legendarios:" << endl;
    for (size_t i = 0; i < 5 && i < legendarios.size(); i++) {
        cout << "- " << legendarios[i].nombre << " [" << legendarios[i].tipo1 << "] Total: " << legendarios[i].total << endl;
    }
    guardarPokemonCSV("pokemon_legendarios.csv", legendarios);
}

void filtrarTanquesDefensivos(const vector<PokemonStats>& lista) {
    cout << "\n--- Pokemon Tanques Defensivos (Defensa >= 130) ---" << endl;
    vector<PokemonStats> tanques;

    for (const auto& p : lista) {
        if (p.defensa >= 130) {
            cout << "- " << p.nombre << " | Defensa: " << p.defensa << " | HP: " << p.hp << endl;
            tanques.push_back(p);
        }
    }
    cout << "Total de Tanques Defensivos: " << tanques.size() << endl;
}

void promedioPorGeneracion(const vector<PokemonStats>& lista) {
    cout << "\n--- Promedio de Stats Totales por Generacion ---" << endl;
    for (int gen = 1; gen <= 6; gen++) {
        int sumaTotal = 0;
        int contador = 0;

        for (const auto& p : lista) {
            if (p.generacion == gen) {
                sumaTotal += p.total;
                contador++;
            }
        }

        if (contador > 0) {
            double promedio = static_cast<double>(sumaTotal) / contador;
            cout << "Generacion " << gen << ": " << contador << " Pokemon | Promedio Total: " << promedio << endl;
        }
    }
}

void mostrarResumen(const vector<PokemonStats>& lista) {
    int conDobleTipo = 0;
    int sumaTotalStats = 0;

    for (const auto& p : lista) {
        if (!p.tipo2.empty()) conDobleTipo++;
        sumaTotalStats += p.total;
    }

    double promedioGeneral = static_cast<double>(sumaTotalStats) / lista.size();

    cout << "\n==========================================" << endl;
    cout << "=== RESUMEN GENERAL DE POKEMON_STATS ===" << endl;
    cout << "==========================================" << endl;
    cout << "Total de registros cargados: " << lista.size() << endl;
    cout << "Pokemon con doble tipo: " << conDobleTipo << endl;
    cout << "Promedio general de Stats Totales: " << promedioGeneral << endl;
}

int main() {
    string rutaCSV = "Pokemon_stats.csv";

    cout << "Cargando archivo " << rutaCSV << "..." << endl;
    vector<PokemonStats> pokedex = cargarPokemonStatsCSV(rutaCSV);

    if (pokedex.empty()) {
        cout << "No se pudieron cargar los datos." << endl;
        return 1;
    }

    cout << "Se cargaron exitosamente " << pokedex.size() << " Pokemon." << endl;

    mostrarResumen(pokedex);
    buscarTopAtaque(pokedex);
    filtrarTanquesDefensivos(pokedex);
    promedioPorGeneracion(pokedex);
    procesarLegendarios(pokedex);

    return 0;
}
