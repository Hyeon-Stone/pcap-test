# HW2 | pcap-test
---
## Execute
```
comandline : ./pcap-test <interface>
ex) pcap-test wlan0
```
### Use dummy interface
---
```
$ sudo ip link add dum0 type dummy
$ sudo ifconfig dum0 up
$ sudo ./pcap-test dum0
$ sudo tcpreplay -i dum0 dum0.pcap
```
---
BoB11 Hyeon Seak hun

Reference : gilgil
