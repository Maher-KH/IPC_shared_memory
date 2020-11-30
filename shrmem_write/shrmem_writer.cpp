#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <fstream>

#define SHR_MEM_SEG_SIZE 1024

using namespace std;
  
int main()
{ 
    /* ftok to generate unique key
       convert a pathname and a project identifier to a System V IPC key
       key_t ftok(const char *pathname, int proj_id);
    */ 
    key_t key = ftok("shmfile",65);
  
    /*  int shmget(key_t,size_tsize,intshmflg); 
    upon successful completion, shmget() returns an identifier for the shared memory segment.*/
    int shmid = shmget(key,SHR_MEM_SEG_SIZE,0666|IPC_CREAT);
  
    /* Before you can use a shared memory segment, you have to attach yourself
      to it using shmat(). 
      void *shmat(int shmid ,void *shmaddr ,int shmflg);
      shmid is shared memory id. shmaddr specifies specific address to use but we should set
      it to zero and OS will automatically choose the address */
  
    char *str = (char*) shmat(shmid,(void*)0,0);
    //str = file.seekg(0);    // will move the get_pointer (in ifstream) to byte number 00 in the file

    cout<<"Write Data : ";
    fgets(str, sizeof(str), stdin);
  
    cout<<"Data written in memory: "<< str << endl;
      
    /* detach from shared memory  
      When you’re done with the shared memory segment, your program should
      detach itself from it using shmdt(). int shmdt(void *shmaddr);
    */
    shmdt(str);

    return 0;
}

