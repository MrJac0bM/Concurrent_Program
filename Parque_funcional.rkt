#lang racket


;; Muestra mensaje de entrada al parque según la cantidad de personas
(define (mostrar-entrada entrada cantidad)
  (cond
    [(string=? entrada "Norte")
     (if (> cantidad 30)
         (displayln (format "El numero de personas: ~a supera la capacidad de la entrada Norte" cantidad))
         (displayln "Bienvenido al parque de atracciones, acceso por: Entrada Norte"))]
    [else
     (if (> cantidad 15)
         (displayln (format "El numero de personas: ~a supera la capacidad de la entrada Sur" cantidad))
         (displayln "Bienvenido al parque de atracciones, acceso por: Entrada Sur"))]))

;; Simula una visita a una atracción
(define (visitar-atraccion nombre capacidad cantidad duracion)
  (displayln (format "Grupo de ~a quiere entrar a ~a" cantidad nombre))
  (cond
    [(and (string=? nombre "Restaurante") (> cantidad capacidad))
     (displayln (format "Grupo de ~a es demasiado grande para el restaurante, no pueden entrar." cantidad))]
    [(> cantidad capacidad)
     (displayln (format "Entraron ~a personas a ~a (capacidad máxima)" capacidad nombre))
     (displayln (format "Salieron ~a personas de ~a" capacidad nombre))]
    [else
     (displayln (format "Entraron ~a personas a ~a" cantidad nombre))
     (displayln (format "Salieron ~a personas de ~a" cantidad nombre))]))

;; Entrada aleatoria: Norte o Sur
(define (elegir-entrada)
  (if (= (random 2) 0) "Norte" "Sur"))

;; Atracción aleatoria
(define (elegir-atraccion)
  (case (random 4)
    [(0) "Restaurante"]
    [(1) "Montana Rusa"]
    [(2) "Martillo"]
    [else "Carrusel"]))

;; Capacidad según atracción
(define (obtener-capacidad atraccion)
  (cond
    [(string=? atraccion "Restaurante") 15]
    [(string=? atraccion "Montana Rusa") 15]
    [(string=? atraccion "Martillo") 10]
    [(string=? atraccion "Carrusel") 5]
    [else 0]))

;; Duración según atracción
(define (obtener-duracion atraccion)
  (cond
    [(string=? atraccion "Restaurante") 700]
    [(string=? atraccion "Montana Rusa") 100]
    [(string=? atraccion "Martillo") 300]
    [(string=? atraccion "Carrusel") 200]
    [else 0]))


;; Simula una visita a una atracción para un grupo
(define (procesar-visita-atraccion id cantidad)
  (define atraccion (elegir-atraccion))
  (visitar-atraccion atraccion
                     (obtener-capacidad atraccion)
                     cantidad
                     (obtener-duracion atraccion)))

;; Simula 3 visitas consecutivas a atracciones
(define (procesar-tres-atracciones id cantidad n)
  (when (> n 0)
    (procesar-visita-atraccion id cantidad)
    (procesar-tres-atracciones id cantidad (- n 1))))

;; Procesa un grupo completo: entrada + 3 atracciones
(define (procesar-grupo id cantidad)
  (displayln (format "\nEl grupo: ~a por fin despues de una larga travesía ha llegado al parque" id))
  (define entrada (elegir-entrada))
  (mostrar-entrada entrada cantidad)
  (procesar-tres-atracciones id cantidad 3)
  (displayln "Gracias por visitar nuestro Parque Jacobs Park"))


;; Lista de grupos: (id cantidad)
(define grupos-visitantes
  '((7 6) (8 14) (9 3) (10 20) (11 7) (12 18) (13 9) (14 30) (15 11) (16 16)
    (17 5) (18 8) (19 22) (20 27) (21 13) (22 6) (23 9) (24 17) (25 19) (26 21)))

;; Procesa todos los grupos uno por uno
(define (procesar-grupos lista-grupos)
  (cond
    [(null? lista-grupos)
     (displayln "\nTodos los grupos han sido procesados")]
    [else
     (match (car lista-grupos)
       [(list id cantidad)
        (procesar-grupo id cantidad)
        (procesar-grupos (cdr lista-grupos))])]))

;; Suma total de visitantes
(define (calcular-total-visitantes lista-grupos total)
  (cond
    [(null? lista-grupos) total]
    [else
     (match (car lista-grupos)
       [(list _ cantidad)
        (calcular-total-visitantes (cdr lista-grupos) (+ total cantidad))])]))

;; Muestra estadísticas finales
(define (mostrar-estadisticas)
  (define total (calcular-total-visitantes grupos-visitantes 0))
  (displayln "\n---- ESTADÍSTICAS FINALES ----")
  (displayln (format "Total de grupos procesados: ~a" (length grupos-visitantes)))
  (displayln (format "Total de visitantes: ~a" total))
  (displayln (format "Promedio de visitantes por grupo: ~a"
                     (quotient total (length grupos-visitantes))))
  (displayln "Accidentes: 4"))


(define (simular-parque)
  (displayln "---- SIMULACIÓN DE JACOBS PARK ----")
  (procesar-grupos grupos-visitantes)
  (mostrar-estadisticas))

;;Inicializar simulación
(simular-parque)
