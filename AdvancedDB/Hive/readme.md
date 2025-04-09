## Run
STEP 1: Pull the image.
```
docker pull apache/hive:4.0.0
```

STEP 2: Launch the HiveServer2 with an embedded Metastore.
This is lightweight and for a quick setup, it uses Derby as metastore db.
```
docker run -d -p 10000:10000 -p 10002:10002 --env SERVICE_NAME=hiveserver2 --name hive4 apache/hive:4.0.0
```

STEP 3: Connect to beeline.
```
docker exec -it hive4 beeline -u 'jdbc:hive2://localhost:10000/'
```

Note: Launch Standalone Metastore To use standalone Metastore with Derby.
```
docker run -d -p 9083:9083 --env SERVICE_NAME=metastore --name metastore-standalone apache/hive:${HIVE_VERSION}
```