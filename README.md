Computer 1:
- Download and install netperf-2.6.0
- Copy config.h to netserver repo
- Setup DHCP server, if there is none
- Install bridge according to:
https://github.com/rumpkernel/buildrump.sh/wiki/virtif-networking-howtos
- cd to netserver repo
- ./compile_netserver.sh
- ./start-netserver.sh (shows IP address assigned by DHCP)
Computer 2:
- Download and install netperf-2.6.0
- cd to netperf directory
- Start netperf:
netperf -H <IP address shown before> -t tcp_stream

Troubleshooting:
- Use negative -l values (signals do not work sometimes)
netperf -H ... -l -1000 -t tcp_stream
- Oversized frames discarded by virtif: set send/receive socket sizes  local and remote (-s,-S) to 1492
netperf -H ... -t tcp_stream -- -s 1492,1492 -S 1492,1492

