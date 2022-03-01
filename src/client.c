#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include "client.h"
#include "bomberman.h"

#pragma comment(lib,"WS2_32")

#define IP "127.0.0.1"
#define PORT 9999

int s;
struct sockaddr_in sock;

int init_socket()
{
    #ifdef _WIN32
        // this part is only required on Windows: it initializes the Winsock2 dll
        WSADATA wsa_data;
        if (WSAStartup(0x0202, &wsa_data))
        {
            printf("unable to initialize winsock2\n");
            return -1;
        }
    #endif

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
    {
        printf("unable to initialize the UDP socket\n");
        return -1;
    }

    printf("socket %d created\n", s);

    struct sockaddr_in sin;
    inet_pton(AF_INET, IP, &sock.sin_addr); // this will create a big entian 32 bit address
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PORT); // converts 9999 to big endian
    return 0;
}

int send_data(int player_id, float x, float y)
{
    packet_t packet = {player_id, x, y};
    char msg[12];
    memcpy(msg, &packet, 12);
    int sent_bytes =sendto(s, msg, 12, 0, (struct sockaddr*)&sock, sizeof(sock));
    char addr_as_string[64];
    inet_ntop(AF_INET, &sock.sin_addr, addr_as_string, 64);
    printf("sends %d bytes to %s \n", sent_bytes,addr_as_string);
    return 0;
}

char* recive_data()
{
    char buffer[8192];
    struct sockaddr_in sender_in;
    int sender_in_size = sizeof(sender_in);

    int len = recvfrom(s, buffer, 8192, 0, (struct sockaddr*)&sender_in, &sender_in_size);
    if(len > 0)
    {
        char msg[12];
        inet_ntop (AF_INET, &sender_in .sin_addr , msg , sizeof(packet_t));
        printf("received %d bytes from %s:%d\n", len, msg, ntohs(sender_in.sin_port));

        return msg;
    }
    return NULL;
}
