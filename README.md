# Concurrent_Program
#  Simulación Concurrente de Parque de Atracciones

## 1. Introducción

Este sistema simula el funcionamiento concurrente de un parque de atracciones donde múltiples grupos de visitantes acceden a diferentes atracciones de forma simultánea. El objetivo es gestionar de forma correcta el funcionamiento del sistema

-  **Seguridad**: Ninguna atracción supera su capacidad máxima.  
-  **Equidad**: Los grupos en espera acceden en orden de llegada  
-  **Eficiencia**: Minimizar tiempos de espera y maximizar uso de recursos.

El modelo utiliza programación concurrente en C++ con hilos, mutex y colas de espera para resolver problemas típicos de sistemas de tiempo real como:

- Condiciones de carrera  
- Sincronización entre procesos  
- Gestión de recursos compartidos  

---

## 2. Estructura General del Sistema

### 2.1 Componentes Principales

- **Entradas**: Dos accesos al parque con capacidades distintas.  
- **Atracciones**:
  -  Montana Rusa (capacidad: 15 personas)
  -  Martillo (capacidad: 10 personas)
  -  Carrusel (capacidad: 5 personas)
  -  Restaurante (capacidad: 15 personas)  
- **Grupos de Visitantes**: Representados como hilos que realizan 3 actividades aleatorias.

### 2.2 Flujo de Operación

1. Los grupos llegan al parque y eligen una entrada aleatoria.  
2. Visitan 3 atracciones en orden aleatorio.  
3. Si una atracción está llena, esperan en cola hasta que haya espacio.

---

## 3. Paradigma de Concurrencia

### 3.1 Modelo Basado en Mutex y Colas

- **Mutex**: Protegen el acceso a variables compartidas (contadores, colas).
- **Colas de Espera**: Almacenan grupos que no pueden entrar inmediatamente.
- **Hilos Independientes**: Cada grupo es un hilo paralelo con lógica propia.


### 3.2 Políticas Clave

- **Gestión de Grupos Grandes**:  
  Si un grupo excede la capacidad de una atracción, se divide en lotes.    
  Los primeros en llegar son los primeros en ser atendidos.

---

## 4.  Prácticas Implementadas

### 4.1 Seguridad en Concurrencia

- **RAII para Mutex**: Uso de unique_lock para liberar automáticamente.
- **Variables Atómicas**: Protegen contadores de accesos simultáneos.
- **Encapsulamiento**: Cada atracción maneja su propia lógica interna.

### 4.2 Eficiencia

- **Tiempos de Simulación**:
  - Restaurante: 700 ms
  - Montana Rusa: 100 ms

- **Desbloqueo durante esperas**:  
  Los hilos liberan mutex mientras duermen (sleep_for).

---

## 5. Complejidad Computacional

### 5.1 Tiempo

Por Grupo:

- Entrada: O(1)  
- Atracciones: O(k), donde k = 3 (actividades fijas por grupo)  
- Esperas: O(n) en el peor caso (grupos en cola)  

**Total**: O(m * n) para m grupos y n atracciones

### 5.2 Espacio

- **Hilos**: 1 por grupo (ejemplo: 20 grupos → 20 hilos)
- **Colas**: Dependen de los grupos en espera 

---



## 7. Pruebas y Validación

### 7.1 Casos de Prueba

- **Grupo Excede Capacidad**  
  Enviar grupo de 20 al Restaurante (capacidad 15)  
  Resultado: 15 entran, 5 esperan


- **Uso Concurrente Máximo**  
  10 grupos acceden simultáneamente a Montana Rusa  
  Resultado : 15 personas en la atracción

### 7.2 Métricas de Validación

- Total atendidos = Suma de todos los grupos   
- Restantes en colas = 0 al finalizar

---

## 8. Resultados y Estadísticas

### 8.1 Ejecución de Ejemplo

---- SIMULACIÓN DE JACOBS PARK ----  
Grupo 7 entra por Entrada Norte  
Grupo de 6 quiere entrar a Montana Rusa  
Salieron 6 personas de Montana Rusa  
...  
---- ESTADÍSTICAS FINALES ----  
Visitantes totales atendidos: 450  
Clientes en restaurante: 150  


---


## 9. Bibliografía

- Dijkstra, E. W. (1965). *Solution of a problem in concurrent programming control*. Communications of the ACM.  
  - Fundamento teórico para la exclusión mutua mediante mutex.

- Hoare, C. A. R. (1978). *Communicating sequential processes*. Communications of the ACM.  
  - Base conceptual para la comunicación y sincronización entre procesos concurrentes.

- Williams, A. (2019). *C++ Concurrency in Action* (2nd ed.). Manning Publications.  
  - Guía práctica sobre programación concurrente moderna en C++ usando `std::thread`, `std::mutex` y RAII.

