#!/bin/bash
#

set -ex

gcc -Wall -Wextra -Wpedantic -fsanitize=address -o main main.c && ./main
