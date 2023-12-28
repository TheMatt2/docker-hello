FROM golang as go_build
WORKDIR /src
COPY ./hello.go ./
RUN go build -o /bin/hello_go ./hello.go

FROM gcc as c_build
WORKDIR /src
COPY ./hello.c ./
RUN gcc -std=c11 -Wall -Wextra -Werror -pedantic -Os -static hello.c -o /bin/hello_c

FROM scratch
COPY --from=c_build /bin/hello_c /bin/hello_c
COPY --from=go_build /bin/hello_go /bin/hello_go
CMD ["/bin/hello_c"]
