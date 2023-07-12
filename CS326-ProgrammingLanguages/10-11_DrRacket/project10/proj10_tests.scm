#lang racket

; -----
; Evalate the following Scheme expressions.
(display "\nScheme Expressions\n")
(+ 1 2)
(+ 1 2 3 4 5)
(+ (* 2 3) (* 4 5))
(+ (* 9 4) (/ 15 3))
(- (* (+ 11 8) 3 4) 5)
(* (- (+ (+ 4 7) 2) 3) 2)
(+ 1 (/ (- 2 3) (* 4 5)))
(+ 1 0.5)
(define (f x)
(+ (* x x) (* x x x) ) )
(f 3)
(f 5)
(define (square n)
(* n n) )
(square 4)
(square 8)
(< 4 2)
(> (+ 5 7) (/ 141 114))
; -----
; Convert into Scheme notation:
(display "\nScheme Expressions 2:\n")
;7 – (4 - 5)
(- 7 ( - 4 5))
;(8 * 7) - (10 + 5)
(-(* 8 7 ) (+ 10 5))
;(2 * 3) + (4 * 5)
(+ ( * 2 3)(* 4 5))
;2 + 3 + 4
( + 2 3 4)
;5 * (4 + (-5 - -3))
(* 5 ( + 4 ( - -5 -3)))
;(36 / 6) / 2
(/ (/ 36 6) 2)
;3 / (5 - (1 / 7))
( / 3 ( - 5 ( / 7)))
;23 + 32
(+ 23 32)
; -----
; function cube definition
;  takes a number and returns x cubed.
(define ( cube num)
  ( * num num num))
; -----
; function rarea definition
;  computes the area of a circle given its radius
(define ( carea rad)
  ( * 3.14 rad rad))
; -----
; fucntion poly1 definition
;  takes a number x and returns 5x^2 + 12x + 36
(define (poly1 x)
  ( + (* 5 x x) (* 12 x) 36))
; -----
; fucntion poly2 definition
;  takes a number x and returns f(x) = 2x^3 + 4x^2 + 7x + 17
(define (poly2 x)
  (+ ( * 2 x x x) (* 4 x x) (* 7 x) 17))
; -----
;  calculate monthly payment
;  See PDF for formula.
(define (payment amount irate term)
  (* amount (/ (* irate (exponent ( + 1 irate) term))( - (exponent ( + 1 irate) term) 1.0))))
; -----
; recursive functions:
;  fact - takes a number x and finds x!
(define ( fact x )
  ( if ( zero? x) 1
  ( * x ( fact (- x 1) ))))
; -----
; Fibonnacci function definition
(define ( fib x)
  ( if (= x 0) 0
       ( if (= x 1) 1
            (+ (fib (- x 1)) (fib (- x 2))))))
; -----
; Harmonic function definition
(define (harmonic x)
  (if ( zero? x) 1
      (+ (harmonic (- x 1))(/ 1.0 x))))
; -----
; Exponent function definition
(define ( exponent base ex)
  ( if ( zero? ex) 1
       ( * base ( exponent base ( - ex 1)))))  
; -----
; Tak function definition
( define (tak x y z)
   (if ( >= y x) z
       ( tak ( tak ( - x 1) y z) ( tak ( - y 1) z x)( tak (- z 1) x y))))
; -----
;  Simple list operations
(list '2 '3 '4 '5 '6)
(list 'a 'b 'c 'd 'e)
(list 'one 'two 'three 'four)
(list '2 '(3 4) '5)
(list '1 '2 'fred '4 '5)
(cons 2 '(3 4))
(cons 3 '(5 7 (9 11)))
(car '(2 4 6 8))
(car '((2 5) 9 13))
(cdr '(5 7 9 11))
(cdr '(122 123))
(length '(11 13 15 17 19))
(reverse '(71 73 75 77 79))
(append '(12 13) '(15 17 19))
;; ============================================================
; Tests

; -----
; cube function tests
;(display "\n---------------------\n")
;(display "Tests - cube\n")
(cube 4)
(cube 9)
(cube 11)

; -----
; rectangle area fucntion tests
(display "\nTests - rarea\n")
(carea 5)
(carea 22)
(carea 42)

; -----
;  poly1 function tests
(display "\nTests - poly1\n")
(poly1 5)
(poly1 9)
(poly1 17)

; -----
;  poly2 function tests
(display "\nTests - poly2\n")
(poly2 5)
(poly2 9)

; -----
;  payment function tests
(display "\nTests - payment\n")
(payment 10000 10 10)
(payment 5000 5 7)

; -----
;  factorial function tests
(display "\nTests - fact\n")
(fact 5)
(fact 10)
(fact 34)

; -----
;  fibonacci function tests
(display "\nTests - fib\n")
(fib 13)
(fib 28)
(fib 32)

; -----
;  harmonic function tests
(display "\nTests - harmonic\n")
(harmonic 3)
(harmonic 7)
(harmonic 5)
(harmonic 10)
(harmonic 25)

; -----
; Tak function tests
;  (tak 2 3 4) = 4
;  (tak 18 12 6) = 7
;  (tak 70 60 55) = 56
;  (tak 70 60 52) = 53
; Note, last one will take a while...

(display "\ntak\n")
(tak 2 3 4)
(tak 18 12 6)
(tak 70 60 55)
(tak 70 60 52)

; -----
; exp function tests
(display "\nexp\n")
(exponent 2 3)
(exponent 2 8)
(exponent 2 16)
(exponent 3 2)
(exponent 3 3)
(exponent 10 8)



