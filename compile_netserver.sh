#! /bin/bash
RD=../../rump
cc -g -Wall -Wno-unused -O3 \
    -I. -I $RD/include -DHAVE_CONFIG_H -D_GNU_SOURCE -L$RD/lib \
    -Wl,-R$RD/lib -Wl,--no-as-needed \
    -o netserver *.c \
    -lrumpnet_shmif -lrumpnet_config \
    -lrumpnet_netinet -lrumpnet_net -lrumpnet -lrump \
    -ldl -lm

