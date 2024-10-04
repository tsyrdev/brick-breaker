COMPILE="clang++ -std=c++17 ./src/*.cpp -I./include -o ./bin/prog -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_ttf"
echo ${COMPILE}
eval $COMPILE
