#!/bin/bash
printf "\nBLAS\n"
valgrind --tool=memcheck --leak-check=full ./tema2_blas input_valgrind >> blas.memory 2>&1

printf "\n\n\nNEOPT\n"
valgrind --tool=memcheck --leak-check=full ./tema2_neopt input_valgrind >> neopt.memory 2>&1

printf "\n\n\nOPT\n"
valgrind --tool=memcheck --leak-check=full ./tema2_opt_m input_valgrind >> opt_m.memory 2>&1