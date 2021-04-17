#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>


void downloadF()
{
  char *LINK[3] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
                    "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
                    "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
  char *file[3] = {"/home/avind/Desktop/shift2/soal3/Foto_for_Stevany.zip", 
                  "/home/avind/Desktop/shift2/soal3/Musik_for_Stevany.zip", 
                  "/home/avind/Desktop/shift2/soal3/Film_for_Stevany.zip"};

  for(int i=0;i<3;i++)
  {
      if(fork() == 0)
      {
          char *argv[] = {"wget", "--no-check-certificate", LINK[i], "-O", file[i], NULL};
          execvp("/usr/bin/wget", argv);
          exit(0);
      }
  }
  for(int i=0;i<3;i++)
  wait(NULL);
}

void unzipF()
{
  char *file[3] = {"/home/avind/Desktop/shift2/soal3/Foto_for_Stevany.zip", 
                    "/home/avind/Desktop/shift2/soal3/Musik_for_Stevany.zip", 
                    "/home/avind/Desktop/shift2/soal3/Film_for_Stevany.zip"};

  for(int i=0;i<3;i++)
  {
      if(fork() == 0)
      {
          char *argv[] = {"unzip", file[i], "-d", "/home/avind/Desktop/shift2/soal3/", NULL};
          execvp("/usr/bin/unzip", argv);
          exit(0);
      }
  }
  for(int i=0;i<3;i++)
  wait(NULL);

}

void removeF()
{
  char *file[3] = {"/home/avind/Desktop/shift2/soal3/Foto_for_Stevany.zip", 
                    "/home/avind/Desktop/shift2/soal3/Musik_for_Stevany.zip", 
                    "/home/avind/Desktop/shift2/soal3/Film_for_Stevany.zip"};


  for(int i=0;i<3;i++)
  {
      if(fork() == 0)
      {
          char *argv[] = {"rm", file[i], NULL};
          execvp("/bin/rm", argv);
          exit(0);
      }
  }
  for(int i=0;i<3;i++)
  wait(NULL);
}




void renameF()
{
  char *filehasil[3] = {"/home/avind/Desktop/shift2/soal3/FOTO", 
                        "/home/avind/Desktop/shift2/soal3/MUSIK", 
                        "/home/avind/Desktop/shift2/soal3/FILM"};
    
  char *filebaru[3] = {"/home/avind/Desktop/shift2/soal3/Pyoto", 
                      "/home/avind/Desktop/shift2/soal3/Musyik", 
                      "/home/avind/Desktop/shift2/soal3/Fylm"};
  
  for(int i=0;i<3;i++)
  
  {
      if(fork() == 0)
      {
         char *argv[] = {"mv", filehasil[i], filebaru[i], NULL};
          execvp("mv", argv);
          exit(0);
      }
  }
  for(int i=0;i<3;i++)
  wait(NULL);
}

void zipF()
{
  chdir("/home/avind/Desktop/shift2/soal3/");
  char *file[3] = {"Pyoto", 
                  "Musyik", 
                  "Fylm"};
    
    if(fork() == 0)
    {
       char *argv[] = {"zip", "-r", "-m", 
                      "/home/avind/Desktop/shift2/soal3/Lopyu_Stevany.zip", 
                      file[0], file[1], file[2], NULL};
        execvp("zip", argv);
        exit(0);
    }

    wait(NULL);
    chdir("/");
}


int main() {
  pid_t pid, sid; 
  pid = fork();   
  
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

	if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
	


  struct tm dt = {0};
  dt.tm_year = 2021 - 1900;
  dt.tm_mon  = 4 - 1;
  dt.tm_mday = 9;
  dt.tm_hour = 22;
  dt.tm_min = 22;
  dt.tm_sec = 0;

  time_t dt1 = mktime(&dt);

  time_t cur_time;
  int flag = 0;
	
  while (1) {
  	
    cur_time = time(NULL);
    
    struct tm ct = *localtime(&cur_time);
    if ( dt.tm_year == ct.tm_year && dt.tm_mon == ct.tm_mon && dt.tm_mday == ct.tm_mday)
    {
      double seconds = difftime(dt1, cur_time);
      if(flag == 1)
      {
        sleep(seconds);
        zipF();
      }
      else if(seconds <= 21600 && flag == 0)
      {
        downloadF();
        unzipF();
        removeF();
        renameF();
        flag++;
      }
    } 
    
    sleep(60);
  }
  
  
}
