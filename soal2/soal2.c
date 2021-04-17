#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int status;
void soal2a();
void soal2b();

int main()
{
  soal2a();
  soal2b();
  soal2c();
  soal2d();
  soal2e();
  return 0;
}

void soal2a()
{
  pid_t child_id;
  child_id=fork();

  if(child_id<0){
    exit(1);
  }

  if(child_id==0){
    char *argv[]={"mkdir","-p","/home/dewi/modul2/petshop",NULL};
    execv("/usr/bin/mkdir",argv);
  }
  
  else{

    //*.jpg agar yg terunzip hny file jpg
    char *argv[]={"unzip","/home/dewi/modul2/pets.zip","-d","/home/dewi/modul2/petshop","*.jpg",NULL};
    execv("/usr/bin/unzip",argv);
  }
}
