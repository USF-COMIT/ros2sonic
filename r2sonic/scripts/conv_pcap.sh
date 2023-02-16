tcprewrite  --infile='/home/k2/Documents/r2sonic/SampleEthernetData/R2_AI+bathy.pcap' \
            --outfile=r2sample_bathy_ai.pcap\
            --dstipmap=10.0.1.102:10.226.212.146\
            --enet-dmac=bc:6e:e2:36:93:36\
            --srcipmap=10.0.0.86:10.226.212.146\
            --enet-smac=bc:6e:e2:36:93:36\
            --fixcsum

sudo udpreplay -i wlp0s20f3 r2sample_bathy.pcap

