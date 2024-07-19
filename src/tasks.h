/**
 * @file tasks.h
 * @brief Task definitions and declarations for the TuneZilla client program.
 *
 * This header file provides a series macros (and variables) to help you with the
 * implementation of a hypothetical communication protocol. Please refer to the full
 * task descriptions given in README.md.
 *
 * Tasks:
 * - TASK_01_PING: Send a "Ping" command to the server and receive the response.
 * - TASK_02_RETRY: Implement logic for handling a timeout.
 * - TASK_03_READ_DATA: Use the "Read" command to read data from the server, decode and print the result as a string.
 * - TASK_04_FRAME_HEADERS: Implement support for receiving packets spread across multiple messages/frames.
 * - TASK_05_LENGTH_BYTE: Implement support for receiving packets longer than 15 bytes.
 * - TASK_06_CHECKSUMS: Use the "Write" command to write data to the server. Calculate and send the required checksum.
 * - TASK_07_AUTHENTICATION: Use the "Seed" and "Auth" commands to authenticate the client with the server. Read the "seed" from the server, calculate and send the required "key".
 * 
 * @date 2024-07
 * 
 * @note DO NOT EDIT THIS FILE.
 * 
 */
#ifndef TASKS_H
#define TASKS_H

#define TASK_OK                     (0)
#define TASK_ERROR                  (1)
#define TASK_NOT_IMPLEMENTED        (2)

//===============================================================
// Task #01 - Ping (This is the initial state of the project)
//
// Send a "Ping" command to the server and receive the response.

#define TASK_01_PING                (0x01)

//===============================================================
// Task #02 - Retry on timeout
//
// Implement logic for handling a timeout.

#define TASK_02_RETRY               (0x02)

//===============================================================
// Task #03 - Request data from the server
//
// Use the "Read" command to read data from the server, decode and print the result as a string.

#define TASK_03_READ_DATA           (0x03)

//===============================================================
// Task #04 - Frame Headers / Receiving Multiple Frames
//
// Implement support for receiving packets spread across multiple messages/frames.

#define TASK_04_FRAME_HEADERS       (0x04)

//===============================================================
// Task #05 - Length Byte / Receiving More Frames
// 
// Implement support for receiving packets longer than 15 bytes.

#define TASK_05_LENGTH_BYTE        (0x05)

//===============================================================
// Task #06 - Sending Multiple Frames / Calculating Checksums
// 
// Use the "Write" command to write data to the server. Calculate and send the required checksum.

#define TASK_06_CHECKSUMS           (0x06)

//===============================================================
// Task #07 - Client Authentication / Data Manipulation
// 
// Use the "Seed" and "Auth" commands to authenticate client with the server. Read the "seed" from
// the server, calculate and send the required "key".

#define TASK_07_AUTHENTICATION      (0x07)

//===============================================================

typedef struct {
    int task_num;
    const char *task_name;
} sTaskEntry;

// Macro to create {task_num, task_name} pairs from a #define macro
#define NEW_TASK(task_macro)  {task_macro, #task_macro}

// List of all defined tasks. Used to fetch names, and run all defined
// tests.
static sTaskEntry task_list[] = {
    NEW_TASK(TASK_01_PING),
    NEW_TASK(TASK_02_RETRY),
    NEW_TASK(TASK_03_READ_DATA),
    NEW_TASK(TASK_04_FRAME_HEADERS),
    NEW_TASK(TASK_05_LENGTH_BYTE),
    NEW_TASK(TASK_06_CHECKSUMS),
    NEW_TASK(TASK_07_AUTHENTICATION),
};
#define NUM_OF_TASKS        (7)

//===============================================================

const char * get_task_name(uint8_t task_num);

int run_task(uint8_t task);

#endif // TASKS_H