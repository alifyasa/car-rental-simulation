#include "general.h"

void print_array_double(double arr[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

void print_array_int(int arr[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

FILE* open_file(char *file_path, char *mode) {
    FILE* opened_file;
    opened_file = fopen(file_path, mode);

    if (opened_file == NULL) {
        fprintf(stderr, "ERROR: Unable to open file '%s' with mode '%s'.\n", file_path, mode);
        if (strncmp(mode, "w", 1) == 0){
            fprintf(stderr, "ERROR: Check again if folder exists.\n");
        }
        exit(EXIT_FAILURE);
    }

    return opened_file;
}

void read_input(
    FILE *input_file,
    double mean_interarrival[],
    double *load_time_min, double *load_time_max,
    double *unload_time_min, double *unload_time_max,
    double dest_prob[],
    int *total_simulation_time)
{
    fscanf(
        input_file, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %d",
            &mean_interarrival[LOCN_AIR_TERMINAL_1], 
            &mean_interarrival[LOCN_AIR_TERMINAL_2], 
            &mean_interarrival[LOCN_CAR_RENTAL],
        load_time_min, load_time_max,
        unload_time_min, unload_time_max,
        &dest_prob[1], &dest_prob[2],
        total_simulation_time
    );

    printf("All Unit of Time is in seconds\n");
    printf("Mean Interarrival Times\t\t: %lf, %lf, %lf\n",
        mean_interarrival[LOCN_AIR_TERMINAL_1], 
        mean_interarrival[LOCN_AIR_TERMINAL_2], 
        mean_interarrival[LOCN_CAR_RENTAL]
    );
           
    printf("Load Time Min\t\t\t: %lf\n", *load_time_min);
    printf("Load Time Max\t\t\t: %lf\n", *load_time_max);
    
    printf("Unload Time Min\t\t\t: %lf\n", *unload_time_min);
    printf("Unload Time Max\t\t\t: %lf\n", *unload_time_max);
    
    printf("Destination Probabilities\t: %lf, %lf\n",
           dest_prob[1], dest_prob[2]);
           
    printf("Simulation Time\t\t\t: %d\n", *total_simulation_time);
}

void set_simlib_globals(){
    /**
     * 4 atributes to make 4 lists:
     *  - 3 FIFO arrival list
     *  - 1 FIFO bus passenger
     */
    maxatr = 4;
};