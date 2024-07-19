/**
 * @file proto.h
 * @brief Protocol definitions for TuneZilla evaluation project
 *
 * This header file defines the constants and macros used in the packet and command layers.
 * Refer to the README.md for additional information about this protocol.
 */

#ifndef PROTO_H
#define PROTO_H

#include <stdint.h>

//===============================================================
// Packet Layer
//===============================================================

// Frame Header
//  [7:4] OpCode
#define TP_OPC_SINGLE           ((uint8_t)(0x0))
#define TP_OPC_FIRST            ((uint8_t)(0x1))
#define TP_OPC_CONSECUTIVE      ((uint8_t)(0x2))

//  [3:0] Length
#define TP_MAX_LEN_NO_LENGTH    (0x0F)

//  Additional Length Byte
#define TP_MAX_LEN_WITH_LENGTH  (0xFF + 1)

#define TP_MAX_LEN_SINGLE       (8 - 1)
#define TP_MAX_LEN_CONSECUTIVE  (8 - 1)

//===============================================================
// Command Layer
//===============================================================

#define MAX_CMD_RETRIES         (3)

// Command Identifiers (CID)
#define CID_10_PING             ((uint8_t)(0x10))
#define CID_20_READ             ((uint8_t)(0x20))
#define CID_21_WRITE            ((uint8_t)(0x21))
#define CID_30_SEED             ((uint8_t)(0x30))
#define CID_31_AUTH             ((uint8_t)(0x31))

// Positive Response
// Helper to get the Positive Response Code (PRC) for the given Command Identifier (CID)
#define PRC(CID)                ((uint8_t)((CID + 0x40) & 0xFF))

// Negative Response
// Indicates a negative result to the given command (CID is byte 1)
#define NRC                     ((uint8_t)(0x7F))

#define NRC_xx_UNDEFINED_NRC    ((uint8_t)(0x00))
#define NRC_10_GENERAL_REJECT   ((uint8_t)(0x10)) // General Reject. Used if a more specific NRC is not available
#define NRC_11_UNKNOWN_COMMAND  ((uint8_t)(0x11)) // Unknown or Unsupported Command ID
#define NRC_12_SEQUENCE_ERROR   ((uint8_t)(0x12)) // Command sequence error. Another command or commands were expected first
#define NRC_13_PARAMETER_ERROR  ((uint8_t)(0x13)) // Parameter not supported or invalid parameter format
#define NRC_14_OUT_OF_RANGE     ((uint8_t)(0x14)) // Parameter request out of range
#define NRC_15_INVALID_DATA     ((uint8_t)(0x15)) // Invalid data / length or incorrect key
#define NRC_16_INVALID_CHECKSUM ((uint8_t)(0x16)) // Invalid checksum
#define NRC_17_ACCESS_DENIED    ((uint8_t)(0x17)) // Access denied, authenication required

#endif // PROTO_H