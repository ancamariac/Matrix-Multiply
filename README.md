
Nume: Ciuciu Anca-Maria
Grupă: 333 AA

# Tema 2 - Optimizare pe operatii cu matrice

Organizare
-
Problema rezolvata de aceasta tema se refera la optimizarea operatiilor realizate pe matrice ce compun urmatoarea expresie: 

> C = B × A × At + Bt × B

Asadar, rezolvarea acestei expresii a fost posibila prin intermediul a trei metode:

1. Metoda neoptimizata (*src/solver_neopt.c*) - ce contine implementarea naiva
2. Metoda optimizata (*src/solver_opt.c*) - o varianta imbunatatita a celei neoptimizate insa cu aceeasi complexitate
3. Metoda blas (*src/solver_blas.c*) - folosind metodele din biblioteca BLAS Atlas

Consider ca metoda optimizata ar fi putut fi implementata mai bine aplicandu-se mai atent anumite tehnici de optimizare de cod. Utilitatea acestei teme consta in analizarea performantelor unui cod realizat prin mai multe metode precum si folosirea bibliotecii BLAS Atlas drept referinta. 

Implementare
-
Intregul enunt al problemei a fost implementat.

Versiunea **neoptimizata** a acestei probleme este compusa din implementarea urmatoarelor metode, impartind operatia pe 4 chunks, R1, R2 R3 si rezultatul final, R4: 
- *upper_X_lower* (ce primeste ca argumente dimensiunea matricei si o matrice superior triunghiulara si intoarce produsul A * At)
- *multiplication* si *multiplication_with_transpose* (ce realizeaza operatia de inmultire cu doua matrice oarecare, respectiv cu transpusa unei matrice oarecare)
- *addition* (ce realizeaza operatia de adunare)

Timpii de executie pentru input:
>
Run=./tema2_neopt: N=400: Time=1.383853 <br>
Run=./tema2_neopt: N=800: Time=12.115036 <br>
Run=./tema2_neopt: N=1200: Time=41.016384 <br>
 
Versiunea **optimizata** a problemei se refera la utilizarea acelorasi metode descrise mai sus, complexitatea fiind aceeasi pentru fiecare operatie. Diferenta intervine la abordarea urmatoarelor tehnici:
- folosirea keyword-ului "register" pentru stocarea constantelor, astfel ca acestea sunt accesate mai repede dintr-un registru
- pastrarea constantelor in variabile pentru a nu se executa operatia respectiva de fiecare data intr-o bucla
- schimbarea configuratiei pentru ordinea buclelor, din ijk in ikj pentru *multiplication*
- inlocuirea lui calloc cu malloc
  
Timpii de executie pentru input:
>
Run=./tema2_opt_m: N=400: Time=0.418594 <br>
Run=./tema2_opt_m: N=800: Time=3.986610 <br>
Run=./tema2_opt_m: N=1200: Time=11.850770 <br>

Versiunea **blas** se refera la utilizarea metodelor deja implementate din biblioteca BLAS Atlas astfel:
- s-a tinut cont de faptul ca matricea A este o matrice superior triunghiulara, folosind functia *cblas_dtrmm* cu valoarea *CblasUpper* pentru inmultirea cu A
- pentru adunarea de la final s-a folosit *cblas_dgemm* ce adauga la rezultatul anterior, inmultirea Bt x B

Timpii de executie pentru input:
>
Run=./tema2_blas: N=400: Time=0.038164 <br>
Run=./tema2_blas: N=800: Time=0.279452 <br>
Run=./tema2_blas: N=1200: Time=0.917279 <br>

Cachegrind
-
Din analiza output-ului generat de cachegrind se observa faptul ca:
- varianta neoptimizara are cea mai mare valoare a lui I ref, reprezentand numarul de instructiuni executate, blas, avand cea mai mica valoare. Asadar, spre exemplu, putem aminti aici faptul ca pentru solver_opt.c, operatiile ce contineau constante au fost stocate independent de bucla din care faceau parte initial, tocmai pentru ca acea operatie sa nu se efectueze de fiecare data. 
> **addition**: int N2 = N * N => parcurgere pana la N2 in loc de N*N
> 
- analizand D refs, scrierile si citirile din memorie, se observa acelasi clasament, datorita utilizarii lui register, in opt_m.
- in ceea ce priveste conditional & indirect branches, versiunea optimizata inregistreaza o performanta mai buna, datorita folosirii configuratiei ikj

Analiza comparativa a rezultatelor
-
![Comparatie](/grafice/comparatie.png "Analiza comparativa")

Testarea metodelor
-
Testarea solutiilor s-a realizat pe cluster, pe coada nehalem. In urma crearii executabilelor cu make, rularea s-a realizat folosind fisierul de input, ce contine dimensiunea matricei, seed-ul folosit pentru generarea datelor si denumirea fisierului de output, astfel:
> ./tema2_mod input

rezultatul fiind verificat cu:
> ./compare /export/asc/tema2/out1 out1 0.0001

Resurse utilizate
-
- https://ocw.cs.pub.ro/courses/asc/laboratoare
- http://www.netlib.org/blas/