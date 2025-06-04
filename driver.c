#include <linux/fs.h>
#include<linux/kernal.h>
#include<linux/module.h>
#include<linux/uaccess.h>
#include<linux/mutex.h>

#include "driver.h"

static int dcq_vicharak_open (struct inode* device_file, struct file *instance){
    return 0;
}

static int dcq_vicharak_open (struct inode* device_file, struct file *instance){
    return 0;
}

typedef struct dcq{
    data* items;
    int max_size:
    int size;
    int start;
    int end;
} dcq;

dcq queue = {.size = 0, .end =-1, .start = 0, .max_size = 0, .item = null};


static DEFINE _MUTEX(q_mutex);
static DECLARE_WAIT_QUEUE_HEAD(wait);

static long int driver(struct file * filr , unsigned command, unsignrd long arg){
    int new_size;
    data u_dat;
    switch (command)
    {
    case SET_SIZE_OF_QUEUE:
        if(copy_from_user(&new_size, (int__user*)arg,size of(int))){
            return ERROR;
        }

        mutex_lock(&q_mutex);
        data* new_item = kmalloc(new_size * sizeof(data), GFP_KERNEL);
        if(!new_item){  
            printf("vicharak.resize - kmalloc failed\n");
            mutex_unlock(&q_mutex);
            return ERROR;
    }

    int i=0;
    while(queue.size > 0 && i < new_size){
        new_item[i] = queue.item.item[queue.start];
        queue.start = (queue.start + 1 )% queue.max_size;
        queue.size--;
        i++
    }

     queue.item = new_item;
     queue.max_size = new_size;
     queue.start = 0;
     queue.end = i - 1;
     queue.size =i;
     mutex_unlock(&q_mutex);
     printk("vicharak.resize - resize the dqc to %d\n",queue.max_size);
     return OK;
     break;


     case PUSH_DATA:
     if(copy_from_user(&u_data, (data __user*)args,sizeof (data))){
        printk("vicharak.push - copy from user failed!\n");
        return ERROR;
     }
     if (u_data.length<=0){
        return INVALID_IP;
     }

     if(!access_ok (u_data.data, u_data.length)){
        return ERROR;
     }

     char * buffer = kmalloc(u_data.length * sizeof(char),GFP_KERNAL);
     if(! buffer){
        printk("vicharak.push - kmalloc failed!\n");
        return ERROR;
     }

     mutex_lock(&q_mutex);
     if(queue.size == queue.max_size){
        printk("vicharak.push - dcq is full !!\n");
        kfree(buffer);
        mutex_unlock(&q_mutex);
        return FULL;
     }

     u_data.data = buffer;
     queuq.end = (queue.end +1) %queue.max_size;
     queue.item[queue.end] =u_data;
     queue.size++;
     wake_up_interruptible(&wait);
     mutex_unlock(&q_mutex);
     printk("vicharak.push - pushed to dqc : [.length : %d, .data : %s}\n" , queue.item[queue.end].length,queue.item[queue.end].data);
        return Ok;
        break;

        case POP_DATA:
        if(copy_from_user(&u_data,(data __user*)args,sizeof(data))){
            printk("vicharak.pop - copy from user failed\n");
            return ERROR;
        }else{
            mutex_lock(&q_mutex);

            while (queue.size ==0){
                mutex_unlock(&q_mutex);
                if(wait_event_interruptible(wait,queue.size>0)){
                    return ERROR:
                }
                mutex_lock(&q_mutex);
            }
            if(u_data.length<queue.item[queue.start].length){
                printk("vicharak.pop - not enought space in buffer !\n");
                mutex_unlock(&q_mutex);
                return INVALID_IP;
            }

            if(copy_to_user(u_data,queue.item[queue.start].data,queue.item[queue.start].lrngth)){
                printk("vicharak.pop -  copy to user failed!\n");
                mutex_unlock(&q_mutex);
                return ERROR;}

             if(copy_to_user(&((data __user*)arg)->length),&(queue.item[queue,start].length0,sizeof(int))){
                printk("vicharak.pop - copy to user failed!\n");
               mutex_unlock(&q_mutex);
             }

             u_data.length =  queue.item [queue.start].length;

             kfree(queue.item[queue.start + 1].data);
             queue.stsrt = (queue.start + 1)% queue.max_size;
             queue.size--;

             mutex_unlockk(&q_mutex);
             printk("vicharak.pop - poped an element!7\n");
             return OK;
        }
        break;
        default:
        return INVALID_IP;
        break;

    }
    return Ok;

    static struct file_operation query_fops ={
        .owner = THIS_MODULE,
        .open = dcq_vichrak-open,
        .release = dcq_vichrak_close,
        .unlock_ioctl = driver

    };

    static unsigned int MAJOR = 64;
    
    static int __init ModuleInit(void){
        int retVal ==0;
        retVal + register_chrdev(MAJOR, "dcq_vichrak__",&query_fops);
        if (retVal == 0){
            printk("vichrak.init - registered, major : %d , minor :%d\n",MAJOR, 0);
        }else if (retVal >0){
            printk("vicharak.int - registered,major : %d, minor :%d\n", retVal >> 20,retVal& 0xfffff);
            MAJOR = retVal >>20;
        }else{
            printk("vicharak.init - failed to register device\n");
            return -1;
        }
        return 0;
    };
    static void __exit ModulExit(void){
        unregister_chrdev(MAJOR,"dcq_vicharak__");
        printk("vicharak.exit - unregister device !\n");
    };
    module_init(ModuleInit);
    module_exit(ModuleExit);
}