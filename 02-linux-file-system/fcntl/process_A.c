#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd, num_write;
    char text[16]= {0};

    struct flock fl;

    sprintf(text, "Son_Tung\n");
     
    fd = open("test.txt", O_RDWR | O_CREAT, 0666);
    if (-1 == fd) 
    {
       printf("Can not open test.txt file\n"); 
       exit(EXIT_FAILURE); 
    }
    else{
        printf("Open test.txt success \n"); 
    }

    num_write = write(fd, text, sizeof(text)-1);
    if (-1 == num_write) 
    {
        printf("Can not write test.txt file\n"); 
        exit(EXIT_FAILURE); 
    }
    else{
        printf("Write test.txt success \n"); 
    }

    fl.l_start = 1;         /* Offset where the lock begins */
    fl.l_len = 8;           /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;    /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET; /* How to interpret 'l_start': SEEK_SET, SEEK_CUR, SEEK_END */
   
    if(fcntl(fd, F_SETLK, &fl) == -1) { 
        printf("can not set write lock byte 1-5\n"); 
    } else { 
        printf("set write lock byte 1-5 \n"); 
    } 

    while (1)
    {
        sleep(1); 
    }
    
    close(fd);
}
