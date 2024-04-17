#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_CMNDS 100
#define MAX_CMND_LENGTH 100


void write_files(int pid, int index) {

    char out_file[MAX_CMND_LENGTH], err_file[MAX_CMND_LENGTH];
    sprintf(out_file, "%d.out", pid);
    sprintf(err_file, "%d.err", pid);


    int outfd = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
    int errfd = open(err_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (outfd == -1 || errfd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(outfd, STDOUT_FILENO) == -1 || dup2(errfd, STDERR_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(outfd);
    close(errfd);
}


void execute_cmnd(char *cmnd, int index) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char out_file[MAX_CMND_LENGTH], err_file[MAX_CMND_LENGTH];
        sprintf(out_file, "%d.out", getpid());
        sprintf(err_file, "%d.err", getpid());
        int outfd = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
        int errfd = open(err_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (outfd == -1 || errfd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        if (dup2(outfd, STDOUT_FILENO) == -1 || dup2(errfd, STDERR_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        close(outfd);
        close(errfd);

        char *args[MAX_CMNDS];
        char *token = strtok(cmnd, " ");
        int i = 0;


        while (token != NULL && i < MAX_CMNDS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);

        fprintf(stderr, "Failed to execute command: %s\n", cmnd);
        exit(EXIT_FAILURE);
    }
    else {
        char out_file[MAX_CMND_LENGTH];
        sprintf(out_file, "%d.out", pid);
        FILE *out_fp = fopen(out_file, "a");
        fprintf(out_fp, "Starting command %d: child pid %d of parent PPID %d\n", index, pid, getpid());
        fclose(out_fp);

        int status;
        waitpid(pid, &status, 0);

        out_fp = fopen(out_file, "a");
        fprintf(out_fp, "Finished child PID %d of parent PPID %d\n", pid, getpid());
        fclose(out_fp);

        char err_file[MAX_CMND_LENGTH];
        sprintf(err_file, "%d.err", pid);
        FILE *err_fp = fopen(err_file, "a");
        if (WIFEXITED(status)) {
            fprintf(err_fp, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        } else {
            fprintf(err_fp, "Terminated abnormally\n");
        }
        fclose(err_fp);
    }
}

int main() {
    char cmnds[MAX_CMNDS][MAX_CMND_LENGTH];
    int index = 0;

    while (index < MAX_CMNDS && fgets(cmnds[index], MAX_CMND_LENGTH, stdin) != NULL) {
        cmnds[index][strlen(cmnds[index]) - 1] = '\0';
        index++;
    }

    int i = 0;
    while (i < index) {
        execute_cmnd(cmnds[i], i + 1);
        i++;
    }

    while (wait(NULL) > 0);

    return 0;
}


