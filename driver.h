#ifndef VICHARAK_IOCTL_DCQ_DRIVER_H
#define VICHARAK_IOCTL_DCQ_DRIVER_H

typedef struct data {
    int length;
    char * data;
} data;

typedef enum ACTIONS {
    OK =0,
    INVALID_IP = 1,
    ERROR = 2,
    Full = 3,
}ACTION;