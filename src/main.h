// Supported by GCC to solve multiple definition problem
#pragma once

#include "simlib.h"
#include "utils/utils.h"

/**
 * Constants
 */

#define BUS_CAPACITY 20

/**
 * Events
 * 
 * What happens in the simulation.
 */
#define EVNT_PERSON_ARRIVAL_AIR_TERMINAL_1 1
#define EVNT_PERSON_ARRIVAL_AIR_TERMINAL_2 2
#define EVNT_PERSON_ARRIVAL_CAR_RENTAL     3
#define EVNT_BUS_ARRIVAL                   4
#define EVNT_BUS_UNLOAD                    5
#define EVNT_BUS_LOAD                      6
#define EVNT_BUS_DEPARTURE                 7
#define EVNT_SIMULATION_END                0

/**
 * Lists
 * 
 * Lists are stored by simlib and retrieved
 * using a number. This number (will be refered as list_number) is used when:
 *  - list_file(). Add all of 'transfer' as an entry.
 *  - list_remove(). Remove an element from the list. Write it to 'transfer'.
 *  - list_size. list_size[list_number] is the size of the list.
 */

#define LIST_AIR_TERMINAL_1 1
#define LIST_AIR_TERMINAL_2 2
#define LIST_CAR_RENTAL     3
#define LIST_BUS_PASSENGER  4


/**
 * Streams
 * 
 * Streams are used to generate random numbers.
 * STRM_X == EVNT_X
 */

#define STRM_PERSON_ARRIVAL_AIR_TERMINAL_1 1
#define STRM_PERSON_ARRIVAL_AIR_TERMINAL_2 2
#define STRM_PERSON_ARRIVAL_CAR_RENTAL     3
#define STRM_BUS_UNLOAD                    4
#define STRM_BUS_LOAD                      5
#define STRM_DESTINATION                   6


/**
 * Record Index
 */

#define RIDX_PERSON_ARRIVAL_TIME 1
#define RIDX_PERSON_DESTINATION  2
// DD is Destination Distance
#define DD_RIDX_OFFET 2 // RIDX_PERSON_DD_X = LOCN_x + DD_RIDX_OFFSET
#define RIDX_PERSON_DD_TO_AIR_TERMINAL_1 3
#define RIDX_PERSON_DD_TO_AIR_TERMINAL_2 4
#define RIDX_PERSON_DD_TO_CAR_RENTAL 5

/**
 * Locations
 */
#define LOCN_AIR_TERMINAL_1 1
#define LOCN_AIR_TERMINAL_2 2
#define LOCN_CAR_RENTAL     3

#define MINUTE 1
#define HOUR   60