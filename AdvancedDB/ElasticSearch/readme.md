### Run
```docker 
docker pull docker.elastic.co/elasticsearch/elasticsearch:8.13.4
docker network create elastic
docker run --name es01 --net elastic -p 9200:9200 -it -m 1GB docker.elastic.co/elasticsearch/elasticsearch:8.13.4
export ELASTIC_PASSWORD="liBKU+9sgJlMuPgu7VkJ"
docker cp es01:/usr/share/elasticsearch/config/certs/http_ca.crt .
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD https://localhost:9200
```

### Create
```bash
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/1" -H 'Content-Type: application/json' -d'
{
  "nombre": "Magikarp",
  "numero": 129,
  "tipo": ["Agua"],
  "debilidad": ["Eléctrico", "Planta"],
  "descripcion": "Pokémon desvalido. Su cola puede lanzar destellos."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/2" -H 'Content-Type: application/json' -d'
{
  "nombre": "Charmander",
  "numero": 4,
  "tipo": ["Fuego"],
  "debilidad": ["Agua", "Tierra", "Roca"],
  "descripcion": "Pokémon lagarto. La llama en su cola muestra su estado emocional."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/3" -H 'Content-Type: application/json' -d'
{
  "nombre": "Bulbasaur",
  "numero": 1,
  "tipo": ["Planta", "Veneno"],
  "debilidad": ["Fuego", "Psíquico", "Volador"],
  "descripcion": "Pokémon semilla. Su semilla brota y crece con el tiempo."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/4" -H 'Content-Type: application/json' -d'
{
  "nombre": "Squirtle",
  "numero": 7,
  "tipo": ["Agua"],
  "debilidad": ["Eléctrico", "Planta"],
  "descripcion": "Pokémon tortuga. Puede retraer su cuerpo dentro de su caparazón para protegerse."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/5" -H 'Content-Type: application/json' -d'
{
  "nombre": "Pikachu",
  "numero": 25,
  "tipo": ["Eléctrico"],
  "debilidad": ["Tierra"],
  "descripcion": "Pokémon ratón. Sus mejillas almacenan electricidad."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/6" -H 'Content-Type: application/json' -d'
{
  "nombre": "Jigglypuff",
  "numero": 39,
  "tipo": ["Normal", "Hada"],
  "debilidad": ["Acero", "Veneno"],
  "descripcion": "Pokémon globo. Puede cantar melodías que inducen el sueño."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/7" -H 'Content-Type: application/json' -d'
{
  "nombre": "Meowth",
  "numero": 52,
  "tipo": ["Normal"],
  "debilidad": ["Lucha"],
  "descripcion": "Pokémon gato araña. Adora las monedas brillantes."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/8" -H 'Content-Type: application/json' -d'
{
  "nombre": "Psyduck",
  "numero": 54,
  "tipo": ["Agua"],
  "debilidad": ["Eléctrico", "Planta"],
  "descripcion": "Pokémon pato. Sufre de constantes dolores de cabeza."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/9" -H 'Content-Type: application/json' -d'
{
  "nombre": "Eevee",
  "numero": 133,
  "tipo": ["Normal"],
  "debilidad": ["Lucha"],
  "descripcion": "Pokémon evolución. Puede evolucionar en múltiples formas diferentes."
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_doc/10" -H 'Content-Type: application/json' -d'
{
  "nombre": "Snorlax",
  "numero": 143,
  "tipo": ["Normal"],
  "debilidad": ["Lucha"],
  "descripcion": "Pokémon dormilón. Duerme la mayor parte del día y solo se despierta para comer."
}'
```

### Update
```bash 
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_update/1" -H 'Content-Type: application/json' -d'
{
  "doc": {
    "nombre": "Gyarados",
    "numero": 130,
    "tipo": ["Agua", "Volador"],
    "debilidad": ["Eléctrico", "Roca"],
    "descripcion": "Pokémon atrocidad. Evolucionado de Magikarp."
  }
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_update/2" -H 'Content-Type: application/json' -d'
{
  "doc": {
    "nombre": "Charmeleon",
    "numero": 5,
    "tipo": ["Fuego"],
    "debilidad": ["Agua", "Tierra", "Roca"],
    "descripcion": "Pokémon llama. Evolucionado de Charmander."
  }
}'

curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X POST "https://localhost:9200/pokedex/_update/3" -H 'Content-Type: application/json' -d'
{
  "doc": {
    "nombre": "Ivysaur",
    "numero": 2,
    "tipo": ["Planta", "Veneno"],
    "debilidad": ["Fuego", "Psíquico", "Volador"],
    "descripcion": "Pokémon semilla. Evolucionado de Bulbasaur."
  }
}'
```

### Read

```bash
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X GET "https://localhost:9200/pokedex/_search" -H 'Content-Type: application/json' -d'
{
  "query": {
    "match_all": {}
  }
}'
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X GET "https://localhost:9200/pokedex/_search" -H 'Content-Type: application/json' -d'
{
  "query": {
    "match": {
      "descripcion": "cola"
    }
  }
}'
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X GET "https://localhost:9200/pokedex/_search" -H 'Content-Type: application/json' -d'
{
  "query": {
    "match": {
      "tipo": "Fuego"
    }
  }
}'
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X GET "https://localhost:9200/pokedex/_search" -H 'Content-Type: application/json' -d'
{
  "query": {
    "match_phrase": {
      "descripcion": "Pokémon desvalido"
    }
  }
}'
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X GET "https://localhost:9200/pokedex/_search" -H 'Content-Type: application/json' -d'
{
  "query": {
    "match": {
      "peso": 10
    }
  }
}'
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X GET "https://localhost:9200/pokedex/_search" -H 'Content-Type: application/json' -d'
{
  "size": 1,
  "sort": {
    "debilidad": {
      "order": "desc"
    }
  },
  "query": {
    "match_all": {}
  }
}'
```

### Delete

```bash
curl --cacert http_ca.crt -u elastic:$ELASTIC_PASSWORD -X DELETE "https://localhost:9200/pokedex/_doc/3"
```


