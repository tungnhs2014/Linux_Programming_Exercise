#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd, num_write, num_flock;
    char text[16]= {0}; // Khai bao mang ky tu 'text' kich thuoc 16 byte va khoi tao tat ca gia tri bang 0
    sprintf(text, "hello word\n"); // Dat chuoi "hello word\n" vao mang 'text'
    
    // Mo file "test.txt" voi quyen doc va ghi, neu file chua ton tai thi tao moi voi quyen 0666 (quyen doc ghi cho tat ca)
    fd = open("test.txt", O_RDWR | O_CREAT, 0666);
    if (-1 == fd) // Kiem tra neu khong mo duoc file
    {
       printf("Can not open test.txt file\n"); // In ra thong bao loi neu khong the mo file
       exit(EXIT_FAILURE); // Thoat chuong trinh voi trang thai loi
    }
    else{
        printf("Open test.txt success \n"); // In ra thong bao mo file thanh cong
    }

    // Ghi noi dung trong 'text' vao file 'test.txt'
    num_write = write(fd, text, sizeof(text)-1);
    if (-1 == num_write) // Kiem tra neu khong ghi duoc file
    {
        printf("Can not write test.txt file\n"); // In ra thong bao loi neu khong the ghi file
       exit(EXIT_FAILURE); // Thoat chuong trinh voi trang thai loi
    }
    else{
        printf("Write test.txt success \n"); // In ra thong bao ghi file thanh cong
    }

    // Dat khoa doc quyen (LOCK_EX) len file de ngan tien trinh khac truy cap file nay
    num_flock = flock(fd, LOCK_EX);
    if(-1 == num_flock) // Kiem tra neu khong the dat khoa
    {
        printf("can not set read lock\n"); // In ra thong bao loi neu khong the dat khoa
	} else {
		printf("set read lock\n"); // In ra thong bao dat khoa thanh cong
    }    

    // Vong lap vo han de giu khoa file
    while (1)
    {
        sleep(1); // Dung chuong trinh moi 1 giay, giup giu trang thai khoa file lau hon
    }

    // Dong file
    close(fd);
}
