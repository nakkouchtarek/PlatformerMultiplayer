#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1337"
#define NUM_THREADS 2

char recvbuf[DEFAULT_BUFLEN];
char phrase[NUM_THREADS][DEFAULT_BUFLEN];

int recvbuflen = DEFAULT_BUFLEN;
int i=0;

SOCKET clients[NUM_THREADS];
pthread_t threads[NUM_THREADS];

struct arg_struct {
    SOCKET c;
    int id;
};

int tmp;

void* send_all()
{
    do
    {
       for(int x=0;x<i;x++)
        {
            switch(x)
            {
                case 0:
                    tmp=1;
                    break;
                case 1:
                    tmp=0;
                    break;
            }
            
            if(send( clients[x], phrase[tmp], 512, 0 )==SOCKET_ERROR)
            {
                printf("Client %d disconnected\n",x);
                closesocket(clients[x]);
                i--;
            }        
        }

        usleep(10000);

    } while (1);

    pthread_exit(NULL);
    return NULL;
}

void* handle_client(void* arguments)
{
    struct arg_struct args = *(struct arg_struct *)arguments;

    SOCKET client = args.c;
    int id = args.id;

    int idt, x_velt, y_velt, x_plust, y_plust, block_indext, x_blockt, y_blockt;
    int current_level;
    char dir;
    bool movingt;
    char flag;
    int vote;
    int recv_size;
    int p_count;

    do
    {
        if(i==NUM_THREADS)
        {
            sprintf(phrase[id], "%d", id);
            send( client, phrase[id], strlen(phrase[id]), 0 );
            break;
        }

    } while(1);

    switch(id)
    {
        case 0:
            tmp=1;
            break;
        case 1:
            tmp=0;
            break;
    }

    do
    {
        do
        {
            recv_size = recv(client, recvbuf, 512, 0);

            if(recv_size != SOCKET_ERROR)
            {
                break;
            }

           usleep(10000);

        } while (recv_size == SOCKET_ERROR);

        sscanf(recvbuf, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%c:%d:%c", &idt, &x_velt, &y_velt, &x_plust, &y_plust, &block_indext, &x_blockt, &y_blockt, &movingt, &dir, &vote, &flag);
        memcpy(phrase[idt], recvbuf, strlen(recvbuf));
        
    } while (1);
    
    if (shutdown(client, SD_SEND) == SOCKET_ERROR) 
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(client);
        WSACleanup();
        return NULL;
        pthread_exit(NULL);
    }

    return NULL;
    pthread_exit(NULL);
}

int main() 
{
    WSADATA wsaData;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    SOCKET tmp;
    struct arg_struct a;
    pthread_t thread1;
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed");
        return 1;
    }

    // clear struct memory space
    ZeroMemory(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    
    if ( getaddrinfo(NULL, DEFAULT_PORT, &hints, &result) != 0 ) {
        printf("getaddrinfo failed");
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket

    if (bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No more use for result
    freeaddrinfo(result);

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    

    printf("Looking for clients...\n");

    pthread_create(&thread1, NULL, send_all, NULL);

    do
    {
        tmp = accept(ListenSocket, NULL, NULL);

        if (tmp == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return -1;
        }
        else
        {
            printf("Client %d connected\n",i);

            clients[i] = tmp;

            a.c = clients[i];
            a.id = i;

            pthread_create(&threads[i], NULL, handle_client, &a);

            i++;
        }
        
    } while (i<=NUM_THREADS);

    return 0;
}