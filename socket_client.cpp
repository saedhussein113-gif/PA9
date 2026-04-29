
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
//extra credet socket code
int main()
{
WSADATA wsa;
WSAStartup(MAKEWORD(2,2), &wsa);

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
