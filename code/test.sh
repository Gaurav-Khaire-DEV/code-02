#!/bin/bash
#

set -ex

gcc -Wall -Wextra -Wpedantic -fsanitize=address -o test-darray core/*.c -Icore test-darray.c && ./test-darray
