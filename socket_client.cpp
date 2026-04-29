/*
 * Authors: CB, SH, YG, LF
 * Course: CPTS 122
 * Assignment: Programming Assignment 9
 * Project: Pac-Man
 *
 * File: socket_client.cpp
 *
 * Description:
 * This file implements a simple TCP client using Winsock2.
 * It connects to the local game server (127.0.0.1:8080)
 * and sends movement commands like UP, DOWN, LEFT and RIGHT.
 * This enables external or network-based control of the Pac-Man game.
 * fundamental logic of sockets were learned through youtube videos.
 *
 * Features:
 * - Establishes socket connection to server
 * - Sends command messages to control gameplay
 * - Demonstrates basic client-server communication
 *
 * Date: April 25, 2026
 */

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
//extra credet socket code, watched online youtube videos for guidance.
int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(client, (sockaddr*)&server, sizeof(server));

	const char* msg = "UP";
	send(client, msg, strlen(msg), 0);

	closesocket(client);
	WSACleanup();
}