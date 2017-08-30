#include <errno.h>
#include <glob.h>
#include <cstdio>
#include <string.h>
#include <unistd.h>


int errfn(const char* pathname, int theerr)
{
    fprintf(stderr, "error accessing %s: %s\n", pathname, strerror(theerr));
    return 0;
}

int main(int argc, char** argv)
{
    glob_t result;
    int i, rc, flags;

    if(argc < 2)
    {
        printf("at least one argument must be given\n");
        return 1;
    }
    
    flags = 0;

    for(i = 1; i < argc; ++i)
    {
        rc = glob(argv[i], flags, errfn, &result);
        if(rc == GLOB_NOSPACE)
        {
            fprintf(stderr, "out of memory during glob operation!\n");
            return 1;
        }
        flags |= GLOB_APPEND;
    }
    if(!result.gl_pathc)
    {
        fprintf(stderr, "no matches\n");
        rc = 1;
    }
    else
    {
        for( i = 0; i < result.gl_pathc; ++i)
        {
            puts(result.gl_pathv[i]);
        }
        rc = 0;
    }
    globfree(&result);
    return rc;
}
