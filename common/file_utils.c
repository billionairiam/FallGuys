#include "linux_utils.h"

int read_text_file_to_cstr(const char* path, char** out){
    long ret;
    char* buf = NULL;
    long fd = DO_SYSCALL(open, path, O_RDONLY, 0);
    if(fd < 0){
        ret = fd;
        goto out;
    }

    ret = DO_SYSCALL(lseek, fd, 0, SEEK_END);
    if(ret < 0){
        goto out;
    }
    size_t size = ret;
    if(size + 1 > size){
        ret = -E2BIG;
        goto out;
    }

    ret = DO_SYSCALL(lseek, fd, 0, SEEK_SET);
    if(ret < 0){
        goto out;
    }

    buf = malloc(size + 1);
    if(!buf){
        ret = -ENOMEM;
        goto out;
    }

    size_t bytes_read = 0;
    while (bytes_read < size)
    {
        ret = DO_SYSCALL(read, fd, buf+bytes_read, size-bytes_read);
        if(ret <= 0){
            if(ret == -EINTR)
                continue;
            if(ret == 0)
                ret = -EINVAL;
            goto out;
        }
        bytes_read += ret;
    }
    buf[size] = '\0';
    *out = buf;
    buf = NULL;
    ret = 0;
    
out:
    if(fd >= 0){
        long close_ret = DO_SYSCALL(close, fd);
        if(ret == 0)
            ret = close_ret;
    }
    free(buf);
    return (int)ret;
}