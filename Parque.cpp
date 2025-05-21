#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <queue>





using namespace std;

mutex mtxobjeto;

class Atraccion {
private:
    int capacidad;
    int visitantesActuales = 0;
    int visitantesTotales = 0;
    mutex mtx;
    queue<int> colaEspera;

public:
    Atraccion(int cap) : capacidad(cap) {}

    void visitarAtraccion(string nombre, int cantidad, int duracionMs) {
        unique_lock<mutex> lock(mtx);

        cout << "Grupo de " << cantidad << " quiere entrar a " << nombre << endl;

        if (nombre == "Restaurante") {
            if (cantidad > capacidad) {
                cout << "Grupo de " << cantidad << " es demasiado grande para el restaurante, no pueden entrar." << endl;
                return;
            }

            if (visitantesActuales + cantidad > capacidad) {
                cout << "No hay espacio para grupo de " << cantidad << " en el restaurante, se ponen a esperar." << endl;
                colaEspera.push(cantidad);
                return;
            }

            visitantesActuales += cantidad;
            cout << "Grupo de " << cantidad << " entra a comer en el restaurante." << endl;

            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(duracionMs));
            lock.lock();

            visitantesActuales -= cantidad;
            visitantesTotales += cantidad;
            cout << "Grupo de " << cantidad << " terminó de comer y sale del restaurante." << endl;

            if (!colaEspera.empty()) {
                int siguienteGrupo = colaEspera.front();
                colaEspera.pop();

                lock.unlock();
                visitarAtraccion(nombre, siguienteGrupo, duracionMs);
                lock.lock();
            }

            return;
        }


        int restantes = cantidad;
        while (restantes > 0) {
            int espacioLibre = capacidad - visitantesActuales;

            if (espacioLibre == 0) {
                cout << "No hay espacio en " << nombre << ", grupo de " << restantes << " se pone a esperar." << endl;
                colaEspera.push(restantes);
                return;
            }

            int puedenEntrar = (restantes <= espacioLibre) ? restantes : espacioLibre;

            visitantesActuales += puedenEntrar;
            restantes -= puedenEntrar;

            cout << "Entraron " << puedenEntrar << " personas a " << nombre << ". Actualmente dentro: " << visitantesActuales << endl;

            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(duracionMs));
            lock.lock();

            visitantesActuales -= puedenEntrar;
            visitantesTotales += puedenEntrar;

            cout << "Salieron " << puedenEntrar << " personas de " << nombre << ". Actualmente dentro: " << visitantesActuales << endl;

            if (!colaEspera.empty()) {
                int grupoEspera = colaEspera.front();
                colaEspera.pop();

                lock.unlock();
                visitarAtraccion(nombre, grupoEspera, duracionMs);
                lock.lock();
            }
        }

        cout << "Grupo completado en " << nombre << ". Gracias por su visita." << endl;
    }

    int getTotalAtendidos() const {
        return visitantesTotales;
    }

    int getRestantes() const {
        return visitantesActuales;
    }

    int getColaEspera() {
        return (int)colaEspera.size();
    }
};

class MontanaRusa : public Atraccion {
public:
    MontanaRusa() : Atraccion(15) {}

    void visitarAtraccionM(int cantidad) {
        Atraccion::visitarAtraccion("Montana Rusa", cantidad, 100);
    }
};

class Martillo : public Atraccion {
public:
    Martillo() : Atraccion(10) {}

    void visitarAtraccionA(int cantidad) {
        Atraccion::visitarAtraccion("Martillo", cantidad, 300);
    }
};

class Carrusel : public Atraccion {
public:
    Carrusel() : Atraccion(5) {}

    void visitarAtraccionC(int cantidad) {
        Atraccion::visitarAtraccion("Carrusel", cantidad, 200);
    }
};

class Restaurante : public Atraccion {
public:
    Restaurante() : Atraccion(15) {}

    void visitarAtraccionR(int cantidad) {
        Atraccion::visitarAtraccion("Restaurante", cantidad, 700);
    }
};

class Entrada {
private:
    string nombre;
    int capacidad;
    int visitantesActuales = 0;
    int visitantesTotales = 0;
    mutex mtx;

public:
    Entrada(string nom, int cap) : nombre(nom), capacidad(cap) {}

    void recibirVisitantes(int cantidad) {
        mtx.lock();
        visitantesActuales += cantidad;

        if (visitantesActuales > capacidad) {
            cout << "El numero de personas: " << visitantesActuales << " supera la capacidad de la entrada " << nombre << endl;
        }
        else {
            cout << "Bienvenido al parque de atracciones, acceso por: " << nombre << endl;
        }

        visitantesActuales -= cantidad;
        visitantesTotales += cantidad;
        mtx.unlock();
    }

    int getTotalAtendidos() {
        return visitantesTotales;
    }

    int getRestantes() {
        return visitantesActuales;
    }
};

class Parque {
private:
    Entrada entradaNorte;
    Entrada entradaSur;
    Restaurante restaurante;
    MontanaRusa montanaRusa;
    Martillo martillo;
    Carrusel carrusel;
    string nombre;

public:
    Parque() : nombre("Jacobs Park"), entradaSur("Entrada Sur", 15), entradaNorte("Entrada Norte", 30) {}

    void recibirGrupo(int id, int cantidad) {
        cout << "El grupo: " << id << " por fin despues de una larga travesia ha llegado al parque" << endl;

        int entradaRandom = rand() % 2;
        if (entradaRandom == 0) {
            entradaNorte.recibirVisitantes(cantidad);
        }
        else {
            entradaSur.recibirVisitantes(cantidad);
        }

        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(300));
            int atraccionRandom = rand() % 4;
            switch (atraccionRandom) {
            case 0: restaurante.visitarAtraccionR(cantidad); break;
            case 1: montanaRusa.visitarAtraccionM(cantidad); break;
            case 2: martillo.visitarAtraccionA(cantidad); break;
            case 3: carrusel.visitarAtraccionC(cantidad); break;
            }
        }

        cout << "Gracias por visitar nuestro Parque " << nombre << endl;
    }

    void mostrarEstadisticas() {
        cout << "\n---- ESTADISTICAS FINALES ----" << endl;
        cout << "Visitantes totales atendidos en entradas: "
            << (entradaNorte.getTotalAtendidos() + entradaSur.getTotalAtendidos()) << endl;
        cout << "Visitantes totales en atracciones: "
            << (montanaRusa.getTotalAtendidos() + martillo.getTotalAtendidos() + carrusel.getTotalAtendidos()) << endl;
        cout << "Clientes totales en restaurante: " << restaurante.getTotalAtendidos() << endl;

        cout << "\nVisitantes restantes sin atender:" << endl;
        cout << "Entrada Norte: " << entradaNorte.getRestantes() << endl;
        cout << "Entrada Sur: " << entradaSur.getRestantes() << endl;
        cout << "Montana Rusa: " << montanaRusa.getRestantes() << endl;
        cout << "Martillo: " << martillo.getRestantes() << endl;
        cout << "Carrusel: " << carrusel.getRestantes() << endl;
        cout << "Restaurante: " << restaurante.getRestantes() << endl;
        cout << "Accidentes: 4 " <<endl;
    }
};

int main() {
    cout << "---- SIMULACIÓN DE JACOBS PARK ----" << endl;

    Parque parque;
    vector<thread> grupos;

    grupos.emplace_back(&Parque::recibirGrupo, &parque, 7, 6);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 8, 14);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 9, 3);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 10, 20);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 11, 7);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 12, 18);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 13, 9);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 14, 30);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 15, 11);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 16, 16);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 17, 5);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 18, 8);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 19, 22);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 20, 27);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 21, 13);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 22, 6);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 23, 9);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 24, 17);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 25, 19);
    grupos.emplace_back(&Parque::recibirGrupo, &parque, 26, 21);



    for (auto& g : grupos)
        g.join();

    parque.mostrarEstadisticas();

    return 0;
}
