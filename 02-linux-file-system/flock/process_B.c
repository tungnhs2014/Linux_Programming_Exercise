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
    char buf[16]= {0}; // Khai bao mot buffer kich thuoc 16 byte va khoi tao gia tri ban dau bang 0

    // Mo file test.txt voi quyen doc va ghi (O_RDWR), neu khong mo duoc tra ve loi
    fd = open("test.txt", O_RDWR, 0666); 
    if (-1 == fd) // Kiem tra neu khong mo duoc file
    {
       printf("Can not open test.txt file\n"); // In thong bao loi neu khong mo duoc file
       exit(EXIT_FAILURE); // Thoat chuong trinh voi trang thai loi
    }
    else{
        printf("Open test.txt success \n"); // In thong bao thanh cong neu mo file duoc
    }

    // Dat khoa doc ghi doc quyen (LOCK_EX) voi co khong chan (LOCK_NB)
    num_flock = flock(fd, LOCK_EX | LOCK_NB);
    if(-1 == num_flock) // Neu khong dat duoc khoa
    {
        printf("can not get read lock file\n"); // In ra thong bao khong the lay khoa doc ghi doc quyen
	} else {
		printf("get read lock file\n"); // In thong bao lay khoa thanh cong
    }    
    
    // Co gang lay khoa doc chia se (LOCK_SH) voi co khong chan (LOCK_NB)
    num_flock = flock(fd, LOCK_SH | LOCK_NB);
    if(-1 == num_flock) // Neu khong lay duoc khoa doc chia se
    {
        printf("can not get read lock file\n"); // In ra thong bao khong the lay khoa doc chia se
    }
    else{
        printf("get read lock file\n"); // In ra thong bao lay khoa doc chia se thanh cong
        
        // Doc noi dung tu file vao buffer, neu doc loi thi in thong bao
        if(read(fd, buf, sizeof(buf) -1) == -1) 
        {
            printf("can not read file\n"); // In ra thong bao khong the doc file
            exit(EXIT_FAILURE); // Thoat chuong trinh voi trang thai loi
        }
        else
        {
            printf("%s\n", buf); // Neu doc thanh cong, in ra noi dung doc duoc tu file
        }
    }

    // Dong file
    close(fd);
}
