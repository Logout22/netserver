#! /bin/bash
if [ "x$1" = "x" ]; then
  echo "Please specify a target directory."
  exit
fi
mkdir ~/stats/$1 > /dev/null 2>&1
for i in tcp_stream tcp_maerts udp_stream; do
  bin/netperf -H 192.168.0.1 -t $i -- -o > ~/stats/$1/$i.csv;
done
for i in tcp_rr tcp_cc tcp_crr udp_rr; do
  bin/netperf -H 192.168.0.1 -l -1000000 -t $i -- -o > ~/stats/$1/$i.csv;
done

