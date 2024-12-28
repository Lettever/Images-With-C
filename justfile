set shell := ["nu", "-c"]

default:
    just --list

build:
    clang src/*.c -Wall -Wextra -o out.exe

clean:
    rm -f ./out.exe
run:
    ./out.exe

br: clean build run
