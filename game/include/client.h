#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <global.h>

extern bool connected;
extern int vote;
extern SOCKET s;
extern bool connected;

void* receive_data(void* arguments);
void* main_client();
void send_coords();