IP_ADDRESS=$(kubectl get svc | grep attested-tls-service | awk '{print $4}')
sudo docker run vtikoo/attested_tls:1.0 ./non_enc_client/tls_non_enc_client -server:$IP_ADDRESS -port:12341
