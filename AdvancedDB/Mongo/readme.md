## Run
```docker
docker run --name my-mongo -p 27017:27017 -d mongo:5
```
## Mapreduce 
```docker
docker run --name my-mongo -p 27017:27017 -d mongo:4
docker cp data.json my-mongo:/data.json
docker exec -it my-mongo mongoimport --db restaurantes --collection restaurantes --file /data.json
```