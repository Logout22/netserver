#! /bin/bash
if [ "x$1" = "x" ]; then
  echo "Please specify a target host."
  exit
fi
if [ "x$2" = "x" ]; then
  echo "Please specify a target directory."
  exit
fi
mkdir -p $2 > /dev/null 2>&1
for i in tcp_stream tcp_maerts udp_stream; do
  bin/netperf -cCH $1 -t $i -- -o > $2/$i.csv;
done
for i in tcp_rr tcp_crr udp_rr; do
  bin/netperf -cCH $1 -l -1000000 -t $i -- -o > $2/$i.csv;
done

