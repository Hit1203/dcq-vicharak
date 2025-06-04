#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include<string.h>

#include"driver.h"

int main(int args,char** argv){
    if(args != 2){
        printf("WRONG STATEMENT\n");
        return 1;
    }

    int fd = open(DRIVER_NAME , O_RDWR);
    if(fd < 0){
        printf("CAN'T OPEN FILE");
        return 1;
    }

    data * d = malloc(sizeof(data));
    if(!d){
        printf("Malloc Wrong\n");
        return 1;
    }

    d->length = strlen(argv[1]);
    d->data = malloc(d->length * sizeof(char) );

    if(! d -> data){
        printf("Malloc Wrong\n");
        return 1;
    }

    memcpy(d->data , argv[1], d->length);
    int ret = ioctl (fd,PUSH_DATA ,d);

    switch(ret){
        case OK:
        printf("./push -> PASSED ,PUSHED {.length =%d, .data =%s}\n", d->length, d->data);
        break;

        case INVALID_IP:
        printf("./push -> FAILED{INVALID_IP} , {.length =%d, .data =%s}\n", d->length, d->data);
        break;

        case ERROR:
        printf("./push -> FAILED{ERROR} , {.length =%d, .data =%s}\n", d->length, d->data);
        break;

        case FULL:
        printf("./push -> FAILED{DCQ is FULL} , {.length =%d, .data =%s}\n", d->length, d->data);
        break;

        default:
    }

    close (fd);
    free(d->data);
    free(d);

    return ret;
}