#include<stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/errno.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100 
extern int errno;
// structure for mesage queue
struct buff
{
long type;
char data [256];
} message;
void server(id)
int id;
{
int n;
printf("\n Server started\n");
printf("\n Server preparing data to send on queue Type :2");
printf("\n UPK-server- Enter text: "); fgets(message.data, MAX, stdin);
message.type=2;
if (msgsnd(id, &message, sizeof(message.data),0) == -1) printf("\n Server Error \n");
printf("\n Server sent data to client \n");
printf("\n Server about to read queue Type : 1 \n");
n=msgrcv(id, &message, sizeof(message),1,0);
if(n < 0)
printf("\nServer cant receive\n");
else printf("\nSERVER : got %s from CLIENT\n",message.data);
}
int main()
{
int i;
key_t key;
int id;
// ftok to generate unique key
 key = ftok("progfile", 65);
if ((id=msgget (key, 0666| IPC_CREAT)) <0) {
printf("Server : CAN'T creat MESSAGE QUEUE \n"); exit(0);
}
server(id);
if( msgctl(id, IPC_RMID, 0 ) < 0 )
{
printf("Server cant REMOVE MESSAGE QUEUE \n");
// msgctl() performs the control operation specified by cmd.
//Refer manual for this.
}
//exit(0);
exit(0);
}