
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





##  Prácticas Implementadas

###  Seguridad en Concurrencia

- **RAII para Mutex**: Uso de unique_lock para liberar automáticamente.
- **Variables Atómicas**: Protegen contadores de accesos simultáneos.
- **Encapsulamiento**: Cada atracción maneja su propia lógica interna.


## Diagrama de concurrencia del flujo de grupos en el parque temático
![image](https://github.com/user-attachments/assets/dff4e075-45ab-4ec0-878a-9ef20c65bbe6)


## UML 
![image](https://github.com/user-attachments/assets/c6410a56-23fd-4bb4-bd8a-3681e5c6dc90)



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



# Simulación de Parque de Atracciones en Racket

Este sistema simula el funcionamiento de un parque de atracciones utilizando **programación funcional pura en Racket**. A diferencia del modelo concurrente en C++, esta implementación resuelve el problema mediante:

- **Composición de funciones puras** (sin efectos secundarios).
- **Recursión** para manejar flujos iterativos.
- **Inmutabilidad de datos** (ningún estado es modificado).

## Objetivos principales

- **Seguridad**: Las atracciones nunca exceden su capacidad (validación estática).
- **Determinismo**: Misma entrada → misma salida siempre.
- **Simplicidad**: Evitar complejidad de sincronización.

##  Paradigma Funcional

### Principios Clave

- **Inmutabilidad**:

```racket
(define grupos-visitantes '((7 6) (8 14) ...)) ;; Lista fija
```
- **Inmutabilidad**:
  ``` racket
  (define (procesar-grupos lista)
  (when (not (null? lista))
    (procesar-grupo (car lista))
    (procesar-grupos (cdr lista))))
  ```
- **Funciones puras**:
  ``` racket
  (define (obtener-capacidad atraccion) ;; Sin efectos secundarios
  (cond [(string=? atraccion "Restaurante") 15]
        ...))
  ```

  ###  Ventajas del Enfoque
  - **Transparencia referencial**: Las funciones siempre producen el mismo resultado para los mismos inputs.
  - **Ausencia de estados compartidos**: Elimina riesgos de condiciones de carrera.
  - **Facilidad de prueba**: Flujo completamente determinista.

##  Complejidad Computacional

###  Análisis Temporal

- **Por grupo**:
  - Entrada: O(1)
  - Atracciones: O(3) → 3 visitas fijas

- **Total**: O(n) para *n* grupos (procesamiento secuencial)

### Análisis Espacial

- **Memoria**:
  - Lista de grupos: O(n)
  - Pila de recursión: O(n) (máxima profundidad = número de grupos)


## Pruebas y Validación

### Casos de Prueba

# Casos de Prueba

## 1. Acceso concurrente a una atracción con capacidad limitada
- **Configuración:** 10 visitantes, 1 atracción (Montaña Rusa, capacidad 1)  
- **Esperado:** Solo un visitante entra a la vez; los demás esperan su turno.  
- **Validación:** No hay condiciones de carrera ni superposición de accesos.
  ![image](https://github.com/user-attachments/assets/d658b7ef-2918-4860-b77d-01dcd0768058)


---

## 2. Exceso de visitantes sobre la capacidad total
- **Configuración:** 50 visitantes, 2 atracciones (Casa del Terror, Martillo, ambas con capacidad 1)  
- **Esperado:** Las atracciones procesan a todos los visitantes uno por uno, sin bloqueos.  
- **Validación:** Todos los hilos completan su ejecución sin errores ni bloqueos.

  ![image](https://github.com/user-attachments/assets/e873fff9-43ad-4120-ac77-83b3ac3e2ce2)


---

## 3. Duraciones distintas por atracción
- **Configuración:** Montaña Rusa (3s), Restaurante (5s), 6 visitantes  
- **Esperado:** Las atracciones gestionan tiempos correctamente; los visitantes salen según su duración.  

---

## 4. Distribución balanceada entre múltiples atracciones
- **Configuración:** 12 visitantes, 3 atracciones (Montaña Rusa, Martillo, Restaurante)  
- **Esperado:** Los visitantes se distribuyen entre atracciones sin colisiones.  
- **Validación:** Se observa concurrencia efectiva y sin conflicto en el acceso.

---

## 5. Terminación limpia del sistema
- **Configuración:** 20 visitantes, 3 atracciones  
- **Esperado:** Todos los hilos finalizan correctamente.  
- **Validación:** No se detectan hilos colgados, ni fugas de memoria.
![image](https://github.com/user-attachments/assets/a0fdeacb-06b0-4ca4-a760-a759ccc6808f)



### Métricas de Validación
- **Total atendidos**: Suma de todos los grupos procesados.
- **Consistencia**: Mismas entradas generan mismas salidas.

## Comparación Paradigmas

| Aspecto             | Versión Funcional (Racket) | Versión Concurrente (C++)        |
|---------------------|-----------------------------|-----------------------------------|
| **Estado**          | Inmutable                   | Mutable                           |
| **Orden de ejecución** | Determinista             | No determinista                   |
| **Paralelismo**     | Secuencial                  | Simultaneo                         |
| **Gestión de errores** | Validación estática      | En tiempo de ejecución             |
| **Complejidad**     | Lineal O(n)                 | Concurrente O(m·n)                   |





## Bibliografía Funcional

- **Abelson, H.** (1996). *Structure and Interpretation of Computer Programs*. MIT Press.  
  *Fundamentos de programación funcional.*

- **Felleisen, M.** (2018). *A Programmer's Guide to Racket*.  
  *Estilo y mejores prácticas en Racket.*

- **Hughes, J.** (1989). *Why Functional Programming Matters*.  
  *Ventajas de la composición funcional.*
