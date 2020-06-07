make clean
make
sudo docker build -t vtikoo/attested_tls:1.0 .
sudo docker push vtikoo/attested_tls:1.0
