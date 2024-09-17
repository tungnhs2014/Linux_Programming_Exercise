#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd;
    struct flock fl;
    
    char buf[25]= {0};

    sprintf(buf, "TungNHS");

    fd = open("test.txt", O_RDWR); 
    if (-1 == fd)
    {
       printf("Can not open test.txt file\n");
       exit(EXIT_FAILURE); 
    }
    else{
        printf("Open test.txt success \n");
    }

    fl.l_start = 1;         /* Offset where the lock begins */
    fl.l_len = 8;           /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;    /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET; /* How to interpret 'l_start': SEEK_SET, SEEK_CUR, SEEK_END */

    if(fcntl(fd, F_SETLK, &fl) == -1) { 
        printf("can not set write lock byte 0-5\n"); 
    } 

    fl.l_start = 9; 
    fl.l_len = 8; 
    fl.l_type = F_WRLCK; 
    fl.l_whence = SEEK_SET; 

    if(fcntl(fd, F_SETLK, &fl) == -1) { 
        printf("can not set write lock byte 6-11\n"); 
    } else { 
        printf("set write lock byte 6-11\n"); 
        lseek(fd, 9, SEEK_SET);

        if(write(fd, buf, sizeof(buf) - 1) == -1) { 
            printf("can not write file \n"); 
            return 0; 
        } else {
            printf("write file \n");
        } 
    }


    close(fd);
}
