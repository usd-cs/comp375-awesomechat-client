/*
 * client.c
 *
 * Authors:
 *  1) Partner A's name (and email)
 *  2) Partner B's name (and email)
 *  3) Dr. Sat Garcia (sat@sandiego.edu)
 *
 * 	USD COMP 375: Computer Networks
 * 	Mini Project #1
 *
 * This is the client that will talk to the chat server.
 *
 * Clients can do one of the following:
 * 	- Introduce themself (MYNAMEIS foo)
 * 	- List current users (LIST)
 * 	- Send a message to another user (SENDTO bar : hello world)
 * 	- Get messages (GET)
 *
 */

#define _XOPEN_SOURCE 600

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define BUFF_SIZE 1024

long prompt();
int connect_to_host(char *hostname, char* port);

int main() {
	// TODO: connect to hopper.sandiego.edu on port 7099 by calling the
	// connect_to_host function. Note that the second parameter should be a
	// string (e.g. "7099", not an integer (i.e. 7099).

	printf("Welcome to the AwesomeChat: The COMP375 chat server.\n\n\n");

	printf("Please enter a username: ");

	// buff will be the array we use to send and receive data to/from the
	// server
	char buff[BUFF_SIZE];
	memset(buff, 0, BUFF_SIZE); // this makes every character '\0', i.e. NUL

	// Start by sending username request to server
	strcpy(buff, "MYNAMEIS ");

	char name_buff[100];
	memset(name_buff, 0, 100);

	// TODO: use fgets() to store user entered name in name_buff. Check the
	// use of fgets in the prompt function later in this file and/or review
	// the fgets manual (i.e. "man fgets") to find the number and type of
	// parameters needed when calling this function.

	strcat(buff, name_buff); // append name to end of buff

	// TODO: send the message in buff using send() function (Beej's Guide,
	// Section 5.7 talks about send()).
	// TODO (later): error check send result

	memset(buff, 0, BUFF_SIZE);

	// TODO: receive response from server for MYNAMEIS command
	// Use recv() to store the message in buff (again, see Beej's Guide,
	// Section 5.7).

	// TODO (later): error check recv() result

	// TODO: Use the strstr function to see if response starts with "BAD"
	
	memset(buff, 0, BUFF_SIZE);

	// Connect to server until ctl-c and return sensor reading or error message
	while (true) {
		long selection = prompt();

		switch (selection) {
			case 1:
				// Send request to server for a list of users
				// TODO: send LIST request

				// TODO: receive and handle server response to LIST
				
				memset(buff, 0, BUFF_SIZE);

				break;

			case 2:
				// Send a message to another user
				// prompt user for username
				printf("Enter username of recipient: ");

				memset(buff, 0, BUFF_SIZE);
				memset(name_buff, 0, 100);

				strcpy(buff, "SENDTO ");

				// TODO: use fgets to read user input into name_buff
				
				// TODO: use strcat to append name_buff to buff

				// TODO: use strcat to append " : " to buff

				// prompt user for message
				char msg_buff[BUFF_SIZE];
				memset(msg_buff, 0, BUFF_SIZE);

				printf("Enter the message to send: ");

				// use fgets to read input into msg_buff
				fgets(msg_buff, BUFF_SIZE, stdin);

				// TODO: use strcat to append msg_buff to buff

				// TODO: send the completed SENDTO request (stored in buff)

				memset(buff, 0, BUFF_SIZE);

				// TODO: receive and handle server response
				// Make sure it doesn't start with "BAD"

				printf("Message sent\n");

				memset(buff, 0, BUFF_SIZE);

				break;

			case 3:
				// Print the messages we haven't received yet
				// TODO: send a GET request

				// TODO: handle server response
				// In response to a GET, the server will send each message on
				// its own line. Often this will require only a single recv,
				// but be safe, you should continually call recv until you
				// get "DONE\n" as part of the message.
				// You can use the strstr function to check whether one string
				// (e.g. "DONE\n") is contained within another one (i.e. the
				// full buffer).
				
				break;

			case 4:
				// Exit the program gracefully.
				printf("Thanks for using AwesomeChat!\n");

				// TODO: close the connection using the close function

				exit(0);
				break;

			default:
				printf("\n*** Invalid selection.\n\n");
				break;
		}
	}

	// Should never get to this point so return 1 for "error"

	// TODO: close the connection
	return 1;
}

/* 
 * Print command prompt to user and obtain user input.
 *
 * @return The user's desired selection, or -1 if invalid selection.
 */
long prompt() {
	printf("What would you like to do?\n\n");
	printf("\t(1) Print list of users that are currently online.\n");
	printf("\t(2) Send a message to another user.\n");
	printf("\t(3) Print your messages.\n");
	printf("\t(4) Quit Program\n\n");
	printf("Selection: ");

	char input[10];
	memset(input, 0, 10); // set all characters in input to '\0' (i.e. NUL)
	fgets(input, 10, stdin); // get input from the standard (command line) input

	// get rid of newline, if there is one
	char *new_line = strchr(input, '\n');
	if (new_line) new_line[0] = '\0';

	// convert string to a long int
	char *end;
	long sensor = strtol(input, &end, 10);

	if (end == input || *end != '\0') {
		sensor = -1;
	}

	return sensor;
}

/*
 * Socket implementation of connecting to a host at a specific port.
 *
 * @param hostname The name of the host to connect to (e.g. "foo.sandiego.edu")
 * @param port The port number to connect to
 * @return File descriptor of new socket to use.
 */
int connect_to_host(char *hostname, char *port) {
	// Step 1: fill in the address info in preparation for setting up the socket.
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

	// Get ready to connect to the hostname and port given as parameters to
	// this (i.e. connect_to_host) function.
	// TODO: make a call to getaddrinfo (see Beej's guide Section 5.1).
	status = getaddrinfo(/*FIXME*/);

	// Step 2: Make a call to socket() to create a socket.

	// TODO: call socket (again, see Beej's guide for help, this time Section
	// 5.2)
	int fd = socket(/*FIXME*/);

	// TODO: make a call to connect (Beej's guide, section 5.4)

	// free memory that was allocated by getaddrinfo
	freeaddrinfo(servinfo);

	// TODO: Replace -1 with the value returned by socket so that we return
	// the file descriptor for the socket
	return -1;
}
