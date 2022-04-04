```
docker run -it --rm -p 8080:8080 -v ${PWD}:/home golang:latest
cd /home
go build . && ./http
```