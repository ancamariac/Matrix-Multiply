#!/bin/bash
printf "\nBLAS\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_blas input_valgrind >> blas.cache 2>&1

printf "\n\n\NEOPT\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_neopt input_valgrind >> neopt.cache 2>&1

printf "\n\n\nOPT\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_opt_m input_valgrind >> opt_m.cache 2>&1

rm -rf cachegrind*