//system headers
#include <error.h>
#include <fcntl.h>
#include <ext2fs/ext2fs.h>
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
        if(ioctl(fd, EXT2_IOC_GETFLAGS, &flags))
        {
            perror("ioctl");
            return 1;
        }
        printf("filename:%s\n", *filename++);
        if(flags & EXT2_APPEND_FL)
        {
            printf("APPEND\n");
        }
        if(flags & EXT2_IMMUTABLE_FL)
        {
            printf("IMMUTABLE\n");
        }
        if(flags & EXT2_SYNC_FL)
        {
            printf("SYNC\n");
        }
        if(flags & EXT2_NODUMP_FL)
        {
            printf("NODUMP\n");
        }
        close(fd);
    }
    return 0;
}
