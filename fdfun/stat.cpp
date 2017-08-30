//system headers
#include <errno.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <unistd.h>

//c++ headers
#include <iostream>
#include <cstdio>
#include <time.h>
#include <errno.h>
using namespace std;

const int TIME_STRING_BUF = 50;

char* time_string(time_t t, char* buf)
{
    struct tm* local;
    local = localtime(&t);
    strftime(buf, TIME_STRING_BUF, "%c", local);
    return buf;
}

int stat_file(const char* file)
{
    struct stat statbuf;
    char time_buf[TIME_STRING_BUF];

    if(lstat(file, &statbuf))
    {
        perror("lstat");
        return 1;
    }

    cout<<"file name"<<file<<endl;
    cout<<"On device: major:"<<major(statbuf.st_dev)<<endl
        <<"minor:"<<minor(statbuf.st_dev)<<endl
        <<"Inode number:"<<statbuf.st_ino<<endl;
    cout<<"Size:"<<statbuf.st_size<<endl;
    cout<<"Type:"<<(statbuf.st_mode & S_IFMT)<<endl
        <<"Permissions:"<<(statbuf.st_mode &~ S_IFMT)<<endl;
    cout<<"Owner:"<<statbuf.st_uid<<endl
        <<"Group:"<<statbuf.st_gid<<endl
        <<"Number of links"<<statbuf.st_nlink<<endl;
    cout<<"Create time:"<<time_string(statbuf.st_ctime, time_buf)<<endl;
    cout<<"Modified time:"<<time_string(statbuf.st_mtime, time_buf)<<endl;
    cout<<"Access time:"<<time_string(statbuf.st_atime, time_buf)<<endl;
    return 0;
}

int main(int argc, const char** argv)
{
    int i;
    int rc = 0;

    for(int i = 0; i < argc; ++i)
    {
        rc |= stat_file(argv[i]);
        if((argc - i) > 1)
        {
            cout<<endl;
        }
    }
    return rc;
}
