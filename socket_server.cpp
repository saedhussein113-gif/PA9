/*
 * Authors: CB, SH, YG, LF
 * Course: CPTS 122
 * Assignment: Programming Assignment 9
 * Project: Pac-Man
 *
 * File: socket_server.cpp
 *
 * Description:
 * This file implements an interactive TCP client using Winsock2
 * that allows a user to manually send movement commands to the
 * Pac-Man game server. The user inputs commands through the console,
 * then they are transmitted to the server  for real-time control.
 *
 * Features:
 * - Console-based user input for commands
 * - Sends commands to server at 127.0.0.1:8080
 * - Uses helper function for socket communication
 * - Supports continuous command input until user exits
 *
 * Date: April 25, 2026
 */

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
//extra credit socket code for sending command to server
void sendCommand(string command)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (sockaddr*)&server, sizeof(server));

    send(clientSocket, command.c_str(), command.length(), 0);

    closesocket(clientSocket);
    WSACleanup();
}

int main()
{
    string command;

    cout << "Pac-Man Network Controller\n";
    cout << "Type UP, DOWN, LEFT, RIGHT, or QUIT\n";

    while (true)
    {
        cout << "Command: ";
        cin >> command;

        if (command == "QUIT")
            break;

        sendCommand(command);
    }

    return 0;
}