#!/bin/bash

gcc -Wall -Wextra -Wpedantic -fsanitize=address -o main core/*.c -Icore main.c
