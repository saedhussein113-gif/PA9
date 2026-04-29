/*Authors: CB, SH, YG, LF
* Course : CPTS 122
* Assignment : Programming Assignment 9
* Project : Pac - Man
*
*File : NetworkServer.hpp
*
*Description :
*Implements a basic socket server using Winsock.
* The server listens on port 8080 for incoming client connections
* and receives simple command input.
* Commands are stored using a mutex and can be accessed
* by the main game loop.
*  fundamental logic of sockets were learned through youtube videos.
*
* Key Features :
*-Runs on a separate thread
* -Uses Winsock2 for networking
* -Lightweight communication for game input
*
* Date: April 25, 2026
*/
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class NetworkServer
{
private:
    std::string lastCommand;
    std::mutex commandMutex;
    bool running;

public:
    NetworkServer()
    {
        running = true;
        lastCommand = "";
    }

    void start()
    {
        std::thread serverThread(&NetworkServer::runServer, this);
        serverThread.detach();
    }

    std::string getCommand()
    {
        std::lock_guard<std::mutex> lock(commandMutex);
        std::string command = lastCommand;
        lastCommand = "";
        return command;
    }

    void stop()
    {
        running = false;
    }

private:
    void runServer()
    {
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);

        SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(8080);

        bind(serverSocket, (sockaddr*)&server, sizeof(server));
        listen(serverSocket, 5);

        std::cout << "Pac-Man socket server running on port 8080...\n";

        while (running)
        {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

            if (clientSocket != INVALID_SOCKET)
            {
                char buffer[100] = {};
                recv(clientSocket, buffer, 100, 0);

                {
                    std::lock_guard<std::mutex> lock(commandMutex);
                    lastCommand = buffer;
                }

                closesocket(clientSocket);
            }
        }

        closesocket(serverSocket);
        WSACleanup();
    }
};