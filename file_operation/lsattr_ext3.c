//system headers
#include <error.h>
#include <fcntl.h>
#include <linux/ext3_fs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/fs.h>


int main(int arg, char** argv)
{
    char ** filename = argv + 1;
    int fd;
    int flags;

    while(*filename)
    {
        fd = open(*filename, O_RDONLY);
        if(fd < 0)
        {
            perror("open");
            return 1;
        }
        if(ioctl(fd, EXT3_IOC_GETFLAGS, &flags))
        {
            perror("ioctl");
            return 1;
        }
        printf("filename:%s\n", *filename++);
        if(flags & EXT3_APPEND_FL)
        {
            printf("%d, APPEND, %d\n", flags, EXT3_APPEND_FL);
        }
        if(flags & EXT3_IMMUTABLE_FL)
        {
            printf("%d, IMMUTABLE, %d\n", flags, EXT3_IMMUTABLE_FL);
        }
        if(flags & EXT3_SYNC_FL)
        {
            printf("%d, SYNC, %d\n", flags, EXT3_SYNC_FL);
        }
        if(flags & EXT3_NODUMP_FL)
        {
            printf("%d, NODUMP, %d\n", flags, EXT3_NODUMP_FL);
        }
        close(fd);
    }
    return 0;
}
