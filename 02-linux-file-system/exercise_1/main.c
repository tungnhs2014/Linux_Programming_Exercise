#include <stdio.h>      // Cho ham printf
#include <stdlib.h>     // Cho ham exit
#include <string.h>     // Cho ham strlen
#include <stdint.h>     // Cung cap cac dinh nghia cho uintmax_t va intmax_t
#include <time.h>       // Cho ham ctime de chuyen doi thoi gian
#include <unistd.h>     // Cho cac system call nhu lseek, close
#include <fcntl.h>      // Cho cac flag nhu O_RDWR, O_CREAT, va ham open
#include <sys/stat.h>   // Cho ham stat va struct stat


int main()
{
    int fd;
    int number_write_1, number_write_2;
    off_t pos;
    struct stat sb; 
    char buf_1[] = "Son Tung ";       // Du lieu se duoc ghi vao file
    char buf_2[] = "co gang len!!";  // Du lieu tiep theo se ghi vao file

    // Mo hoac tao tep "test.txt" voi quyen doc-ghi, va cap quyen 0666 (rwxrwxrwx)
    fd = open("test.txt", O_RDWR | O_CREAT, 0666);
    if (-1 == fd)
    {
        // Kiem tra loi khi khong the mo file
        printf("Can not open test.txt file\n");
        exit(EXIT_FAILURE);
    }

    // Di chuyen con tro doc-ghi den vi tri dau tien cua file
    pos = lseek(fd, 0, SEEK_SET);
    number_write_1 = write(fd, buf_1, strlen(buf_1)); // Ghi chuoi buf_1 vao file

    // Kiem tra loi khi khong ghi duoc du lieu buf_1 vao file
    if (-1 == number_write_1)
    {
        printf("Can not write buf_1\n");
        close(fd);  // Dam bao dong tep neu co loi
        exit(EXIT_FAILURE);
    }

    // Di chuyen con tro doc-ghi den vi tri thu 10 cua file de ghi du lieu tiep theo
    pos = lseek(fd, 10, SEEK_SET);
    number_write_2 = write(fd, buf_2, strlen(buf_2)); // Ghi chuoi buf_2 vao file

    // Kiem tra loi khi khong ghi duoc du lieu buf_2 vao file
    if (-1 == number_write_2)
    {
        printf("Can not write buf_2\n");
        close(fd);  // Dam bao dong tep neu co loi
        exit(EXIT_FAILURE);
    }

    // Dong tep sau khi da ghi du lieu
    close(fd);

    // Su dung ham stat de lay thong tin chi tiet ve tep
    int check = stat("test.txt", &sb);
    if (0 == check)
    {
        // In ra loai tep dua tren mode cua tep
        printf("File type: ");
        switch (sb.st_mode & S_IFMT)
        {
            case S_IFBLK:   printf("block device\n");       break;
            case S_IFCHR:   printf("character device\n");   break;
            case S_IFDIR:   printf("directory\n");          break;
            case S_IFIFO:   printf("FIFO/pipe\n");          break;
            case S_IFLNK:   printf("symlink\n");            break;
            case S_IFREG:   printf("regular file\n");       break;
            case S_IFSOCK:  printf("socket\n");             break;
            default:        printf("unknown?\n");           break;
        }

        // In ra so inode va kich thuoc cua tep
        printf("\nI-node number: %ju\n", (uintmax_t)sb.st_ino);
        printf("File size: %jd bytes\n\n", (intmax_t)sb.st_size);

        // In ra cac thoi gian lien quan den tep (thoi gian thay doi trang thai, truy cap, va chinh sua)
        printf("Last status change:     %s", ctime(&sb.st_ctime)); // Thoi gian thay doi trang thai tep
        printf("Last file access:       %s", ctime(&sb.st_atime)); // Thoi gian truy cap tep
        printf("Last file modification: %s", ctime(&sb.st_mtime)); // Thoi gian chinh sua tep
    }
    else
    {
        // Neu ham stat that bai, in thong bao loi
        printf("Can not retrieve file information\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
