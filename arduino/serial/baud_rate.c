#include <stdio.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char *argv[]) {
    struct termios attribs;
    speed_t ispeed, ospeed;
    int fd;

    if(argc == 1) {
        fprintf(stdout, "Usage: ./a.out <serial_device>");
	return -1;
    }

    fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        fprintf(stdout, "error in openening %s\n", argv[1]);
	return -1;
    }

    if(tcgetattr(fd, &attribs) < 0) {
        perror("stdin");
        return -1;
    }
    
    // speed returned are octal value, please lookup in termios.h for reference
    ispeed = cfgetispeed(&attribs);
    ospeed = cfgetospeed(&attribs);
    printf("Baud: input speed: 0%o, output speed: 0%o\n", ispeed, ospeed);

    return 0;
}
