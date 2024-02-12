#include<stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/errno.h>
#include <stdlib.h>
#define MAX 100
extern int errno;
// structure for mesage queue
struct buff
{
long type;
char data [256];
} message;
// Client routine 
 void client(int id)
{
int n;
printf("\n Client is about read from server Type: 2 \n");
n=msgrcv(id,&message, sizeof(message),2,0);
if (n < 0){
printf("Client cant receive\n");
}
else 
printf("CLIENT got *%s* from SERVER\n", message.data);
printf("\n Client ready to send data of Type : 1 \n \n");
printf("\n UPK-Client- Enter text: ");
fgets(message.data, MAX, stdin);
message.type=1;
if (msgsnd(id, &message, sizeof(message.data),0)== -1) printf("Client error\n");
printf("\n client sent data Type: 1 \n");
printf("\n client terminating now \n");
}
int main()
{ int id; key_t key;
        key = ftok("progfile",65);
        if ( (id= msgget (key, 0666|0666) ) <0)
{ printf("CLIENT: CAN'T GET MESSAGE QUEUE\n"); exit(0);
} client(id);
}