// References:
// https://www.geeksforgeeks.org/socket-programming-cc/
// https://www.kernel.org/doc/html/latest/networking/can.html
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/can/raw.h>

int main(int argc, char **argv)
{
    int sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW );    
    
    if(sockfd < 0){
      perror("socket");
      return 1;
    }
    
    printf("sockfd value is: %d\n", sockfd);

    struct ifreq ifr;
    strcpy(ifr.ifr_name, "can0");
    
    if(ioctl(sockfd, SIOCGIFINDEX, &ifr) < 0){
      printf("Value of ifr_ifindex: %d\n", ifr.ifr_ifindex);
      perror("ioctl");
      close(sockfd);
      return 1;
    }

    // Check if the socket is bound to the CAN interface
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      perror("bind");
      close(sockfd);
      return 1;
    }
    printf("Socket bound to interface can0\n");

    printf("CAN0 was located\n");
    return 0;
}
