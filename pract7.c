#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int pipe1[2], pipe2[2];
    char pathname[200], buffer[500];

    pipe(pipe1);    //Parent to child  ( Parent writes (1) & Child reads (0) )
    pipe(pipe2);    //Child to parent  ( Child writes (1) & Parent reads (0) )

    pid_t pid = fork();

    if(pid < 0){
        printf("Fork failed");
        return 1;
    }

    if(pid > 0){
        close(pipe1[0]);
        close(pipe2[1]);

        printf("Enter pathname : ");
        fgets(pathname, sizeof(pathname), stdin);
        pathname[strcspn(pathname , "\n")] = '\0';

        write(pipe1[1], pathname, strlen(pathname) + 1);
        close(pipe1[1]);

        printf("\nContents of file : \n");

        int n;
        while((n = read(pipe2[0], buffer, sizeof(buffer))) > 0){
            write(STDOUT_FILENO, buffer, n);
        }

        close(pipe2[0]);
        wait(NULL);
    }
    else{
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], pathname, sizeof(pathname));
        close(pipe1[0]);

        FILE *fp = fopen(pathname, "r");

        if(fp == NULL){
            char *msg = "Unable to open file \n";
            write(pipe2[1], msg, strlen(msg));
            close(pipe2[1]);
            return 1;
        }

        int n;
        while((n = fread(buffer, 1 , sizeof(buffer), fp )) > 0){
            write(pipe2[1], buffer, n);
        }

        fclose(fp);
        close(pipe2[1]);
    }

    return 0;
    


}