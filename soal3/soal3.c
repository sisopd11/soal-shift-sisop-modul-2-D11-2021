#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<time.h>
#include<wait.h>
#include<sys/prctl.h>
#include<stdbool.h>

void daemon_program(){
	pid_t pid;
    pid_t sid;
    pid = fork();

    if(pid < 0) {
        exit(EXIT_FAILURE);
    }

    if(pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
   
    if(sid < 0){
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(){
      
    int status;
       
    pid_t child;
    child = fork();
    
    while(wait(&status) > 0);

    program_daemon();

    while(1){
        
        char currenttime[100];
        time_t n = time(NULL);
        struct tm* t = localtime(&n);
        strftime(currenttime, 40, "%Y-%m-%d_%H:%M:%S", t);

        pid_t child;
        child = fork();

        if(child < 0){
            exit(0);
        }

        if(child == 0){
            char *argv[] = {"mkdir", currenttime, NULL};
            execv("/bin/mkdir", argv);
        }

        int status1;
        while(wait(&status1) > 0);

        pid_t child2;
        child2 = fork();
        
        if(child2 < 0){
            exit(0);
        }
        
        if(child2 == 0){
           
            chdir(currenttime);
    	    int a;

            for(a = 0; a < 10; a++){
                char currenttime2[100];
                time_t n2 = time(NULL);
                struct tm* t2 = localtime(&n2);
                strftime(currenttime2, 40, "%Y-%m-%d_%H:%M:%S", t2);

                char link[100];
                sprintf(link, "https://picsum.photos/%ld", (n2 % 1000) + 50);

                pid_t child3;
                child3 = fork();

                if(child3 < 0){
                    exit(0);
                }

                if(child3 == 0){
                    char *argv[] = {"wget", link, "-O", currenttime2, "-o", "/dev/null", NULL}; 
                    execv("/usr/bin/wget", argv);
                }
                sleep(5);
            }

        }
        sleep(40);
    }
}
