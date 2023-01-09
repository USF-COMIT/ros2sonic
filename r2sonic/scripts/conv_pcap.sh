tcprewrite --infile='/home/k2/Downloads/SampleEthernetData/R2_bathy.pcap'   --outfile=r2sample_bathy.pcap --dstipmap=10.0.1.102:131.247.136.111 --enet-dmac=b0:7b:25:a0:53:71 --srcipmap=10.0.0.86:131.247.136.111 --enet-smac=b0:7b:25:a0:53:71 --fixcsum

sudo udpreplay -i enp0s5 r2sample_bathy.pcap 

