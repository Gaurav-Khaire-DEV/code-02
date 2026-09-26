#!/bin/bash

gcc -g -Wall -Wextra -Wpedantic -fsanitize=address -o main main.c
