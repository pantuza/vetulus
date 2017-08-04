FROM opensuse:latest

RUN zypper update -y && \
    zypper install -y git gcc-c++ cmake ninja make vim which curl

RUN mkdir -pv /vetulus

WORKDIR /vetulus

ADD . /vetulus/

RUN cd /vetulus/scripts/ && ./install_deps.sh

EXPOSE 4242
