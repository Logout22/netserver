#! /bin/bash
if [ "x$1" = "x" ]; then
  echo "Please specify a target host."
  exit
fi
if [ "x$2" = "x" ]; then
  echo "Please specify a target directory."
  exit
fi

[ -d $2 ] || mkdir -p $2
for i in tcp_stream tcp_maerts udp_stream; do
  for j in {01..100}; do
    bin/netperf -cCH $1 -l 300 -t $i -- -o > $2/$i.$j.csv;
  done
done
for i in tcp_rr tcp_crr udp_rr; do
  for j in {01..100}; do
    bin/netperf -cCH $1 -l -500000 -t $i -- -o > $2/$i.$j.csv;
  done
done

