#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <global.h>

//Send some data
char message[512];
char server_reply[512];

//Receive a reply from the server
int recv_size;
int id_src;

int x_vel2,y_vel2,x_plus2,y_plus2,block_index2,x_block2,y_block2;
int idt,x_velt,y_velt,x_plust,y_plust,block_indext,x_blockt,y_blockt;
bool movingt;
char dirt;
char flagt;
int vote;
int votet;

bool connected=false;

SOCKET s;

struct arg_struct {
    SOCKET c;
};

// Send player coords
void send_coords()
{
    sprintf(message, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%c:%d:%c", id_src, player.x_vel, player.y_vel, player.x_plus, player.y_plus, player.block_index, player.x_block, player.y_block, player.moving, player.dir, player.vote, player.flag);
    send(s , message , 512 , 0);
}

// Receive data from server usually 2nd player's data
void* receive_data(void* arguments)
{
    do
    {
        if(recv(s , server_reply , 512 , 0)!=SOCKET_ERROR)
        {   
            sscanf(server_reply, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%c:%d:%c", &idt, &x_velt, &y_velt, &x_plust, &y_plust, &block_indext, &x_blockt, &y_blockt, &movingt, &dirt, &votet, &flagt);

            if(id_src!=idt)
            {
                connected=true;
                player2.x_vel=x_velt;
                player2.y_vel=y_velt;
                player2.x_plus=x_plust;
                player2.y_plus=y_plust;
                player2.block_index=block_indext;
                player2.x_block=x_blockt;
                player2.y_block=y_blockt;
                player2.dir=dirt;
                player2.moving=movingt;
                player2.vote=votet;
                player2.flag=flagt;
            }
        }

    } while (1);
}

// Setup socket, send id and start receiving/sending data
void* main_client()
{
	WSADATA wsa_data;

	struct sockaddr_in server;
    struct arg_struct a;

    // initialize winsock
	if (WSAStartup(MAKEWORD(2,2), &wsa_data) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
        WSACleanup();
		return NULL;
	}
	
	//Create a socket

	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
        WSACleanup();
	}
	
    // give the server we want to connect to
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 1337 );

	//Connect to remote server

    do
    {
        if (connect(s , (struct sockaddr*)&server , sizeof(server)) >= 0)
        {
            break;
        }
    } while (1);
    
	
	printf("Connected\n");

    // get id
    
    do
    {
        recv_size = recv(s , server_reply , 512 , 0);

        if(recv_size!=SOCKET_ERROR)
        {   
            server_reply[recv_size] = '\0';
            sscanf(server_reply, "%d", &id_src);
            printf("My id is %d\n",id_src);
            player_count++;
            break;
        }
        
    } while (1);

    pthread_t thread;
    a.c = s;

    pthread_create(&thread, NULL, receive_data, &a);

    return NULL;
}