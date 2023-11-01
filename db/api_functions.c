// api_functions.c
#include "api_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 2048

void api(const char *path) {
    int sock;
    struct sockaddr_in server;
    int port = 3000;
    char buffer[BUFFER_SIZE];
    char *ip_address = "64.227.121.226";

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server info
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_address, &server.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Send HTTP GET request
    sprintf(buffer, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, ip_address);
    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Receive the response
    printf("HTTP response:\n");
    while (1) {
        ssize_t received_len = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (received_len < 0) {
            perror("recv failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        if (received_len == 0) {
            break;
        }

        buffer[received_len] = '\0';
        printf("%s", buffer);
    }

    // Close the socket
    close(sock);
}

char *api_json(const char *path) {
    int sock;
    struct sockaddr_in server;
    int port = 3000;
    char buffer[BUFFER_SIZE];
    char *ip_address = "64.227.121.226";
    char *body = NULL;

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return NULL;
    }

    // Set server info
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_address, &server.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        close(sock);
        return NULL;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(sock);
        return NULL;
    }

    // Send HTTP GET request
    sprintf(buffer, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, ip_address);
    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");
        close(sock);
        return NULL;
    }

    // Receive the response
    ssize_t received_len = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (received_len < 0) {
        perror("recv failed");
        close(sock);
        return NULL;
    }

    buffer[received_len] = '\0'; // Null-terminate the buffer

    // Find the start of the JSON body
    char *json_start = strstr(buffer, "\r\n\r\n");
    if (json_start) {
        json_start += 4; // Skip the header
        body = strdup(json_start);
    } else {
        body = strdup(""); // No body received
    }

    // Close the socket
    close(sock);

    return body; // The caller is responsible for freeing this memory
}
