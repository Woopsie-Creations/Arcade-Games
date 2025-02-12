clear

arm-linux-gnueabihf-as -o Bin/SF.o main.s
arm-linux-gnueabihf-ld -o Bin/SF Bin/SF.o

qemu-arm ./Bin/SF