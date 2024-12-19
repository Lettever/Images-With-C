default:
    just --list

build:
    gcc src/*.c -o out.exe

clean:
    rm -f ./out.exe
run:
    ./out.exe

br: clean build run