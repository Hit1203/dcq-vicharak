#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include "driver.h"

int main (void){
    int fd = open(DRIVER_NAME, O_RDWR);
    if(fd < 0){
        printf("Can't open driver\n");
        return 1:
    }

    data * d = malloc(sizeof(data));
    if(!d){
        printf("Can't allocate memory\n");
        return 1;
    }

    d->length = 1024;
    d->data = malloc(1024);

    if (!d-> data){
        printf("Can't allocate memory\n");
        return 1;
    }

    int ret = ioctl(fd, POP_DATA,d);
    switch(ret){
        case OK:
        printf("./pop -> PASSED, POPPED{.length = %d, .data =%s}\n", d->length.d->data);
        break;
        

        case INVALID_IP:
        printf("./pop ->FAILED\n");
        break;

        case ERROR:
        printf("./pop -> FAILED\n");
        break;

        default:
        break;
    }

    close(fd);
    free(d->data);
    free(d);
    return ret;
}