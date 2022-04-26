
Nume: Ciuciu Anca-Maria
Grupă: 333 AA

# Tema 2 - Optimizare pe operatii cu matrice

Organizare
-
Problema rezolvata de aceasta tema se refera la optimizarea operatiilor realizate pe matrice ce compun urmatoarea expresie: 

> C = B × A × At + Bt × B

Asadar, rezolvarea acestei expresii a fost posibila prin intermediul a trei metode:

1. Metoda neoptimizata (*src/solver_neopt.c*) - ce contine implementarea naiva
2. Metoda optimizata (*src/solver_opt.c*) - o varianta imbunatatita a celei neoptimizata insa cu aceeasi complexitate
3. Metoda blas (*src/solver_blas.c*) - folosind metodele din biblioteca BLAS Atlas

Consider ca metoda optimizata ar fi putut fi implementata mai bine aplicandu-se mai atent anumite tehnici de optimizare de cod. Utilitatea acestei teme consta in analizarea performantelor unui cod realizat prin mai multe metode precum si folosirea bibliotecii BLAS Atlas drept referinta. 

Implementare
-
Intregul enunt al problemei a fost implementat. 


Testarea metodelor
-
Testarea solutiilor s-a realizat pe cluster, pe coada nehalem. In urma crearii executabilelor cu make, rularea s-a realizat folosind fisierul de input, ce contine dimensiunea matricei, seed-ul folosit pentru generarea datelor si denumirea fisierului de output, astfel:
> ./tema2_mod input

rezultatul fiind verificat cu:
> ./compare /export/asc/tema2/out1 out1 0.0001

Resurse utilizate
-
https://ocw.cs.pub.ro/courses/asc/laboratoare
http://www.netlib.org/blas/