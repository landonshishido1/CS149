#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_COMMANDS 100

// Parse a single command and its arguments from a string
int parse_command(char* line, char* argv[]) {
    int argc = 0;
    argv[argc] = strtok(line, " \n");
    while (argv[argc] != NULL) {
        argc++;
        argv[argc] = strtok(NULL, " \n");
    }
    return argc; // Number of arguments
}

void execute_command(int index, char* argv[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char out_filename[20], err_filename[20];
        sprintf(out_filename, "%d.out", getpid());
        sprintf(err_filename, "%d.err", getpid());

        int out_fd = open(out_filename, O_RDWR | O_CREAT | O_APPEND, 0777);
        int err_fd = open(err_filename, O_RDWR | O_CREAT | O_APPEND, 0777);

        if (out_fd == -1 || err_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        dup2(out_fd, STDOUT_FILENO);
        dup2(err_fd, STDERR_FILENO);
        close(out_fd);
        close(err_fd);

        // Log the start message to the .out file
        dprintf(STDOUT_FILENO, "Starting command %d: child %d pid of parent %d\n", index, getpid(), getppid());

        // Execute the command using execvp
        execvp(argv[0], argv);

        // If execvp returns, there was an error
        perror(argv[0]); // Writes directly to the stderr which is now err_fd
        exit(2);
    } else {
        // Parent process
        waitpid(pid, &status, 0);

        char out_filename[20], err_filename[20];
        sprintf(out_filename, "%d.out", pid);
        sprintf(err_filename, "%d.err", pid);

        int out_fd = open(out_filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        int err_fd = open(err_filename, O_WRONLY | O_CREAT | O_APPEND, 0777);

        if (out_fd == -1 || err_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            // Child exited normally, write to err file
            int exit_status = WEXITSTATUS(status);
            dprintf(err_fd, "Exited with exitcode = %d\n", exit_status);

            // Log the finish message to the .out file
            dprintf(out_fd, "Finished child %d pid of parent %d\n", pid, getppid());
        } else if (WIFSIGNALED(status)) {
            // Child was killed by a signal, write to err file
            dprintf(err_fd, "Child %d killed by signal %d\n", pid, WTERMSIG(status));
        }

        close(out_fd);
        close(err_fd);
    }
}



int main() {
    char* argv[MAX_NUMBER_OF_COMMANDS];
    char line[MAX_COMMAND_LENGTH];
    int command_count = 0;

    // Read commands from stdin until EOF
    while (1) {
        if (!fgets(line, sizeof(line), stdin)) {
            if (feof(stdin)) {
                // End of file (EOF) reached, break out of the loop
                break;
            } else {
                // Error occurred in fgets
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }
        // Remove newline at the end of line
        line[strcspn(line, "\n")] = 0;
        if (line[0] == 0) {
            // Empty line, skip
            continue;
        }
        if (parse_command(line, argv) > 0) {
            execute_command(++command_count, argv);
        }
    }

    // All commands are processed, wait for all children to complete
    while (wait(NULL) > 0); // Wait for all child processes to finish

    return EXIT_SUCCESS;
}