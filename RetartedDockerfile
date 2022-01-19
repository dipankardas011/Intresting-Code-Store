FROM ubuntu:latest

COPY . /usr/var/MATRIX
WORKDIR /usr/var/MATRIX

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install gcc g++ build-essential libncurses-dev -y

CMD [ "make main", "make clean" ]