DESC KEYSPACES;
CREATE KEYSPACE IF NOT EXISTS taller_keyspace WITH replication = {'class': 'SimpleStrategy', 'replication_factor': 1};
USE taller_keyspace;
CREATE TABLE IF NOT EXISTS Usuario (
    id_usuario TEXT PRIMARY KEY,
    seguidores MAP<TEXT, BOOLEAN>,
    seguidos MAP<TEXT, BOOLEAN>
);
INSERT INTO Usuario (id_usuario, seguidores, seguidos) VALUES ('X', {'UsuarioY': true, 'UsuarioZ': false}, {'UsuarioY': true, 'UsuarioZ': true});
INSERT INTO Usuario (id_usuario, seguidores, seguidos) VALUES ('Y', {'UsuarioX': true, 'UsuarioZ': true}, {'UsuarioX': true});
INSERT INTO Usuario (id_usuario, seguidores, seguidos) VALUES ('Z', {'UsuarioX': true}, {'UsuarioX': false, 'UsuarioY': true});
