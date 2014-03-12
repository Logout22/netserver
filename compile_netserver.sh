#! /bin/sh
RD=../../rump
cc -g -Wall -Wno-unused -O3 \
    -I. -I $RD/include -DHAVE_CONFIG_H -D_GNU_SOURCE -L$RD/lib \
    -o netserver *.c \
    -Wl,-R$RD/lib -Wl,--whole-archive					\
	    -lrumpnet_virtif -lrumpnet_config -lrumpdev_bpf		\
	    -lrumpnet_netinet6 -lrumpnet_netinet -lrumpnet_net -lrumpnet\
	    -lrump -lrumpuser	\
	-Wl,--no-whole-archive -ldl -lm

