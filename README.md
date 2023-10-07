# Minitalk Project

![Project Status](https://img.shields.io/badge/status-complete-brightgreen.svg)

Minitalk is a program that facilitates communication between two distinct processes using UNIX signals, specifically `SIGUSR1` and `SIGUSR2`. The project comprises two executables: the `server` and the `client`. Both programs are crafted to handle signal transmission and reception, thereby allowing them to communicate messages in real-time.

## Table of Contents
- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Functionality](#functionality)
- [Acknowledgments](#acknowledgments)
- [Bonus Features](#bonus-features)
- [Conclusion](#conclusion)
- [Credits](#credits)

## Description

The core functionality of Minitalk lies in the transmission of a string from the client to the server using only UNIX signals. Instead of traditional character or string-based communication, messages are communicated bit-by-bit via the aforementioned signals.

## Installation

```bash
git clone <repository-url>
cd minitalk
make
```

## Usage

### Server

Begin by starting the server:

```bash
./server
```

The server will display its process ID (PID) upon startup. This PID is required to start the client.

### Client

Start the client by passing the server's PID and the message to be sent as arguments:

```bash
./client <server-pid> <message>
```

Replace `<server-pid>` with the PID displayed by the server upon startup. Replace `<message>` with the message to be sent to the server.

## Functionality

### Signal Handling:
The primary method of communication is through the signals SIGUSR1 and SIGUSR2. A binary representation of each character in the string is sent bit by bit. For instance, if the bit is 1, SIGUSR1 is sent; if 0, SIGUSR2 is dispatched.

### Server Operation:
- Displays its PID upon launch.
- Waits and listens for incoming signals.
- Reconstructs each character from the received bits.
- Prints the character once fully received.
- Continues to receive and print characters until the client signals the end of the transmission.

### Client Operation:
- Validates the provided server PID.
- Converts the message string into a series of bits.
- Transmits each bit as a SIGUSR1 or SIGUSR2 signal to the server.
- Signals the end of the message transmission.

## Acknowledgments
- The server has to quickly display the string. For a standard of quickness, if 100 characters take longer than 1 second, it's considered too lengthy.
- The server should be capable of receiving strings from various clients sequentially without restarting.
- The entire communication is solely based on UNIX signals.

## Bonus Features

### Server Acknowledgment:
After successfully receiving a message, the server sends an acknowledgment signal back to the client.

### Unicode Character Support:
Both the client and server are enhanced to support and accurately convey Unicode characters.

## Conclusion
Remember, this project showcases the power of UNIX signals and their potential use in inter-process communication. The uniqueness of Minitalk is in its simplicity, harnessing the fundamental building blocks of the UNIX operating system to achieve a basic but robust communication platform.

## Credits 
 - Developed by: williamroocha
 - Project for: 42 Lisboa