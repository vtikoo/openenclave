FROM ubuntu:18.04

## Install tools required to install openenclave
RUN apt update; apt -y install wget gnupg python apt-transport-https libssl1.0.0 libssl-dev

## Adding the Intel and Microsoft repositories to apt
RUN echo 'deb [arch=amd64] https://download.01.org/intel-sgx/sgx_repo/ubuntu bionic main' | tee /etc/apt/sources.list.d/intel-sgx.list \
    && wget -qO - https://download.01.org/intel-sgx/sgx_repo/ubuntu/intel-sgx-deb.key | apt-key add -
RUN echo "deb [arch=amd64] https://packages.microsoft.com/ubuntu/18.04/prod bionic main" | tee /etc/apt/sources.list.d/msprod.list \
    && wget -qO - https://packages.microsoft.com/keys/microsoft.asc | apt-key add -

## Install openenclave & openenclave platform software (psw)
RUN apt update \
    && apt -y install libsgx-enclave-common libsgx-enclave-common-dev libsgx-dcap-ql libsgx-dcap-ql-dev az-dcap-client open-enclave gcc g++

# COPY . /samples/
# WORKDIR /samples/attested_tls/

# ## Copy over the samples, Source openenclaverc, Set up environment variables, Make the sample
# RUN cp -R /opt/openenclave/share/openenclave/samples . \
#     && . /opt/openenclave/share/openenclave/openenclaverc \
#     && export CC=gcc && export CXX=g++ && export PKG_CONFIG_PATH=/opt/openenclave/share/pkgconfig/ \
#     && make

# CMD make run
COPY config.mk /samples/
COPY . /samples/attested_tls
WORKDIR /samples/attested_tls
CMD make run
