Image for macOS and version 3.11 
docker pull arm64v8/cassandra:3.11
docker run --name my-cassandra -d -p 9042:9042 arm64v8/cassandra:3.11
docker exec -it my-cassandra cqlsh
