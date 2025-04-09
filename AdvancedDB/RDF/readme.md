1. Instala Docker y Java.

2. **Ejecuta Hadoop**: 
   ```
   docker pull sequenceiq/hadoop-docker:2.7.1
   ```

   ```
   docker run --name hadoop-container -it sequenceiq/hadoop-docker:2.7.1 /etc/bootstrap.sh -bash
   ```

   ```
   export PATH=$PATH:/usr/local/hadoop/bin
   ```

3. **Copia el archivo TTL al contenedor**: Una vez que tengas el ID o el nombre del contenedor, puedes usar el comando `docker cp` para copiar el archivo TTL desde tu sistema local al contenedor. Por ejemplo, si tu contenedor se llama `mi-contenedor` y el archivo TTL que deseas copiar se encuentra en `/ruta/a/tu/archivo.ttl` en tu sistema local, ejecuta el siguiente comando:

   ```
   docker cp datos.ttl hadoop-container:/datos.ttl
   ```

   Esto copiará el archivo `archivo.ttl` desde tu sistema local al directorio `/ruta/en/contenedor/` dentro del contenedor con nombre `mi-contenedor`.

4. **Transfiere el archivo TTL a Hadoop**: Una vez que Hadoop está configurado, necesitas transferir tu archivo TTL al sistema de archivos HDFS de Hadoop. Puedes usar el comando `hadoop fs -put` para cargar el archivo TTL desde tu sistema local al sistema de archivos HDFS. Por ejemplo:

   ```
   hadoop fs -put /datos.ttl /input
   ```

5. **Verifica la carga del archivo**: Puedes verificar si el archivo se ha cargado correctamente usando el comando `hadoop fs -ls`. Por ejemplo:

   ```
   hadoop fs -ls /input
   ```

   Esto debería mostrar el archivo TTL que has cargado en el sistema de archivos HDFS.

