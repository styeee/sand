port_v="${port:-55555}"
sudo docker run --rm \
-v "$(pwd)/work:/work" \
-p $port_v:$port_v \
-e port=$port_v \
-d runner
