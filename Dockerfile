FROM opensuse:latest

RUN zypper update -y && \
    zypper install -y \
            git \
            gcc-c++ \
            cmake \
            ninja \
            make \
            automake \
            autoconf \
            vim \
            which \
            curl \
            perl \
            go \
            m4 \
            libtool \
            binutils \
            net-tools \
            telnet

RUN mkdir -pv /vetulus

WORKDIR /vetulus

ADD . /vetulus/

RUN cd /vetulus/scripts/ && bash install_deps.sh
