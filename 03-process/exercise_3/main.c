#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int fd, status, wpid;
    pid_t pid;
    int num_chidlren = 3; // So luong tien trinh con can tao

    // Vong lap tao 3 tien trinh con
    for (int i = 0; i < 3; i++)
    {
        pid = fork(); // Tao tien trinh con
        if (pid < 0) // Neu fork() that bai
        {
            perror("fork failed\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            if (pid == 0) // Kiem tra neu la tien trinh con
            {
                // In ra PID va PPID cua tien trinh con
                printf("\nIn the child process %d, PID: %d, PPID: %d\n", i + 1, getpid(), getppid());
                exit(EXIT_SUCCESS); // Tien trinh con ket thuc thanh cong
            }
            else
            {
                // Neu la tien trinh cha, in ra PID cua tien trinh cha
                printf("\nIn the parent process, PID: %d\n", getpid());

                // Tien trinh cha cho tien trinh con ket thuc
                wpid = waitpid(pid, &status, 0);
                if (wpid == -1) // Kiem tra loi neu waitpid that bai
                {
                    perror("Error with waitpid\n");
                    exit(EXIT_FAILURE);
                }
                
                // Kiem tra tien trinh con da ket thuc thanh cong hay chua
                if (WIFEXITED(status))
                {
                    printf("Child process terminated with status: %d\n", WEXITSTATUS(status)); // In trang thai ket thuc cua tien trinh con
                }
                else
                {
                    printf("Child process did not terminate normally\n"); // Bao loi neu tien trinh con khong ket thuc binh thuong
                }

                // Kiem tra neu tien trinh con bi ket thuc do mot tin hieu
                if(WIFSIGNALED(status))
                {
                    printf("Child process was killed by signal: %d\n", WTERMSIG(status)); // In ra tin hieu ket thuc tien trinh con
                }
            }
        }
    }
   
    return 0;
}
