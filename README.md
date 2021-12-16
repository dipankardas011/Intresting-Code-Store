# Intresting Codes

1. Expression Evaluator
2. 3N+1 Problem

## to run the container
```bash
docker build buildenv -t "name-of-image"
```
to run the contaniner
```ps
docker run --rm -it -v "${pwd}:/root/env" "name-of-image"
```
## Cleanup

Remove the build-evironment image:
```ps
docker rmi "name-of-image" -f
```