#include <errno.h>
#include <dirent.h>
#include <cstdio>

int main()
{
    DIR* dir;
    struct dirent* ent;

    if(!(dir = opendir(".")))
    {
        perror("opendir");
        return 1;
    }
    errno = 0;
    while((ent = readdir(dir)))
    {
        puts(ent->d_name);
        errno = 0;
    }

    if(errno)
    {
        perror("readdir");
        return 1;
    }
    closedir(dir);
    return 0;
}

