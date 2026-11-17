#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main(void){
    int fd1, fd2;
    char sentence[500], result[500];

    //Create two pipes 
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    pid_t pid = fork();   //create child process

    if(pid < 0){
        printf("Fork failed");
        exit(1);
    }

    if(pid > 0){
        printf("PROCESS 1\n");
        printf("Enter your sentence : ");
        fgets(sentence, sizeof(sentence), stdin);
        sentence[strcspn(sentence, "\n")] = '\0';

        fd1 = open(FIFO1, O_WRONLY);
        write(fd1, sentence, strlen(sentence)+1);
        close(fd1);

        fd2 = open(FIFO2, O_RDONLY);
        int n = read(fd2, result, sizeof(result));
        if(n < 0){
            perror("read FIFO2");
            exit(1);
        }
        result[n] = '\0';
        close(fd2);

        printf("Result recieved from Process 2 : \n");
        printf("%s\n", result);

        wait(NULL);
        unlink(FIFO1);
        unlink(FIFO2);
        
    }

    else{
        int characters = 0;
        int lines = 1;
        int words = 0;
        int in_word = 0;

        fd1 = open(FIFO1, O_RDONLY);
        int n = read(fd1, sentence, sizeof(sentence)-1);
        if(n < 0){
            perror("read FIFO1");
            exit(1);
        }
        sentence[n] = '\0';
        close(fd1);

        for(int i=0; sentence[i] != '\0'; i++){
            characters++;

            if(sentence[i] == '\n') lines++;
            if(sentence[i] == ' ' || sentence[i] == '\t') in_word = 0;
            else if(in_word == 0){
                words++;
                in_word = 1;
            }

        }

        FILE *fp = fopen("output.txt", "w");
        if(fp == NULL){
            printf("File cannot be created");
            exit(1);
        }

        fprintf(fp, "Number of Characters : %d\n", characters);
        fprintf(fp, "Number of Lines : %d\n", lines);
        fprintf(fp, "Number of Words : %d\n", words);
        fclose(fp);

        sprintf(result, "Characters=%d\nWords=%d\nLines=%d\nOutput is stored in output.txt", characters, words, lines);

        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, result, strlen(result)+1);
        close(fd2);

        exit(0);

    }

    return 0;
}



