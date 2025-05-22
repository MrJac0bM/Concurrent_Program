
#  Simulación Concurrente de Parque de Atracciones

## Introducción

Este sistema simula el funcionamiento concurrente de un parque de atracciones donde múltiples grupos de visitantes acceden a diferentes atracciones de forma simultánea. El objetivo es gestionar de forma correcta el funcionamiento del sistema

-  **Seguridad**: Ninguna atracción supera su capacidad máxima.  
-  **Equidad**: Los grupos en espera acceden en orden de llegada  
-  **Eficiencia**: Minimizar tiempos de espera y maximizar uso de recursos.

El modelo utiliza programación concurrente en C++ con hilos, mutex y colas de espera para resolver problemas típicos de sistemas de tiempo real como:

- Condiciones de carrera  
- Sincronización entre procesos  
- Gestión de recursos compartidos

## Paradigma de Concurrencia

El sistema sigue un modelo de concurrencia mediante **hilos (multi-threading)** donde:

- Cada **grupo de visitantes** es un **hilo independiente** que ejecuta su flujo.

- Las **atracciones** son recursos compartidos protegidos por mecanismos de sincronización:

  - **Mutex (`std::mutex`)**:  
    Garantizan exclusión mutua al modificar estados compartidos (por ejemplo, contadores de capacidad).

  - **Colas de espera (`std::queue`)**:  
    Implementan política de espera ordenada para grupos en atracciones llenas.


---

##  Estructura General del Sistema

###  Componentes Principales

- **Entradas**: Dos accesos al parque con capacidades distintas.  
- **Atracciones**:
  -  Montana Rusa (capacidad: 15 personas)
  -  Martillo (capacidad: 10 personas)
  -  Carrusel (capacidad: 5 personas)
  -  Restaurante (capacidad: 15 personas)  
- **Grupos de Visitantes**: Representados como hilos que realizan 3 actividades aleatorias.

###  Flujo de Operación

1. Los grupos llegan al parque y eligen una entrada aleatoria.  
2. Visitan 3 atracciones en orden aleatorio.  
3. Si una atracción está llena, esperan en cola hasta que haya espacio.

---

##  Paradigma de Concurrencia

###  Modelo Basado en Mutex y Colas

- **Mutex**: Protegen el acceso a variables compartidas (contadores, colas).
- **Colas de Espera**: Almacenan grupos que no pueden entrar inmediatamente.
- **Hilos Independientes**: Cada grupo es un hilo paralelo con lógica propia.


###  Políticas Clave

- **Gestión de Grupos Grandes**:  
  Si un grupo excede la capacidad de una atracción, se divide en lotes.    
  Los primeros en llegar son los primeros en ser atendidos.

---

##  Prácticas Implementadas

###  Seguridad en Concurrencia

- **RAII para Mutex**: Uso de unique_lock para liberar automáticamente.
- **Variables Atómicas**: Protegen contadores de accesos simultáneos.
- **Encapsulamiento**: Cada atracción maneja su propia lógica interna.
---

## 5. Complejidad Computacional

###  Tiempo

Por Grupo:

- Entrada: O(1)  
- Atracciones: O(k), donde k = 3 (actividades fijas por grupo)  
- Esperas: O(n) en el peor caso (grupos en cola)  

**Total**: O(m * n) para m grupos y n atracciones

###  Espacio

- **Hilos**: O(n) 1 por grupo (ejemplo: 20 grupos → 20 hilos)
- **Colas**: O(n) Dependen de los grupos en espera 

---



## Pruebas y Validación

### Casos de Prueba

- **Grupo Excede Capacidad**  
  Enviar grupo de 20 al Restaurante (capacidad 15)  
  Resultado: 15 entran, 5 esperan


- **Uso Concurrente Máximo**  
  10 grupos acceden simultáneamente a Montana Rusa  
  Resultado : 15 personas en la atracción

###  Métricas de Validación

- Total atendidos = Suma de todos los grupos   
- Restantes en colas = 0 al finalizar




##  Bibliografía

- Dijkstra, E. W. (1965). *Solution of a problem in concurrent programming control*. Communications of the ACM.  

- Hoare, C. A. R. (1978). *Communicating sequential processes*. Communications of the ACM.  
- Williams, A. (2019). *C++ Concurrency in Action* (2nd ed.). Manning Publications.  


