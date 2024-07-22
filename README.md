# Introduction

Welcome! This project serves as the technical evalulation for applicants to TuneZilla Software's Software Engineer position. Carefully read through this README for your instructions.

## Overview

Applicants should build upon the provided C project to implement a hypothetical communication protocol. The primary goal of this exercise is to evaluate your ability to read and write C programs. While functional code is helpful, we are more interested in how you approach and the quality of your solution. If you get stuck at any point, do your best to continue (i.e., use placeholder data, leave comments, explain your work, etc).

Applicants should limit themselves to under 3 hours to complete this evaluation. Completion of every task is not expected nor required -- again, we are more interested in your approach and code quality.

### Submitting Your Work

When finished, applicants should compress their project files, **excluding executibles**, to a `.zip` and send to the specified email address. To avoid content filters **DO NOT** send us your executibles/`.exe` files, we will rebuild your project using the included Dockerfile. Applicants who complete at least four (4) of the tasks will be compensated for their submission.

# Project Structure

The project is organized as follows:

```
TuneZilla_Dev_Evaluation/
    src/
        lib/
            log.h
            log.c
            msg.h
            msg.c
            proto.h
            version.h
        client.c
        tasks.h
        tasks.c
    .gitignore
    Makefile
    Dockerfile
    README.md
    client.exe
    server.exe
```

Of these files you should only need to edit `src/task.c`. Please **do not** modify `src/client.c` or any file in `src/lib/*`. You are welcome to create additional `src/` files as required. If you choose to use additional files, or non-standard libraries be sure to update your Makefile/Dockerfile and include them in your submission. The use of non-standard libraries should not be required.

---

# Tasks

These series of tasks will walk you through the implementation of a hypothetical communication protocol. This protocol facilitates the communication between a client (your application) and a server (provided by us). 

It is your job to implement the necessary functionality to `client.exe` so that it can communicate with the provided `server.exe` in order to complete the given tasks. It is advised that you complete the given tasks in order as they are designed to incrementally build on eachother. The ideal solution should be capable of completing all the included tasks without human intervention.

## Task #00 - Getting Started

This first task will assist you with running the included `server.exe` and `client.exe` as well as setting up your build environment for creating your custom `client.exe`.

### Running the Project

1. **Start the Server Application**:
   - Open a new Terminal or shell in the project directory
   - Start the server application (**This application is bundled with the project**)
     ```sh
     ./server.exe
     ```

2. **Run the Client Application**:
   - In a different Terminal / shell
   - Start the client application
     ```sh
     ./client.exe
     ```
   - For the included `client.exe` you should see the following output:
     ```
     ...

     TASK_01_PING Starting...
         --> 01 10
         <-- 01 50
     TASK_01_PING SUCCESS
     
     TASK_02_RETRY Starting...
     ERROR: TASK_02_RETRY is not implemented. See src/tasks.c
     
     TASK_03_READ_DATA Starting...
     ERROR: TASK_03_READ_DATA is not implemented. See src/tasks.c
     
     TASK_04_FRAME_HEADERS Starting...
     ERROR: TASK_04_FRAME_HEADERS is not implemented. See src/tasks.c
     
     TASK_05_LENGTH_BYTE Starting...
     ERROR: TASK_05_LENGTH_BYTE is not implemented. See src/tasks.c
     
     TASK_06_CHECKSUMS Starting...
     ERROR: TASK_06_CHECKSUMS is not implemented. See src/tasks.c
     
     TASK_07_AUTHENTICATION Starting...
     ERROR: TASK_07_AUTHENTICATION is not implemented. See src/tasks.c
     ```
   - If you wish to perform a single task you can provide that task # as an argument:
     ```sh
     ./client.exe 02
     ```

### Modifying the Project
During the following tasks you will be required to make changes to the project to add functionality to the `client.exe` application.

Start by opening `src/tasks.c`. The client application makes calls to `run_task()`, this is the entrypoint for your solutions. You should implement your task solutions to the switch/case block contained in this function. **We've provided the solution to Task #01 as an example**.

After you've made your additions to `src/tasks.c` rebuild the project, as described below. 

### Building the Project

After modifying the included `.c`/`.h` files you will need to rebuild your `client.exe`. You can do this with the included Dockerfile, or by using the Makefile (using MINGW32/MSYS2, etc).

This project assumes you are using WINDOWS. If this is not the case and/or you are not able to put together a working environment please do your best to continue. You can use the examples provided in this README as placeholder data.

#### With the Included Dockerfile

   - Install docker as required for your computer ([Docker Desktop for Windows](https://docs.docker.com/desktop/install/windows-install/))
   - In a terminal or shell navigate to the project directory
   - Build the image:
     ```sh
     docker build -t tz-eval .
     ```
   - Create a container with the name `tz-eval-builder`:
     ```sh
     docker rm -f tz-eval-builder
     docker create --name tz-eval-builder tz-eval
     ```
   - Copy the compiled `client.exe` out of the container
     ```sh
     docker cp tz-eval-builder:/client.exe ./client.exe
     ```

#### Using the Included Makefile

1. **Install MINGW32 / MSYS2**:
   - Download and install MSYS2 from the official website: [MSYS2](https://www.msys2.org/).
   - Follow the installation instructions provided on the MSYS2 website.

2. **Set Up MINGW32**:
   - Open the MINGW32 shell (you can find it in the Start menu).
   - Update the package database and base packages:
     ```sh
     pacman -Syu
     ```
   - Close and reopen the MINGW shell.
   - Install the GCC compiler and Make:
     ```sh
     pacman -S mingw-w64-i686-toolchain
     pacman -S make
     ```

3. **Building using Make**
   - Open the MINGW32 shell (you can find it in the Start menu).
   - Navigate to the project directory:
     ```sh
     cd /c/Users/<your-username>/<path_to_project>/
     ```
   - Use Make to compile the project:
     ```sh
     make clean all
     ```
   - This will make a new `client.exe` which you can run with:
     ```
     ./client.exe
     ```
   - Alternatively you can use this command to make and run the executible:
     ```
     make clean run
     ```

## Task #01 - Ping (Initial State)
Send a "Ping" command to the server and receive the response.

Using the included msg_send() function the client (your application) will send a "Ping" request to the server. The server will reply with the "Positive Response Code" for the Ping command

The client (your application) will send a "Ping" to the server using the provided msg_send() function. The server will reply to the  Ping with the positive Ping response (0x50 or CID + 0x40). Receive this message using the provided msg_recv() function.

Note, be sure to include the first byte (0x01). This is part of our protocol and will be explained later.

#### Example:
```
--> 01 10 (Client, you)
<-- 01 50 (Server)
```

## Task #02 - Retry on Timeout
Implement logic for handling a timeout.

If you do not receive a timeout within the timeout period (1s) msg_recv() will return a MSG_TIMEOUT (2) error. In this case we assume the server did not receive our initial request and we should retry the same message again.

Note, be sure to include the first byte (0x01). This is part of our protocol and will be explained later.

#### Example:
```
--> 01 10
... (Timeout)
--> 01 10
<-- 01 50
```

## Task #03 - Request data from the server

Use the "Read" command to read data from the server, decode and print the result as a string.

The "Read" (0x20) command takes a "Data Identifier" parameter immediately following the Command ID. This identifier specifies which data should be returned by the server. Upon receiving a valid request the server will reply with the requested data. For this task use a data identifier of `0x01` and print the result as a string. 

Note, the server will send a Positive Response byte **and echo the data identifier**, both of these bytes are not part of the result and should not be printed.

Note, be sure to include the first byte (0x02). This is part of our protocol and will be explained later.

#### Example:
```
--> 02 20 01
<-- 04 60 01 ?? ??

// Print "?? ??" as a string (Hint, it's ASCII text)
'??'
```

## Task #04 - Frame Headers / Receiving Multiple Frames

Implement support for receiving packets spread across multiple messages/frames.

msg_send() and msg_recv() are limited to 8 bytes per message or "frame" (similar to CAN2.0). To work around this limitation our protocol uses a simple header byte at the start of every message. This header byte contains an opcode and the total length of data. Up until now this header byte has been hardcoded into our messages. Refer to the "Transport / Packet Layer" section for more information.

For this task use a data identifier of 0x02 and print the result as a string. The result will be spread across multiple frames. Do not print the header bytes.

Note, be sure to include the header (0x02) in your request. You can start to implement support for packets in your "send command" functions. Refer to the "Transport / Packet Layer" section for more information.

#### Example:
```
--> 02 20 02
<-- 1B 60 02 ?? ?? ?? ?? ??
<-- 21 ?? ?? ?? ??

// Print "?? ?? ... ?? ??" as a string (Hint, it's ASCII text)
'?????????'
```

## Task #05 - Length Byte / Receiving More Frames

Implement support for receiving packets longer than 15 bytes.

msg_send() and msg_recv() are limited to 8 bytes per message or "frame" (similar to CAN2.0). To work around this limitation our protocol uses a simple header byte at the start of every message. This header byte contains an opcode and the total length of data. Up until now this header byte has been hardcoded into our messages. Refer to the "Transport / Packet Layer" section for more information.

For this task use a data identifier of 0x03 and print the result as a string. The result will be spread across multiple frames and is longer than . Do not print the header / length bytes.

Note, be sure to include the header (0x02) in your request. You **should** implement packet support in your "send command" functions. Refer to the "Transport / Packet Layer" section for more information.

#### Example:
```
--> 02 20 03

<-- 10 14 60 03 ?? ?? ?? ??
<-- 21 ?? ?? ?? ?? ?? ?? ??
<-- 22 ?? ?? ?? ?? ?? ?? ??
<-- 23 ??

// Print "?? ?? ... ?? ??" as a string (Hint, it's ASCII text)
'???????????????????'
```

## Task #06 - Sending Multiple Frames / Calculating Checksums

Use the "Write" command to write data to the server. Calculate and send the required checksum.

The "Write" (0x21) command takes 3 parameters; The first parameter is the "Data Identifier" which specifies what the data is/where it should be written to; The second parameter is the Data which is being written; And the final parameter is an 8-bit checksum.

For this task use a **data identifier of 0x04** and **send exactly 20 bytes**, the contents is up to you. Be sure to calculate and include the checksum according to the following definition:
```c
CHECKSUM = INVERSE(SUM8(data))
```

Note, you **should** implement the checksum calculation as part of your solution. Do not hardcode this value in.

#### Example 1 (Correct Checksum / Data Accepted):
```
--> 10 16 21 04 xx xx xx xx
--> 21 xx xx xx xx xx xx xx
--> 22 xx xx xx xx xx xx xx
--> 23 xx xx CS

// Server accepts the data / checksum
<-- 02 61 04

// Optionally read the data back with the "Read" command
--> 02 20 04
<-- 10 15 60 04 xx xx xx xx
<-- 21 xx xx xx xx xx xx xx
<-- 22 xx xx xx xx xx xx xx
<-- 23 xx xx
```

#### Example 2 (Incorrect Checksum / Data Rejected):
Note, Refer to the "Negative Response Code" Table to help with debugging the server's response.
```
--> 10 16 21 04 xx xx xx xx
--> 21 xx xx xx xx xx xx xx
--> 22 xx xx xx xx xx xx xx
--> 23 xx xx CS

<-- 03 7F 21 16
```

## Task #07 - Client Authentication / Data Manipulation

Use the "Seed" and "Auth" commands to authenticate your client with the server. Read the seed from the server, calculate and send the key back.

The "Seed" (0x30) command returns two 32-bit integers (big-endian), these are the seed values to use with your key calculation. The client should calculate the 32-bit key according to the following definition:
```c
KEY = XOR(ADD(SEED[0],SWAP(SEED[1])),0x20240701);
```

Once calculated, the client uses the "Auth" (0x31) command to send the key for validation (big-endian). If correct, the server will respond with a Positive Request. Once authenticated the client can use the "Read" (0x20) command to access Data Identifier `0x50`, for this task print the result of this read command as a string. 

Note, the seed values returned by the server are random. The following example is for reference only.

#### Example:
```
// Request Seed
--> 01 30
<-- 19 70 01 23 45 67 89 AB
<-- 21 CD EF

// Authenticate key
--> 05 31 D0 D4 F7 F1
<-- 01 71

// Read protected data
--> 02 20 05
<-- 10 14 60 05 ?? ?? ?? ??
<-- 21 ?? ?? ?? ?? ?? ?? ??
<-- 22 ?? ?? ?? ?? ?? ?? ??
<-- 23 ??

// Print "?? ?? ... ?? ??" as a string (Hint, it's ASCII text)
'???????????????????'
```

---

# Protocol

This section serves as a rudimentary description of the hypothetical protocol used in this evaluation. **It is intentionally vague**. Much of this information is provided in `src/lib/proto.h`.

The above tasks will require you to implement a mix of a Packet and Command layers. These layers are built ontop of a provided Message / Datalink layer.

## Message / Datalink Layer (See `src/lib/msg.c`)

This layer is responsible for the transfer of "message frames" between the client and the server. Each message can contain between 1 to 8 bytes of data.

This layer is implemented in `src/lib/msg.c` and you do not need to edit this file or implement this layer. For this evaluation you will only need to use `msg_send()` and `msg_recv()`. Opening / Closing the connection is already handled for you in `src/client.c`.

## Packet Layer

The packet layer is responsible for transfering "packets" between the client and the server. This layer allows individual packets to exceed the 8 byte limit of message / datalink layer.

In general the packet format can be described as:
```
Format [Length] Data..
```

### Format Byte

The purpose of the Format Byte is to tell the receiving client/server how to interpret this message frame and in some cases the messages which follow. It's primarily use is to link multiple frames together to form packets larger than 8 bytes.

The format byte is divided into two 4-bit nibbles. The first of which is the Frame "Opcode". This Opcode tells the receiving client/server how to interpret this message frame and in some cases the messages which follow. Depending 

There are three Opcodes defined by this protocol. Depending on the Opcode, the second 4-bit nibble encodes the `Length` of Packet* or the `Sequence Number`: 

   - **Single Frame**
     ```
     0L ..      - Opcode of 0, Length equal to L (Up to 15 bytes) *
     00 LL ..   - Opcode of 0, Length equal to LL+1 (Up to 256 bytes) *
     ```
   - **First Frame**
     ```
     1L ..      - Opcode of 1, Length equal to L (Up to 15 bytes) *
     10 LL ..   - Opcode of 1, Length equal to LL+1 (Up to 256 bytes) *
     ```
   - **Consecutive Frame**
     ```
     2N ...      - Opcode of 2, Sequence number included
     ```
    
`*` The Packet Length is given by the lower 4 bits of the format byte which allows upto 15 bytes in length. In cases where the packet exceeds 15 bytes a length of `0` is used and an additional length byte is included. This extra byte allows a total packet length of upto 256 bytes.

#### Single Frame (Format = `0x0_`)

An Opcode of `0` indicates that the packet is fully contained in a single message frame (ie,. Data is 7 bytes or less). 

#### First Frame (Format = `0x1_`) and Consecutive Frames (Format = `0x2_`)

If the packet is larger than 7 bytes the data is split across multiple messages. To save bandwidth we only encode the Length in the First Frame. The remaining data is transfered using Consecutive Frames.

To ensure data is received in order / without missing messages, each Consecutive frame contains a `Sequence Number`. For each Packet, this 4-bit number starts at `1` and increments with each Consecutive Frame. The receiver should ignore any messages with the incorrect `Sequence Number`. Consecutive Frames must be sent within the Timeout period, incomplete messages are ignored without Acknowledgement.

## Command Layer

The Command Layer describes the contents of the Packet and allows the client to interface with the server. 

The server only responds to incoming commands / requests from the client, it will not initiate contact on it's own. The general, command sequence is as follows:
```
Client --> Server: Sends Command
Client <-- Server: Sends Response
```

### Command Requests

Each command is comprised of a `CommandId` (or CID) and an optional list of Parameters. The number and content of these parameters depends on the CID being executed. 

```
CommandId [Parameters...]
```

#### Positive Responses

If the command was successful the server will reply with this CID's `Positive Response Code` (PRC) and an optional set of Response Parameters / Data. Again, the contents and number of parameters depends on the CID that was executed.

```
PRC [Parameters...]
```

The `Positive Response Code` (PRC) is a unique code which corresponds to each `CommandID`/CID. In general it is calculated as:

```c
PRC = CID + 0x40
```

#### Negative Responses

If the command was unsuccessful the server will reply with a `Negative Response`. This response contains a `Negative Response Code` (or NRC) which indicates the reason for the unsuccessful result. All `Negative Response`s are 3 bytes long, containing `0x7F` followed by the CID, and finally the NRC.

```
7F CID NRC
```

The meaning of the `Negative Response Code` (NRC) is as follows:

```
0x10 - General Reject (Used if a more specific NRC is not available)
0x11 - Unknown or Unsupported Command ID
0x12 - Command sequence error (Another command or commands were expected first)
0x13 - Parameter not supported, or invalid parameter format
0x14 - Parameter request out of range
0x15 - Invalid data / length or incorrect key
0x16 - Invalid checksum
0x17 - Access denied, authenication required
```

### Command Definitions

#### PING Request
- PING Request:
    - `Byte 0`    - Command ID (CID) = `0x10`
- Positive PING Response:
    - `Byte 0`    - Positive Response Code (PRC): `0x50`
- Negative PING Response
    - None (Should always return the Positive Response)

##### Example (Packet Layer Omited):
```
--> 10  - PING Request
<-- 50  - Positive PING Response
```

#### READ Request
- READ Request:
    - `Byte 0`    - Command ID (CID) = `0x20`
    - `Byte 1`    - Data Identifier
- Positive READ Response:
    - `Byte 0`    - Positive Response Code (PRC): `0x60`
    - `Byte 1`    - Data Identifier
    - `Byte 2:2+N`- Data[`N` Bytes]
- Negative READ Response:
    - See "Negative Responses" section

##### Example (Packet Layer Omited):
```
--> 20 01       - READ Request (Data Identifier = 0x01)
<-- 60 01 XX..  - Positive READ Response (Data Identifier = 0x01, Data = XX..)
```

#### WRITE Request
- WRITE Request:
    - `Byte 0`    - Command ID (CID) = `0x21`
    - `Byte 1`    - Data Identifier
    - `Byte 2:2+N`- Data[`N Bytes`]
    - `Byte 2+N`  - Checksum
        - The Checksum is given as `INVERSE(SUM8(Data))`
- Positive WRITE Response:
    - `Byte 0`    - Positive Response Code (PRC) = `0x61`
    - `Byte 1`    - Data Identifier
- Negative WRITE Response:
    - See "Negative Responses" section

##### Example (Packet Layer Omited):
```
--> 21 04          - WRITE Request (Data Identifier = 0x04)
<-- 60 04 XX.. CS  - Positive WRITE Response (DataId=0x04, Data=XX.., Checksum=CS)
```

#### SEED Request
- SEED Request:
    - `Byte 0`    - Command ID (CID) = `0x30`
- Positive SEED Response:
    - `Byte 0`    - Positive Response Code (PRC) = `0x70`
    - `Byte 1:9`  - Seed[`8 Bytes`]
        - The Seed is two 32-bit unsigned integers
- Negative SEED Response:
    - See "Negative Responses" section

##### Example (Packet Layer Omited):
```
--> 30       - SEED Request
<-- 70 XX..  - Positive SEED Response (Seed=XX..)
```

#### AUTH Request
- AUTH Request:
    - `Byte 0`    - Command ID (CID) = `0x31`
    - `Byte 1:5`  - Key[`4 Bytes`]
        - The key is a 32-bit unsigned integer
- Positive AUTH Response:
    - `Byte 0`    - Positive Response Code (PRC) = `0x71`
- Negative AUTH Response:
    - See "Negative Responses" section
    
##### Example (Packet Layer Omited):
```
--> 31 XX.. - AUTH Request (Key=XX..)
<-- 71      - Positive AUTH Response
```

---
