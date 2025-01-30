clear

as -o Bin/SF.o main.s

ld -o Bin/SF Bin/SF.o \
   -lSystem \
   -syslibroot `xcrun -sdk macosx --show-sdk-path` \
   -e _start \
   -arch arm64 \
   -macos_version_min 15.0.0

./Bin/SF 