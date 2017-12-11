FROM alpine:latest

RUN apk update && \
    apk add bash \
			sudo \
			python \
			git \
            gcc \
			g++ \
			cmake \
			ninja \
			make \
			vim \
			which \
			curl \
			perl \
			go \
			openssl \
            openssl-dev \
            c-ares \
            c-ares-dev \
            zlib \
            zlib-dev \
            protobuf-c \
            protobuf-c-dev

RUN mkdir -pv /vetulus

WORKDIR /vetulus

ADD . /vetulus/

RUN pwd
RUN cd /vetulus/scripts/ && bash install_deps.sh

EXPOSE 4242
