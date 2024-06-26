#pragma once

#include "../../main.h"

#define QUEUE_LENGTH_RCRD_OFFSET 0
#define RCRD_QUEUE_LENGTH_AIR_TERMINAL_1 1
#define RCRD_QUEUE_LENGTH_AIR_TERMINAL_2 2
#define RCRD_QUEUE_LENGTH_CAR_RENTAL     3

#define RCRD_BUS_PASSENGER_NUM 4

#define QUEUE_DELAY_RCRD_OFFSET 4
#define RCRD_QUEUE_DELAY_AIR_TERMINAL_1 5
#define RCRD_QUEUE_DELAY_AIR_TERMINAL_2 6
#define RCRD_QUEUE_DELAY_CAR_RENTAL     7

#define BUS_STOP_TIME_RCRD_OFFSET 7
#define RCRD_BUS_STOP_TIME_AIR_TERMINAL_1  8
#define RCRD_BUS_STOP_TIME_AIR_TERMINAL_2  9
#define RCRD_BUS_STOP_TIME_CAR_RENTAL     10

#define RCRD_BUS_LOOP_TIME 11

#define PERSON_TOTAL_TIME_RCRD_OFFSET 11
#define RCRD_PERSON_TOTAL_TIME_FROM_AIR_TERMINAL_1 12
#define RCRD_PERSON_TOTAL_TIME_FROM_AIR_TERMINAL_2 13
#define RCRD_PERSON_TOTAL_TIME_FROM_CAR_RENTAL     14

void record_queue_length();
void record_delay(double arrival_time, int location);
void record_passenger_count();
void record_bus_stop_time(double arrival_time, int location);
void record_loop_time(double last_departure_time);
void record_person_total_time(double arrival_time, int arrival_location);
void init_record();
void report(FILE* output_file);