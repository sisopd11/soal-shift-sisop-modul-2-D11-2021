#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<wait.h>
#include<string.h>
#include<dirent.h>

void soal2b(char *basePath);
void soal2a();

int main()
{
   soal2a();
}

void soal2a()
{
  int status;
  pid_t child_id;
  child_id=fork();

  if(child_id<0){
    exit(1);
  }

  if(child_id==0){
      char *argv[]={"unzip","/home/dewi/modul2/pets.zip","-d","/home/dewi/modul2/petshop","*.jpg",NULL};
      execv("/usr/bin/unzip",argv);
  }

  else
  {
     while(wait(&status)>0);
     soal2b("petshop");
  }

}

//traverse dir scr rekursif
void soal2b(char *basePath)
{
  DIR *dir;
  //menampung variabelnya
  struct dirent *dp;
  char path[1000];
  char *str;
  char nama[100];
  char *temp;

  dir = opendir(basePath);

  if(!dir) return;

  while((dp=readdir(dir))!=NULL){
     int i=0;

     if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
     str = dp->d_name;
     snprintf(nama,sizeof nama, "%s", dp->d_name);
     temp=strtok(str,";_");
     
     while(temp != 0){
        if(i==0||i==3){
	     if(fork()==0){
                 char buf[100];
                 snprintf(buf,sizeof buf, "/home/dewi/modul2/petshop/%s", temp);
                 char *argv[]={"mkdir","-p","/home/dewi/modul2/petshop",buf,NULL};
                 execv("/bin/mkdir",argv);
		//printf("%s\n",buf);
            }
        }
        temp = strtok(NULL,";_");
        i++;
     }
     strcpy(path,basePath);
     strcat(path, "/");
     strcat(path, dp->d_name);
    
     soal2b(path);
  }    	 
 } 
   closedir(dir); 
}
