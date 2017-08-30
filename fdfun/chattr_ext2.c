#include <errno.h>
#include <fcntl.h>
#include <linux/ext2_fs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, const char** argv)
{
    const char** filename = argv + 1;
    int fd;
    int flags = 0;

    if(argc < 3)
    {
        perror("cmd [ I | A | S | N ] filename");
        return 1;
    }
    if(strchr(argv[1], 'I')) flags = EXT2_IMMUTABLE_FL;
    if(strchr(argv[1], 'A')) flags = EXT2_APPEND_FL;
    if(strchr(argv[1], 'S')) flags = EXT2_SYNC_FL;
    if(strchr(argv[1], 'N')) flags = EXT2_NODUMP_FL;

    while(*(++filename))
    {
        printf("filename:%s\n", *filename);
        fd = open(*filename, O_RDWR);
        if(fd < 0)
        {
            perror("open");
            return 1;
        }
        printf("flags:%d", flags);
        if(ioctl(fd, EXT2_IOC_SETFLAGS, &flags))
        {
            perror("ioctl");
            return 1;
        }
        close(fd); 
    }
    return 0;
}
