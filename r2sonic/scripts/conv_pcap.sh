#!/bin/bash

PCAP_FILE=$1

INTERFACE=$2

IP_ADDR=$(ip -f inet addr show $INTERFACE | sed -En -e 's/.*inet ([0-9.]+).*/\1/p')
MAC_ADDR=$(cat /sys/class/net/$INTERFACE/address)

echo "modifying pcap file with your network settings"

tcprewrite  --infile=$PCAP_FILE \
            --outfile=r2_temp.pcap\
            --dstipmap=10.0.1.102:$IP_ADDR\
            --enet-dmac=$MAC_ADDR\
            --srcipmap=10.0.0.86:$IP_ADDR\
            --enet-smac=$MAC_ADDR\
            --fixcsum

echo "replaying the file on IP: $IP_ADDR with mac: $MAC_ADDR  (<ctrl>+c) to stop"

sudo udpreplay -i $INTERFACE r2_temp.pcap -r -1

rm r2_temp.pcap

