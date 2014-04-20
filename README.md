This repo holds an adapted netserver (part of [netperf](http://www.netperf.org/)) ready to work with Rump.
It is Q&D, but maybe of some use. Improving patches welcome.
A short description of what to do:

Computer 1:
- Download and install [netperf](http://www.netperf.org/) version 2.6.0 (see their README)
- Set up netserver:

        git clone https://github.com/Logout22/netserver
        cd netserver
        git checkout virtif
        cp ../netperf-2.6.0/config.h .
        ./compile_netserver.sh

- Setup DHCP server, if there is none
- Install bridge according to [this article](https://github.com/rumpkernel/wiki/wiki/Howto:-Networking-with-if_virt)
- Start netserver

        cd netserver
        ./start-netserver.sh (prints IP address assigned by DHCP)

Computer 2:
- Download and install netperf-2.6.0
- Start netperf:

        cd netperf-2.6.0
        netperf -H <IP address shown before> -t tcp_stream

Troubleshooting:

- Use negative -l values (signals do not work sometimes)

        netperf -H ... -l -1000 -t tcp_rr

- Oversized frames are discarded: set send/receive socket sizes to 1492

        netperf -H ... -t tcp_stream -- -s 1492,1492 -S 1492,1492

Please be aware that this can be quite slow. Please check with
Wireshark for packet transmissions or try another benchmark
if you see no progress.
