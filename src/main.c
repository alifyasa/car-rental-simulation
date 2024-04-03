#include "main.h"

/* Parameters */

double MEAN_INTERARRIVAL[4]; // 4 because assume indexing starts at 1
double LOAD_TIME_MIN, LOAD_TIME_MAX;
double UNLOAD_TIME_MIN, UNLOAD_TIME_MAX;
double DESTINATION_PROBABILITIES[3];
int TOTAL_SIMULATION_TIME;


/* Global Variables */

FILE *FILE_INPUT, *FILE_OUTPUT;

int CURR_BUS_LOCN;
int NEXT_BUS_LOCN;

double BUS_NEXT_DEPARTURE_TIME;
int BUS_NEXT_DEPARTURE_CANCELLED;
int BUS_STOPPED;
int BUS_ON_STANDBY;

// Map event to stream
int EVNT_TO_STRM[] = {
    -1, // index starts at 1
    STRM_PERSON_ARRIVAL_AIR_TERMINAL_1,
    STRM_PERSON_ARRIVAL_AIR_TERMINAL_2,
    STRM_PERSON_ARRIVAL_CAR_RENTAL,
    -1, // no stream for event bus arrival
    STRM_BUS_UNLOAD,
    STRM_BUS_LOAD
};
int LOCN_TO_LIST[] = {
    -1,
    LIST_AIR_TERMINAL_1,
    LIST_AIR_TERMINAL_2,
    LIST_CAR_RENTAL
};
double TIME_TO_NEXT_LOCN_FROM[] = {
    -1.0,
    1.0 / 30.0 * HOUR, // convert to minute
    (0.5 + 3.0 + 1.0) / 30.0 * HOUR,
    (1.0 + 3.0 + 0.5) / 30.0 * HOUR,
};
int NEXT_LOCATION_FROM[] = {
    -1,
    LOCN_AIR_TERMINAL_2,
    LOCN_CAR_RENTAL,
    LOCN_AIR_TERMINAL_1
};

void init_model()
{
    // Simulation end at max double time
    event_schedule(__DBL_MAX__, EVNT_SIMULATION_END);

    /**
     * From the problem:
     *   "Bus is initially at car terminal and leaves immediately"
     * Hence bus starts by departing to air terminal 1
     */
    CURR_BUS_LOCN = LOCN_CAR_RENTAL;
    NEXT_BUS_LOCN = LOCN_AIR_TERMINAL_1;
    event_schedule(sim_time, EVNT_BUS_DEPARTURE);

    // Initialize people arrival
    event_schedule(
        sim_time + expon(
            MEAN_INTERARRIVAL[LOCN_AIR_TERMINAL_1], 
            EVNT_TO_STRM[EVNT_PERSON_ARRIVAL_AIR_TERMINAL_1]
        ),
        EVNT_PERSON_ARRIVAL_AIR_TERMINAL_1);
    event_schedule(
        sim_time + expon(
            MEAN_INTERARRIVAL[LOCN_AIR_TERMINAL_2], 
            EVNT_TO_STRM[EVNT_PERSON_ARRIVAL_AIR_TERMINAL_2]
        ),
        EVNT_PERSON_ARRIVAL_AIR_TERMINAL_2);
    event_schedule(
        sim_time + expon(
            MEAN_INTERARRIVAL[LOCN_CAR_RENTAL], 
            EVNT_TO_STRM[EVNT_PERSON_ARRIVAL_CAR_RENTAL]
        ),
        EVNT_PERSON_ARRIVAL_CAR_RENTAL);
}

/**
 * Used to initialize EVNT_LOAD_BUS event.
 * It checks whether there is a passenger that
 * are waiting and the bus is not full.
*/
void safe_schedule_load_bus(int location) {
    // if bus is in current location
    int bus_is_here = location == CURR_BUS_LOCN;
    // if bus is not full
    int bus_is_not_full = list_size[LIST_BUS_PASSENGER] < BUS_CAPACITY;
    // and if there are still passengers waiting
    int exist_more_passenger = list_size[LOCN_TO_LIST[location]] >= 1;
    if (bus_is_here && BUS_STOPPED && bus_is_not_full && exist_more_passenger) {
        // try to load them
        double next_load_time = sim_time 
            + uniform(LOAD_TIME_MIN, LOAD_TIME_MAX, EVNT_TO_STRM[EVNT_BUS_LOAD]);
        // Let that person unload first
        if (next_load_time > BUS_NEXT_DEPARTURE_TIME) {
            int cancelled = event_cancel(EVNT_BUS_DEPARTURE);
            if (cancelled) {
                BUS_NEXT_DEPARTURE_CANCELLED = 1;
                printf(
                    "[%9.4f] --- BUS DEPARTURE CANCELLED.\n", 
                    sim_time
                );
            }
        }
        event_schedule(
            next_load_time,
            EVNT_BUS_LOAD
        );
    } else if (BUS_NEXT_DEPARTURE_CANCELLED) {
        // If we cancel it, reschedule
        event_schedule(
            sim_time,
            EVNT_BUS_DEPARTURE
        );
    } else if (!exist_more_passenger) {
        BUS_ON_STANDBY = 1;
        printf(
            "[%9.4f] BUS ON STANDBY AT LOCATION %d. PASSENGER COUNT: %i\n", 
            sim_time, CURR_BUS_LOCN, list_size[LIST_BUS_PASSENGER]
        );
    }
}

void load_bus(int location){
    BUS_ON_STANDBY = 0;
    // Remove first passenger from location
    list_remove(FIRST, LOCN_TO_LIST[location]);
    // rank passenger based on distance
    list_rank[LIST_BUS_PASSENGER] = location + DD_RIDX_OFFET;
    list_file(INCREASING, LIST_BUS_PASSENGER);
    printf(
        "[%9.4f] PERSON LOADED AT LOCATION %d. PASSENGER COUNT: %i\n", 
        sim_time, location, list_size[LIST_BUS_PASSENGER]
    );

    // Try scheduling another EVNT_LOAD_BUS
    safe_schedule_load_bus(location);
}

/**
 * Used to initialize EVNT_UNLOAD_BUS event.
 * It checks whether there is a passenger that
 * have location as ther destination.
*/
void safe_schedule_unload_bus(int location) {
    // If there are still passengers
    int bus_is_not_empty = list_size[LIST_BUS_PASSENGER] >= 1;

    // Ask that passenger about their destination
    peek_first(LIST_BUS_PASSENGER);
    // if that person's destination is also here
    int first_passenger_dest_here = peek_transfer[RIDX_PERSON_DESTINATION] == location;
    if(bus_is_not_empty && first_passenger_dest_here) {
        double next_unload_time = sim_time 
            + uniform(UNLOAD_TIME_MIN, UNLOAD_TIME_MAX, EVNT_TO_STRM[EVNT_BUS_UNLOAD]);
        // Let that person unload first
        if (next_unload_time > BUS_NEXT_DEPARTURE_TIME) {
            int cancelled = event_cancel(EVNT_BUS_DEPARTURE);
            if (cancelled) {
                BUS_NEXT_DEPARTURE_CANCELLED = 1;
                printf(
                    "[%9.4f] --- BUS DEPARTURE CANCELLED.\n", 
                    sim_time
                );
            }
        }
        event_schedule(
            next_unload_time,
            EVNT_BUS_UNLOAD
        );
    } else {
        printf(
            "[%9.4f] --- NO PASSENGER TO UNLOAD. TRYING TO SCHEDULE LOAD.\n", 
            sim_time
        );
        safe_schedule_load_bus(location);
    }
}

void unload_bus(int location) {
    BUS_ON_STANDBY = 0;
    // unload passenger
    list_remove(FIRST, LIST_BUS_PASSENGER);
    printf(
        "[%9.4f] PERSON UNLOADED AT LOCATION %d. PASSENGER COUNT: %i\n", 
        sim_time, location, list_size[LIST_BUS_PASSENGER]
    );
    // Try scheduling more unload
    // If not possible, schedule load
    safe_schedule_unload_bus(location);
}

void bus_arrival() {
    CURR_BUS_LOCN = NEXT_BUS_LOCN;
    NEXT_BUS_LOCN = NEXT_LOCATION_FROM[CURR_BUS_LOCN];
    BUS_STOPPED = 1;
    BUS_ON_STANDBY = 0;
    printf(
        "[%9.4f] BUS ARRIVED AT LOCATION %d. PASSENGER COUNT: %d. WAITING LINE: %d\n", 
        sim_time, CURR_BUS_LOCN, list_size[LIST_BUS_PASSENGER], list_size[LOCN_TO_LIST[CURR_BUS_LOCN]]
    );
    
    event_schedule(
        sim_time + 5 * MINUTE,
        EVNT_BUS_DEPARTURE
    );
    BUS_NEXT_DEPARTURE_TIME = sim_time + 5 * MINUTE;
    BUS_NEXT_DEPARTURE_CANCELLED = 0;

    safe_schedule_unload_bus(CURR_BUS_LOCN);
}

void bus_departure() {
    printf(
        "[%9.4f] BUS LEFT LOCATION %d. NEXT ARRIVAL: (+%9.4f)\n", 
        sim_time, CURR_BUS_LOCN, TIME_TO_NEXT_LOCN_FROM[CURR_BUS_LOCN]
    );
    BUS_STOPPED = 0;
    BUS_ON_STANDBY = 0;
    // not in any location
    event_schedule(
        sim_time + TIME_TO_NEXT_LOCN_FROM[CURR_BUS_LOCN],
        EVNT_BUS_ARRIVAL
    );
}

/**
 * Handle person arrival event.
 * 
 * List of locations are available at main.h.
*/
void person_arrival_at(int location, int event_type) {
    event_schedule(
        sim_time + expon(
            MEAN_INTERARRIVAL[location],
            EVNT_TO_STRM[event_type]
        ),
        event_type
    );

    // Fill transfer
    transfer[RIDX_PERSON_ARRIVAL_TIME] = sim_time;
    if (location == LOCN_CAR_RENTAL) {
        transfer[RIDX_PERSON_DESTINATION] =
            // return 1 or 2
            random_integer(DESTINATION_PROBABILITIES, STRM_DESTINATION);
    } else {
        transfer[RIDX_PERSON_DESTINATION] = LOCN_CAR_RENTAL;
    }

    transfer[RIDX_PERSON_DD_FROM_AIR_TERMINAL_1] = (
        (int) transfer[RIDX_PERSON_DESTINATION] - LOCN_AIR_TERMINAL_1
    ) % 3;
    transfer[RIDX_PERSON_DD_FROM_AIR_TERMINAL_2] = (
        (int) transfer[RIDX_PERSON_DESTINATION] - LOCN_AIR_TERMINAL_2
    ) % 3;
    transfer[RIDX_PERSON_DD_FROM_CAR_RENTAL] = (
        (int) transfer[RIDX_PERSON_DESTINATION] - LOCN_CAR_RENTAL
    ) % 3;

    // FIFO, so insert last and remove first
    list_file(LAST, LOCN_TO_LIST[location]);

    printf(
        "[%9.4f] PERSON ARRIVED AT LOCATION %d. TOTAL PEOPLE WAITING: %i\n", 
        sim_time, location, list_size[location]
    );

    int bus_is_here = location == CURR_BUS_LOCN;
    if (bus_is_here && BUS_STOPPED && BUS_ON_STANDBY) {
        safe_schedule_load_bus(location);
    }
}


int main()
{
    FILE_INPUT = open_file("test/input/modsim.in", "r");
    FILE_OUTPUT = open_file("test/output/modsim.out", "w");
    read_input(
        FILE_INPUT,
        MEAN_INTERARRIVAL,
        &LOAD_TIME_MIN, &LOAD_TIME_MAX,
        &UNLOAD_TIME_MIN, &UNLOAD_TIME_MAX,
        DESTINATION_PROBABILITIES,
        &TOTAL_SIMULATION_TIME);

    init_simlib();
    init_model();

    while (sim_time < TOTAL_SIMULATION_TIME)
    {
        timing();
        switch (next_event_type)
        {
        case EVNT_PERSON_ARRIVAL_AIR_TERMINAL_1:
            person_arrival_at(LOCN_AIR_TERMINAL_1, next_event_type);
            break;
        case EVNT_PERSON_ARRIVAL_AIR_TERMINAL_2:
            person_arrival_at(LOCN_AIR_TERMINAL_2, next_event_type);
            break;
        case EVNT_PERSON_ARRIVAL_CAR_RENTAL:
            person_arrival_at(LOCN_CAR_RENTAL, next_event_type);
            break;
        case EVNT_BUS_ARRIVAL:
            bus_arrival();
            break;
        case EVNT_BUS_UNLOAD:
            unload_bus(CURR_BUS_LOCN);
            break;
        case EVNT_BUS_LOAD:
            load_bus(CURR_BUS_LOCN);
            break;
        case EVNT_BUS_DEPARTURE:
            bus_departure();
            break;
        case EVNT_SIMULATION_END:
            printf("Simulation END! Thank You\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Unhandled Event Type '%i', Panicking.\n", next_event_type);
            exit(EXIT_FAILURE);
        }
    }
}
