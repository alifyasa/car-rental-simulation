// Supported by GCC to solve multiple definition problem
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../main.h"

/* Prints an array of double */
void print_array_double(double arr[], int arr_size);

/* Prints an array of int */
void print_array_int(int arr[], int arr_size);

/* Open a file. Panics if error. */
FILE* open_file(
    char* file_path,
    char* mode
);

/* 
 * Read input from FILE. 
 * 
 * File format is "%lf %lf %lf %lf %lf %lf %lf %lf %lf %d".
 */
void read_input(
    FILE* input_file,
    double mean_interarrival[],
    double* load_time_min, double* load_time_max, 
    double* unload_time_min, double* unload_time_max,
    double dest_prob[],
    int* total_simulation_time
);

/*  
 * Set the following simlib globals:
 *  1. maxatr
 */
void set_simlib_globals();