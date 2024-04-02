#include "simlib.h"

#define EVENT_BUS_ARRIVAL_1     4
#define EVENT_BUS_ARRIVAL_2     5
#define EVENT_BUS_ARRIVAL_3     6
#define EVENT_ARRIVAL_1         1
#define EVENT_ARRIVAL_2         2
#define EVENT_ARRIVAL_3         3
#define STREAM_INTERARRIVAL_1   1
#define STREAM_INTERARRIVAL_2   2
#define STREAM_INTERARRIVAL_3   3
#define INITIAL_BUS_LOCATION    0

FILE *inputfile, *outputfile;
double mean_interarrival[4], min_load, max_load, min_unload, max_unload;
double dest_prob[3];
int simulation_time, bust_loc;

void init_schedule(){
    list_rank[4] = 1;

    bust_loc = INITIAL_BUS_LOCATION;

    for(int i = 0; i<3; i++){
        event_schedule(sim_time + expon(mean_interarrival[i+1], STREAM_INTERARRIVAL_1 + i), EVENT_ARRIVAL_1 + i);
    }

    event_schedule(sim_time, EVENT_BUS_ARRIVAL_3);
}

int main() {
    inputfile = fopen("test/input/modsim.in", "r");
    outputfile = fopen("test/output/modsim.out", "w");
    fscanf(inputfile, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %d", &mean_interarrival[1], &mean_interarrival[2], &mean_interarrival[3], &min_unload, &max_unload, &min_load, &max_load, &dest_prob[1], &dest_prob[2], &simulation_time);
    // char myString[] = "Hello, World!";
    // printf("%s\n", myString);
    init_simlib();

    init_schedule();

    while(sim_time < simulation_time){
        timing();
        switch (next_event_type)
        {
            case EVENT_BUS_ARRIVAL_1:
                /* code */
                break;
            case EVENT_BUS_ARRIVAL_2:
                /* code */
                break;
            case EVENT_BUS_ARRIVAL_3:
                /* code */
                break;
            case EVENT_ARRIVAL_1:
                /* code */
                break;
            case EVENT_ARRIVAL_2:
                /* code */
                break;
            case EVENT_ARRIVAL_3:
                /* code */
                break;
            default:
                break;
        }
        simulation_time++;
        break;
    }

    return 0;
}