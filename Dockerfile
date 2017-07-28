FROM alpine:latest

RUN apk update && \
    apk add git g++ cmake ninja make bash vim

RUN mkdir -pv /vetulus

WORKDIR /vetulus

ADD . /vetulus/

RUN cd /vetulus/scripts/ && . install_deps.sh

EXPOSE 4242
