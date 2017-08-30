# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl Libop.t'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use strict;
use Libop;
use warnings;
use 5.010;
use strict;

use Test::More tests => 5;
BEGIN { 
use_ok('Libop') ;
ok(Libop::xadd(1, 2) eq 3);
ok(Libop::xsub(1, 2) eq -1);
ok(Libop::xdiv(1, 2) eq 0.5);
ok(Libop::xmul(1, 2) eq 2);
};
