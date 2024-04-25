// https://man7.org/linux/man-pages/man7/packet.7.html
// https://man7.org/linux/man-pages/man2/socket.2.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>


int main(int argc, char **argv)
{
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if(sockfd < 0){
    	perror("sockfd");
    }
	
    struct ifreq ifr;
    strcpy(ifr.ifr_name,"eth1");

    if(ioctl(sockfd, SIOCGIFHWADDR, &ifr) < 0){
    	perror("ioctl");
	close(sockfd);
	return 1;
    }
    printf("Test passed.\n");

    return 0;
}
