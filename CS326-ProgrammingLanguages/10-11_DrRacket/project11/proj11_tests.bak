#lang racket

;; Project #11

; -----
;  Predicates - iseven? or isodd?



(newline)
(display "Even Tests -> (iseven? atm) \n")
(iseven? 10)
(iseven? 21)
(iseven? 50)
(iseven? 97)
(newline)

(display "Odd Tests -> (isodd? atm) \n")
(isodd? 10)
(isodd? 21)
(isodd? 50)
(isodd? 97)
(newline)

; -----
;  Multiply all numbers in a list, including sublists.
;  [i.e.,   (product '(1 2 3) = 6 ]



(display "Product Tests -> (prod lst) \n")
(prod '(2 3 4 5))
(prod '(10 20 30))
(prod '(2 3 (2 3) 4 5))
(prod '(2 2 2 2))
(prod '(2 2 (2 2 (2 2 2) 2)))
(prod '())
(newline)

; -----
;  Multiply each element of a list by n.
;  [i.e.,   (lstmul 2 '(2 3 4)) = (list 4 6 8)]



(display "List Multiplication Tests -> (lstmul lst) \n")
(lstmul 2 '(2 3 4))
(lstmul 5 '(2 4 6 8))
(lstmul 2 '(1 2 (3 4)))
(lstmul 10 '(10 20 30 40))
(lstmul 2 '(100 200 (300 400)))
(lstmul 2 '(1 2 (3 4 (5 6) (7 8) 9) 10 (11) 12))
(lstmul 12 '())
(lstmul 10 '(10 20 (10 20) 30 40))
(lstmul 2 '(2 4 (2 4) 2 4 (2 2 (2 2)) 2 4))
(newline)

; -----
;  Sum numbers in a list, including sublists
;  [i.e.,   (sumlist '(2 3 4) = 9 ]



(display "Sum List Tests -> (sumlist lst) \n")
(sumlist '(1 2 3 4 5 6 7 8 9))
(sumlist '(1 2 (2 3) 4))
(sumlist '(100 200 300 400 4 3 2 1))
(sumlist '(1 2 (3 4 (5 6 (7 8 (9 10) 11)) 12) 13 14))
(sumlist '())
(newline)

; -----
;  Length of a list.
;  [i.e.,   (len '(1 2 3 4 5 6 7 8)) = 8 ]



(display "Length Tests -> (len lst) \n")
(len '(1 2 3 4 5 6 7 8))
(len '(4))
(len '(7 9 1 4 2))
(len '(7 9 (1 4) 2))
(len '(1 1 (1 1 (1 1 1) 1 ) 1 (1 1 1)))
(len '())
(newline)

; -----
;  Average of list.
;  [i.e.,   (average '(4 5 6 7 8)) = 6 ]



(display "Average Tests -> (average lst) \n")
(average '(4 5 6 7 8))
(average '(1 (2) 3 (4 5 (6 7) 8 (9) 10)))
(average '(21 32 46 51 69))
(average '(111 222 333))
(average '(3))
(average '())
(average '(4 5 (6 7) 8))
(average '(2 2 (4 4) 2 (4 2 (4 2) 2 4) 4))
(newline)

; -----
;  Flatten the list
;  [i.e.,   (flatten '(1 2 (3 4 (5 6)))) = (list 1 2 3 4 5 6) ]



(display "Flatten Lists Tests -> (flatten lst) \n")
(flatten '(1 2 (3 4 (5 6))))
(flatten '(1 2 (3 4 (5 6) 7 8 (9 10) 11 (12) 13 14) 15 16))
(flatten '(a ((c d) f) d))
(flatten '(a (((d f g)) e) h))
(flatten '())
(flatten '(1 1 (1 1 (1 1 1) 1 ) 1 (1 1 1)))
(newline)

; -----
;  Reverse all items in a list.
;  [i.e.,   (rvlst '(2 3 4 5)) = (list 5 4 3 2) ]



(display "Reverse List Tests -> (revlst lst) \n")
(rvlst '(1 2 3 4 5 6))
(rvlst '(1 2 (3 4) (5 6) 7 8))
(rvlst '(9 87 6 5 4 3 2 1))
(rvlst '(10 20 30 40))
(rvlst '())
(rvlst '(9 8 (7 6 (5 4) 3) 2 1))
(newline)

; -----
;  Remove first occurance of item from a list.
;  [i.e.,   (rmFirstOcc 3 '(2 3 4 3)) = (list 2 4 3) ]



(display "Remove First Occurance of Item from List Tests -> (rmFirstOcc lst) \n")
(rmFirstOcc 3 '(2 3 4 3))
(rmFirstOcc 18 '(12 14 87 12 18))
(rmFirstOcc 5 '(1 2 (3 4 (5) 6)))
(rmFirstOcc 3 '(2 3 4 3))
(rmFirstOcc 9 '(1 3 5 7 9 11 13))
(rmFirstOcc 3 '(4 7 (5 2) (8 1) (9 2 (3 1))))
(rmFirstOcc 8 '(0 2 (4 6 (8 10) 12) 14 16))
(rmFirstOcc 10 '())
(rmFirstOcc 50 '(10 (20 (30 (40 (50 60) 70) 80) 90) 100))
(newline)

; -----
;  Find smallest element in list.
;  Accepts list and item.
;  [i.e.,   (minimum '(7 5 (6 1))) = 1 ]




(display "Minimum Item in List Tests -> (minimum lst) \n")
(minimum '(5 4 3 2 1))
(minimum '((2 3) 7 5 (6 1)))
(minimum '(5 2 7))
(minimum '(4121 3532 5522))
(minimum '((9 8) 1))
(minimum '(26 18 (27 21 19 (12 21 (7 10) 15) 17))) 
(minimum '(12 15 12 (71 34 (51 9)) 61))
(minimum '(21 15 (71 34 (51 (37 4)) 61) 32 41 18))
(minimum '())
(newline)

; -----
; Insertion Sort
;  [i.e.,   (insertion-sort '(9 1 8 2 7 3 6 4 5)) = (1 2 3 4 5 6 7 8 9) ]



(display "Insertion Sort Tests -> (insertion-sort lst) \n")
(insertion-sort '(5 9 8 4 2))
(insertion-sort '(5 9 2))
(insertion-sort '(5 9 1 2))
(insertion-sort '(12 7 3 5 9 11 1 8 10 4 2 6 12 1))
(newline)

; -----
;  Sqaure program.
;  Read a number from the user and output its value squared and cubed.
;  Note, uses built-in (read) function



(sqr-and-cube)

; -----
;  Simple list stats program.
;  Read a list from the user and compute the
;  length, sum, and average.
;  Note, also uses built-in (read) function
;  Also sorts lists and displays.




(liststats)


