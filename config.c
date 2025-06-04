#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include<stdlib.h>
#include "driver.h"

int main (int args, char** argv){
    if(args !=2){
        printf("Invalid Arguments !! \nUSAGE : ./config <size>");
        return 1;   
    }

    int fd = open (DRIVER_NAME, O_RDWR);
    if(fd < 0){
        printf("Cannot open driver\n");
        return 1;
    }

    int size = atoi (argv[1]);
    int ret = ioctl(fd , SET_SIZE_OF_QUEUE, & size);
    switch (ret){
        case OK:
        printf("./config -> PASSED\n");
        break;

        case INVALID_IP:
        printf("./config -> UNSUCCEFUL\n");
        break;

        case error:
        printf("./config -> failed \n");
        break;
    }

    close (fd);
    return ret;
    
}