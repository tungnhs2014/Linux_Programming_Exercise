#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    char *file_path = "./log/hello.txt";  // Duong dan den file
    char message[] = {"Hello Son Tung\n"}; // Thong diep can ghi vao file
    char buffer[256]; // Bo dem dung de doc noi dung tu file
    int fd, byte_read, byte_written; // Cac bien dung de luu tru file descriptor, so byte doc, va so byte ghi
    pid_t pid; // Bien luu tru process ID

    // Tao thu muc ./log neu chua ton tai
    if(mkdir("./log", 0777) && errno != EEXIST)
    {
        perror("Error creating directory\n"); // In ra thong bao loi neu khong tao duoc thu muc
        exit(EXIT_FAILURE); // Thoat chuong trinh neu loi
    }

    // Tao tien trinh con su dung fork()
    pid = fork();
    if(pid < 0)
    {
        perror("Fork failed\n"); // Bao loi neu khong the tao tien trinh con
        exit(EXIT_FAILURE);
    }

    // Kiem tra neu la tien trinh con
    if(pid == 0)
    {   
        sleep(1); // Doi 1 giay de tien trinh cha ghi xong file
        printf("Processing B: Reading file...\n");

        // Mo file de doc
        fd = open(file_path, O_RDONLY);
        if(fd < 0)
        {
            perror("Error opening file in Process B\n"); // Bao loi neu mo file that bai
            exit(EXIT_FAILURE);
        }
        
        // Doc du lieu tu file vao buffer
        byte_read = read(fd, buffer, sizeof(buffer) - 1);
        if(byte_read < 0){
            perror("Error reading file in Process B"); // Bao loi neu doc file that bai
            close(fd);
            exit(EXIT_FAILURE);           
        }
        buffer[byte_read] = '\0'; // Them ky tu ket thuc chuoi vao buffer
        printf("Content of the file: %s\n", buffer); // In noi dung cua file
        close(fd); // Dong file
    }
    else // Neu la tien trinh cha
    {
        printf("Process A: Creating and writing to file..\n");

        // Mo file de ghi, neu file ton tai thi xoa no di va ghi de
        fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd < 0)
        {
            perror("Error opening file in Process A\n"); // Bao loi neu mo file that bai
            exit(EXIT_FAILURE);
        }
        
        // Ghi thong diep vao file
        byte_written = write(fd, message, strlen(message));
        if(byte_written < 0)
        {
            perror("Error writing file in Process A"); // Bao loi neu ghi file that bai
            close(fd);
            exit(EXIT_FAILURE);     
        } 
        else if (byte_written != strlen(message)) 
        {
            fprintf(stderr, "Error: Not all bytes were written to the file\n"); // Bao loi neu khong ghi duoc het thong diep
            close(fd);
            exit(EXIT_FAILURE);
        }

        close(fd); // Dong file sau khi ghi

        sleep(10); // Tien trinh cha doi 10 giay
        printf("Process A is still running...\n");

        wait(NULL); // Tien trinh cha doi tien trinh con hoan thanh
        printf("Process A collected the child process.\n");       

    }
    return 0;
}
