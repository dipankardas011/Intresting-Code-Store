FROM golang:1.18 as build

WORKDIR /home
COPY . .
RUN go build -o runner .
CMD [ "./runner" ]
EXPOSE 80
