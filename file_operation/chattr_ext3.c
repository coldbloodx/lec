#include <errno.h>
#include <fcntl.h>
#include <linux/ext3_fs.h>
#include <linux/fs.h>
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
    if(strchr(argv[1], 'I')) {flags = EXT3_IMMUTABLE_FL;};
    if(strchr(argv[1], 'A')) {flags = EXT3_APPEND_FL;};
    if(strchr(argv[1], 'S')) {flags = EXT3_SYNC_FL;};
    if(strchr(argv[1], 'N')) {flags = EXT3_NODUMP_FL;};

    while(*(++filename))
    {
        printf("filename:%s\n", *filename);
        fd = open(*filename, O_RDONLY);
        if(fd < 0)
        {
            perror("open");
            return 1;
        }
        printf("flags:%d\n", flags);
        if(ioctl(fd, EXT3_IOC_SETFLAGS, &flags))
        {
            perror("ioctl");
            close(fd);
        }
        close(fd); 
    }
    return 0;
}
