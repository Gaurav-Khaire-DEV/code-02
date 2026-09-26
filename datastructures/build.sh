#!/bin/bash

gcc -Wall -Wextra -Wpedantic -fsanitize=address -o main main.c
