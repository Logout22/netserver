#! /bin/bash
cc -g -Wall -Wno-unused -O3 \
    -I. -DHAVE_CONFIG_H -D_GNU_SOURCE \
    -o netserver *.c -ldl -lm
