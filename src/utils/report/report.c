/**
  * Record
  * 
  * use sampst for question b, d, e, f
  * use timest for question a, c
  */
#include "report.h"

void record_queue_length() {
    timest(
        list_size[LIST_AIR_TERMINAL_1],
        RCRD_QUEUE_LENGTH_AIR_TERMINAL_1
    );
    timest(
        list_size[LIST_AIR_TERMINAL_2],
        RCRD_QUEUE_LENGTH_AIR_TERMINAL_2
    );
    timest(
        list_size[LIST_CAR_RENTAL],
        RCRD_QUEUE_LENGTH_CAR_RENTAL
    );
}

void record_delay(double arrival_time, int location){
    sampst(
        sim_time - arrival_time,
        location + QUEUE_DELAY_RCRD_OFFSET
    );
}

void record_passenger_count() {
    timest(
        list_size[LIST_BUS_PASSENGER],
        RCRD_BUS_PASSENGER_NUM
    );
}

void record_bus_stop_time(double arrival_time) {
    sampst(
        sim_time - arrival_time,
        RCRD_BUS_STOP_TIME
    );
}

void record_loop_time(double last_departure_time) {
    sampst(
        sim_time - last_departure_time,
        RCRD_BUS_LOOP_TIME
    );
}

void record_person_total_time(double arrival_time, int arrival_location){
    sampst(
        sim_time - arrival_time,
        PERSON_TOTAL_TIME_RCRD_OFFSET + arrival_location
    );
}

void init_record() {
    // initialize timest val
    record_queue_length();
    record_passenger_count();
}

void report(FILE* output_file) {
    fprintf(
        output_file,
        "(A) QUEUE LENGTH"
    );
    out_timest(
        output_file,
        RCRD_QUEUE_LENGTH_AIR_TERMINAL_1,
        RCRD_QUEUE_LENGTH_CAR_RENTAL
    );

    fprintf(
        output_file,
        "(B) DELAY TIME"
    );
    out_sampst(
        output_file,
        RCRD_QUEUE_DELAY_AIR_TERMINAL_1,
        RCRD_QUEUE_DELAY_CAR_RENTAL
    );
    
    fprintf(
        output_file,
        "(C) BUS PASSENGER COUNT"
    );
    out_timest(
        output_file,
        RCRD_BUS_PASSENGER_NUM,
        RCRD_BUS_PASSENGER_NUM
    );

    fprintf(
        output_file,
        "(D) BUS STOP TIME"
    );
    out_sampst(
        output_file,
        RCRD_BUS_STOP_TIME,
        RCRD_BUS_STOP_TIME
    );

    fprintf(
        output_file,
        "(E) BUS LOOP TIME"
    );
    out_sampst(
        output_file,
        RCRD_BUS_LOOP_TIME,
        RCRD_BUS_LOOP_TIME
    );

    fprintf(
        output_file,
        "(F) PERSON TOTAL TIME"
    );
    out_sampst(
        output_file,
        RCRD_PERSON_TOTAL_TIME_FROM_AIR_TERMINAL_1,
        RCRD_PERSON_TOTAL_TIME_FROM_CAR_RENTAL
    );
}