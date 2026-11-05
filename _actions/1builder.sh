sudo docker run --rm \
-v "$(pwd)/src:/src" \
-v "$(pwd)/build:/build" \
-v "$(pwd)/work:/work" \
builder
