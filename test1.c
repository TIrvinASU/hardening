// https://www.kernel.org/doc/html/latest/i2c/dev-interface.html

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


int main(int argc, char **argv)
{
    int fd;
    fd =  open("/dev/i2c-0", O_RDWR);
   
    if(fd < 0){
    	perror("open");
    }else{
    	printf("File descriptor for I2C-0 controller device: %d\n", fd);
	printf("I2C-0 test in progress..\n");
    }

    unsigned long funcs;  // bit mask
    // get i2c-0 adapter functionality, store in funcs
        if(ioctl(fd, I2C_FUNCS, &funcs) < 0) {
            perror("ioctl");
            close(fd);
            return 1;
      }

    // see if adapter functionality matches funcs
    // I2C_FUNCS is defined in linux/i2c-dev.h
    // I2C_FUNCS = 0x0705	
    if (funcs & I2C_FUNCS) {
        printf("I2C bus supports standard I2C operations\n");
    } else {
        printf("I2C bus does not support standard I2C operations\n");
    }

    close(fd);  
    printf("I2C-0 test complete.\n");
    return 0;
}
