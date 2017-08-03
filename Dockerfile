FROM opensuse:latest

RUN zypper update -y && \
    zypper install -y git gcc-c++ gcc7-c++ cmake ninja make vim which

RUN mkdir -pv /vetulus

WORKDIR /vetulus

ADD . /vetulus/

RUN cd /vetulus/scripts/ && ./install_deps.sh

EXPOSE 4242
