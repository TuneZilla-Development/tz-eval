#include <stdint.h>
#include <stdio.h>

#include "lib/log.h"
#include "lib/msg.h"

#include "tasks.h"

/**
 * @brief An example implementation of Task #01
 * 
 * @note This implementation is an example of how to use the included msg_ functions.
 * It should **not** be used as a template for your solutions. It is recommended that
 * you abstract out each layer of the protocol to generic functions which you reuse 
 * throughout the evaluations.
 * 
 * @return TASK_OK (0) on success. TASK_ERROR (1) on failure.
 */
int task_01_ping() {
    int result = MSG_OK;

    uint8_t msg[MSG_BUFFER_SIZE];
    uint8_t len = 0;

    // Send "Ping"..
    //  Opcode is 0, Length is 1 byte
    //  Command is 0x10 (Ping)
    msg[0] = 0x01;
    msg[1] = 0x10; // See definitions given in src/lib/proto.h ;)
    len = 2;
    if ((result = msg_send(msg, len)) != MSG_OK) {
        printf("\t --/ ERROR: Failed to write to pipe\n");
        return TASK_ERROR;
    }

    // Print the message to the terminal
    print_bytes(msg, len, "-->", "\t");

    // Receive response..
    result = msg_recv(msg, &len);
    if (result == MSG_TIMEOUT) {
        printf("\t x-- TIMEOUT: Failed to receive message in time\n");
        return TASK_ERROR;
    } else if (result != MSG_OK) {
        printf("\t /-- ERROR: Failed to read from pipe\n");
        return TASK_ERROR;
    }

    // Print the message to the terminal
    print_bytes(msg, len, "<--", "\t");

    // Check response
    //  Opcode is 0, Length is 1 byte
    //  Result must be 0x50 (0x10 + 0x40)
    if(len < 2 || msg[0] != 0x01 || msg[1] != 0x50) {
        printf("ERROR: Unexpected Response!");
        return TASK_ERROR;
    }

    return TASK_OK;
}

/**
 * @brief Retrieves the name of a task based on its task number.
 * 
 * This function searches through the list of tasks to find a task with a matching task
 * number. If a matching task is found, it returns the name of the task. If no match is
 * found, it returns "UNDEFINED_TASK".
 *
 * @note Do not edit this function.
 *
 * @param task_num The task number to search for.
 * @return The name of the task if found, or "UNDEFINED_TASK" if the task number is 
 * not defined.
 */
const char * get_task_name(uint8_t task_num) {
    // Iterate through our task list until we find a matching task_num
    for (int i = 0; i < NUM_OF_TASKS; i++) {
        if(task_list[i].task_num == task_num) {
            return task_list[i].task_name;
        }
    }

    // Make sure this task_num is defined in tasks.h / task_list
    return "UNDEFINED_TASK";
}
/**
 * @brief Executes a specified task based on the task number.
 *
 * This function logs the start of the task, executes the task based on the task number
 * using a switch-case statement, and logs the completion of the task. Each task should
 * be implemented within the corresponding case.
 *
 * @note Edit this function to implement the solutions for each task. Add the necessary
 * code within the appropriate case statements.
 *
 * @param task_num The task number to be executed.
 * @return The result of the task execution (TASK_OK, TASK_NOT_IMPLEMENTED, or specific
 * task result).
 */
int run_task(uint8_t task_num) {
    int result = TASK_OK; // OK

    // Write a message to `client.log`
    log_print("Task #%02X starting..\n", task_num);
    
    // Perform the task!
    // NOTE: Edit this Switch/Case to implement your solutions..
    switch(task_num){
    case(TASK_01_PING):
        result = task_01_ping();
        break;
    case(TASK_02_RETRY):
        // Add your TASK_02 implementation here..
        result = TASK_NOT_IMPLEMENTED;
        break;
    case(TASK_03_READ_DATA):
        // Add your TASK_03 implementation here..
        result = TASK_NOT_IMPLEMENTED;
        break;
    case(TASK_04_FRAME_HEADERS):
        // Add your TASK_04 implementation here..
        result = TASK_NOT_IMPLEMENTED;
        break;
    case(TASK_05_LENGTH_BYTE):
        // Add your TASK_05 implementation here..
        result = TASK_NOT_IMPLEMENTED;
        break;
    case(TASK_06_CHECKSUMS):
        // Add your TASK_06 implementation here..
        result = TASK_NOT_IMPLEMENTED;
        break;
    case(TASK_07_AUTHENTICATION):
        // Add your TASK_07 implementation here..
        result = TASK_NOT_IMPLEMENTED;
        break;
    default:
        result = TASK_NOT_IMPLEMENTED;
        break;
    }

    if(result == TASK_NOT_IMPLEMENTED) {
        log_print("ERROR: Task #%02X is not implemented\n", task_num);
    }

    log_print("Task #%02X done (%d)\n", task_num, result);

    return result;
}