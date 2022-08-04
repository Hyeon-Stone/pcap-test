# HW2 | pcap-test

| Ethernet Header의 MAC<br>
| IP Header의 IP<br>
| TCP Header의 PORT<br>
| TCP Payload가 있다면 최대 10Byte까지 출력
---
## Execute
```
comandline : ./pcap-test <interface>
ex) pcap-test wlan0
```
---
### Use dummy interface
```
$ sudo ip link add dum0 type dummy
$ sudo ifconfig dum0 up
$ sudo ./pcap-test dum0
$ sudo tcpreplay -i dum0 dum0.pcap
```
---
## Result
_**Please view Terminal Full Screen!!**_

---
![Print Info](https://user-images.githubusercontent.com/79035672/182746508-7c5baeef-d425-4694-88c9-a2f4038ebd41.png)

---
| BoB11 Hyeon Seak hun

| Reference : gilgil

| Reference(Only Print Format) : https://biji-jjigae.tistory.com/45?category=821384
