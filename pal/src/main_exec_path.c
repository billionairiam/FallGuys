#include "api.h"
#include "syscall.h"
#include "linux_utils.h"


#define BUF_SIZE 1023u

char* get_main_exec_path(void){
    char* buf = malloc(BUF_SIZE);
    if(!buf)
        return NULL;
    
    ssize_t len = DO_SYSCALL(readlink, "/proc/self/exe", buf, BUF_SIZE);
    if(len<0){
        free(buf);
        return NULL;
    }
    buf[len]='\0';
    
    return buf;
}