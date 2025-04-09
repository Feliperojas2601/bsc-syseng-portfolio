### Ejecución 

```docker
docker run -d \
  --name Kylin5-Machine \
  --hostname Kylin5-Machine \
  -m 8G \
  -p 7070:7070 \
  -p 8088:8088 \
  -p 9870:9870 \
  -p 8032:8032 \
  -p 8042:8042 \
  -p 2181:2181 \
  apachekylin/apache-kylin-standalone:5.0-beta
```