#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include "libop.h"

#include "const-c.inc"

MODULE = Libop		PACKAGE = Libop		

INCLUDE: const-xs.inc

void
hello_world(char *classname)
CODE:
    printf("Hello World from perl xs language!\n");

double
xadd(a , b)
    double a
    double b
    
double
xsub(a , b)
    double a
    double b

double
xmul(a , b)
    double a
    double b
    
double
xdiv(a , b)
    double a
    double b
