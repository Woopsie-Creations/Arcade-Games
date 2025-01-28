as -o Bin/HelloWorld.o main.s

ld -o Bin/HelloWorld Bin/HelloWorld.o \
   -lSystem \
   -syslibroot `xcrun -sdk macosx --show-sdk-path` \
   -e _start \
   -arch arm64 \
   -macos_version_min 15.0.0

./HelloWorld 