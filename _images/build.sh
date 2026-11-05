base_t=${base:-"debian:12-slim"}

if [ -z "$1" ]
then
	for f in *.docker; do
    		sudo docker build --build-arg BASE=$base_t -t "${f%%.*}" -f "$f" .
	done
else
	sudo docker build --build-arg BASE=$base_t -t "${1%%.*}" -f "$1" .
fi