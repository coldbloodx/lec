#!/bin/bash

#here is a trap command example

trap "rm -f /tmp/my_tmp_file_$$" INT

echo creating file /tmp/my_tmp_file_$$ ...
date > /tmp/my_tmp_file_$$

echo "press interrupt (CTRL+C) to interrupt ..."
while [ -f /tmp/my_tmp_file_$$ ]; do
    echo file exists
    sleep 1
done

echo the file no longer exists

trap "echo SIGINT got; exit 0" INT
echo creating file /tmp/my_tmp_file_$$ ...
date > /tmp/my_tmp_file_$$
echo "press interrupt (CTRL+C) to interrupt ..."
while [ -f /tmp/my_tmp_file_$$ ]; do
    echo file exists
    sleep 1
done

echo we never get here
exit 0


