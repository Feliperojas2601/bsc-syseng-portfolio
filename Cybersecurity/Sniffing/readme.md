### Run 
Use docker to run ubuntu 16.04 
```
docker pull ubuntu:16.04
```
```
docker run -it --name ubuntu1604 ubuntu:16.04 /bin/bash
```
Install python and scapy 
```
apt-get install -y python3 python3-pip python3-dev libpcap-dev
```
```
pip3 install scapy
```
Create directory to store all .py files
```
mkdir scripts
```
Create an n.py sniffing file 
```
nano scripts/n.py
```
Run an n.py sniffing file 
```
python3 scripts/n.py
```
Create a first sniffer that ask for the IP address of the container
```python
# Importa la biblioteca Scapy
from scapy.all import *

# Función principal
if __name__ == "__main__":  
    a = IP()
    a.show()
```
Create a sniffer script that captures ICMP packets
```python
from scapy.all import *

# Función para imprimir los paquetes capturados
def print_pkt(pkt):
    pkt.show()

# Función principal
if __name__ == "__main__":
    # Sniffing de paquetes ICMP y llamada a la función print_pkt para imprimirlos
    sniff(filter='icmp', prn=print_pkt)
```
Create a sniffer script that captures TCP packets
```python
from scapy.all import *

# Función para imprimir los paquetes capturados
def print_pkt(pkt):
    pkt.show()

# Función principal
if __name__ == "__main__":
    # Sniffing de paquetes TCP y llamada a la función print_pkt para imprimirlos
    sniff(filter='tcp', prn=print_pkt)
```
Create a sniffer script that captures TCP packets from a particular IP and with a destination port number 23
```python
from scapy.all import *

# Función para imprimir los paquetes capturados
def print_pkt(pkt):
    pkt.show()

# Función principal
if __name__ == "__main__":
    # Sniffing de paquetes TCP desde IP a puerto y llamada a la función print_pkt para imprimirlos
    sniff(filter='tcp and src host 64.233.167.99 and dst port 23', prn=print_pkt)
```
Create a sniffer script that captures packets that come from or to go to a particular subnet. 
You pick any subnet, such as 168.176.0.0/16; do not pick the subnet that your VM is attached to.
```python
from scapy.all import *

# Función para imprimir los paquetes capturados
def print_pkt(pkt):
    pkt.show()

# Función principal
if __name__ == "__main__":
    # Sniffing de paquetes en red y llamada a la función print_pkt para imprimirlos
    sniff(filter='net 168.176.0.0/16', prn=print_pkt)
```
Spoof ICMP packets: create a script that set fields packets to arbitrary values (change the source IP address). 
Use Wireshark to observe whether your requests are accepted by the receiver (destination IP).
```python
from scapy.all import *
import random

def send_random_icmp_packets(destination_ip, num_packets):
    for _ in range(num_packets):
        # Genera una dirección IP de origen aleatoria
        spoofed_source_ip = ".".join(map(str, (random.randint(0, 255) for _ in range(4))))

        # Construye el paquete ICMP con la dirección IP de origen falsificada
        packet = IP(src=spoofed_source_ip, dst=destination_ip) / ICMP()

        # Envía el paquete
        send(packet)

# Dirección IP de destino
destination_ip = "192.168.1.100" 

# Número de paquetes a enviar
num_packets = 5  

# Envía múltiples paquetes ICMP con direcciones IP de origen aleatorias
send_random_icmp_packets(destination_ip, num_packets)
```
