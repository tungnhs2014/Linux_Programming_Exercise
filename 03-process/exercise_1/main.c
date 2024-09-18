#include <stdio.h>   
#include <unistd.h>   // Thu vien cho ham nhu fork(), getpid(), getppid()
#include <stdlib.h>  

int main(int argc, char *argv[])
{
    pid_t child_pid;     // Khai bao bien child_pid kieu pid_t de luu tru PID cua tien trinh con
    child_pid = fork();  // Tao ra mot tien trinh con. fork() tra ve PID cua tien trinh con cho tien trinh cha, va tra ve 0 cho tien trinh con
    
    if (child_pid >= 0)  // Kiem tra xem viec goi fork() co thanh cong khong. Neu fork thanh cong, gia tri tra ve se >= 0
    {
        if (child_pid == 0)  // Neu child_pid == 0, dieu nay co nghia day la tien trinh con
        {
            printf("\nIn the child process, PID: %d\n", getpid());   // In ra PID cua tien trinh con bang cach goi ham getpid()
            printf("PID in the parent process: %d\n", getppid());    // In ra PID cua tien trinh cha bang cach goi ham getppid()
        }
        else  // Neu child_pid > 0, dieu nay co nghia la day la tien trinh cha
        {
            printf("\nIn the parent process, PID: %d\n", getpid());  // In ra PID cua tien trinh cha bang cach goi ham getpid()
            while(1);  // Vong lap vo han de giu cho tien trinh cha ton tai
        }
    }
    else  // Neu child_pid < 0, dieu nay co nghia la goi fork() that bai
    {
        printf("fork failed\n");
	}
    return 0;  
}
