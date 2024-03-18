#include <stdio.h>
//#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/watchdog.h> // Include header file for watchdog IOCTL commands

int main(int argc, char **argv)
{
    int fd;
    fd =  open("/dev/watchdog", O_RDWR);
   
    if(fd < 0){
    	perror("open");
    }else{
    	printf("File descriptor for watchdog controller device: %d\n", fd);
	printf("Watchdog test in progress..\n");
    }

   
    if(ioctl(fd, WDIOC_KEEPALIVE, 0) != 0) {
        perror("ioctl");
        close(fd);
        return 1; // Return error code
    }
    
    close(fd);  
    printf("Watchdog test complete.\n");
    return 0;
}
