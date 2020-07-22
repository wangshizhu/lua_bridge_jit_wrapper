rm -rf ../build
mv ../bin/lua51.dll ./
rm -rf ../bin
mv ./lua51.dll ../bin
mkdir build
cmake ./ -B ./build
cd build
make