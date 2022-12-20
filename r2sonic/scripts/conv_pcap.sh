tcprewrite --infile='/media/psf/Dropbox/Work/USF/r2sonic_driver/docs/R2_EthernetDataSamples/SampleEthernetData/R2_bathy.pcap'   --outfile=r2sample_bathy.pcap --dstipmap=10.0.1.102:10.0.1.102 --enet-dmac=00:1c:42:47:cd:f0 --srcipmap=10.0.0.86:10.0.1.102 --enet-smac=00:1c:42:47:cd:f0 --fixcsum

sudo udpreplay -i enp0s5 r2sample_bathy.pcap 

