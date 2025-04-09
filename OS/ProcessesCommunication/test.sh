#!/bin/
sizes=(125 1250 12500 125000 1250000 12500000)
echo "Pipe"
for i in ${sizes[@]}
do
    gcc Pipe.C -o Pipe
    ./Pipe $i
    wait
done
sleep 1
echo "FIFO"
for i in ${sizes[@]}
do
    gcc MkFIFOProducer.C -o MKFIFOProducer 
    gcc MkFIFOReceptor.C -o MKFIFOReceptor 
    ./MKFIFOProducer $i & ./MKFIFOReceptor $i
    wait  
done
gcc files.c -o files -lpthread
gcc sharedMem.c -o sharedMem -lpthread
sizes1=(1000 10000 100000 1000000 10000000 100000000)
echo "Archivos:"
for i in ${sizes1[@]}
do
  ./files $i
done
sleep 1
echo "Memoria compartida:"
for i in ${sizes1[@]}
do
  ./sharedMem $i
done
sleep 1
echo "Sockets"
for i in ${sizes[@]}
do
    gcc Server.C -o server &
    ./server $i & 
    gcc Client.C -o client
    ./client $i 127.0.0.1 
    wait
done


