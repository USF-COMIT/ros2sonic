tcprewrite  --infile='/home/k2/Downloads/SampleEthernetData/R2_bathy.pcap' \
            --outfile=r2sample_bathy.pcap\
            --dstipmap=10.0.1.102:10.226.212.146\
            --enet-dmac=10.226.211.255\
            --srcipmap=10.0.0.86:10.226.212.146\
            --enet-smac=10.226.211.255\
            --fixcsum

sudo udpreplay -i wlp0s20f3 r2sample_bathy.pcap

