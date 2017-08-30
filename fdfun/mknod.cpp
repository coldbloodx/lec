#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>

void usage()
{
    perror("usage mknode <path> [ b | c | u | p ] majorid minorid ]");
    exit(1);
}

int main(int argc, char** argv)
{
    int major = 0, minor = 0;
    const char* path = NULL;
    int mode = 0666;
    char* end;
    int args;

    if(argc < 3)
    {
        usage();
    }

    path = argv[1];

    if(!strcmp(argv[2], "b"))
    {
        mode |= S_IFBLK;
        args = 5;
    }
    else if(!strcmp(argv[2], "c") || !strcmp(argv[2], "u"))
    {
        mode |= S_IFCHR;
        args = 5;
    }
    else if(!strcmp(argv[2], "p"))
    {
        mode |= S_IFIFO;
        args = 3;
    }
    else
    {
        perror("unknow node type");
        exit(1);
    }

    if(argc != args)
    {
        usage();
    }

    if(args == 5)
    {
        major = strtol(argv[3], &end, 0);
        if(*end)
        {
            perror("bad major number");
            exit(1);
        }

        minor = strtol(argv[4], &end, 0);
        if(*end)
        {
            perror("bad minor number");
            exit(1);
        }
    }
    if(mknod(path, mode, makedev(major, minor)))
    {
        perror("mknod");
        exit(1);
    }
    return 0;
}
