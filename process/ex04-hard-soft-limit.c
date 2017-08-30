#include <stdio.h>
#include <sys/resource.h>


void print_limit(char* name, int resource)
{
    struct rlimit limit;
    if(getrlimit(resource, &limit) < 0)
    {
        perror("get resource error");
        exit(1);
    }
    printf("%s:%d, %d\n", name, limit.rlim_cur, limit.rlim_max);
}

int main()
{
    print_limit("RLIMIT_AS", RLIMIT_AS);
    print_limit("RLIMIT_CORE", RLIMIT_CORE);
    print_limit("RLIMIT_CPU", RLIMIT_CPU);
    print_limit("RLIMIT_DATA", RLIMIT_DATA);
    print_limit("RLIMIT_FSIZE", RLIMIT_FSIZE);
    print_limit("RLIMIT_LOCKS", RLIMIT_LOCKS);
    print_limit("RLIMIT_MEMLOCK", RLIMIT_MEMLOCK);
    print_limit("RLIMIT_NOFILE", RLIMIT_NOFILE);
    print_limit("RLIMIT_NPROC", RLIMIT_NPROC);
    print_limit("RLIMIT_RSS", RLIMIT_RSS);
    return 0;
}
