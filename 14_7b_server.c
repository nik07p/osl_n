#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
 #define MAXSIZE 40
 
 void die(char *s){
   perror(s);
   exit(1);
   
 }
 
 int main(){
   char c;
   int shmid;
   key_t key;
   char *shm,*s;
   key=400;
   
   if((shmid=shmget(key,MAXSIZE,IPC_CREAT | 0666))<0){
     die("shmget");
   }
   
   if((shm=shmat(shmid,NULL,0))==(char *)-1)
{
   die("shmat");
} 

s=shm;

for(c='A';c<='Z';c++){
*s++=c;
}

while(*shm !='+'){
   sleep(1);
 }
 
 exit(0);
  
 }
