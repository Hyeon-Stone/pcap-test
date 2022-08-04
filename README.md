# HW2 | pcap-test
_**Please view Terminal Full Screen!!**_
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
### Result
---
![Print Info](https://user-images.githubusercontent.com/79035672/182746508-7c5baeef-d425-4694-88c9-a2f4038ebd41.png)
---
BoB11 Hyeon Seak hun

Reference : gilgil

Reference(Only Print Format) : https://biji-jjigae.tistory.com/45?category=821384
