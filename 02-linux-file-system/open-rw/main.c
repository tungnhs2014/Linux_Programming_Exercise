#include <stdio.h>
#include <string.h>
#include <unistd.h> // cung cap cac ham he thong nhu lseek, close
#include <fcntl.h> // cung cap dinh nghia cho cac co va ham nhu open

int main()
{
	int fd; // dung de luu file descriptor cua tep tin duoc mo bang open()
	int number_read, number_write; // bien so de luu file doc va ghi
	char buf[] = "Son Tung!\n";
	off_t pos; // bien luu vi tri con tro
	
	// Mo tep tin "Tung.tx" voi quyen doc/ghi, neu chua co thi tao moi, quyen 0667 
	fd = open("Tung.txt", O_RDWR | O_CREAT, 0667);
	
	// Kiem tra neu viec mo tep tin that bai tra ve -1
	if(-1 == fd){
		printf("open() Tung.txt failed\n");
	}
	
	// Ghi noi dung cua buf1 
	number_write = write(fd, buf, strlen(buf));
	
	// In ra so byte da ghi vao tep tin
	printf("Write %d bytes to Tung.txt\n", number_write);

	// Doi con tro tep tin den vi tri thu 3 (byte thu 2) tu dau tep
	pos = lseek(fd, 0, SEEK_SET); // Di chhuyen con tro den dau tep	
	pos = lseek(fd, 3, SEEK_CUR); // Di chuyen con tro 3 byte tu vi tri hien tai

	// Ghi chuoi vao tep ti
	write(fd, "Nguyen Huu ", strlen("Nguyen Huu ")); 
 	
	// Dong tep tin sau khi hoan tat
	close(fd);
 
	return 0;
}
