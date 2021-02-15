git submodule update --force --recursive --init

mkdir -p third-party/assimp/build
cmake -S third-party/assimp -B third-party/assimp/build/
cd third-party/assimp/build/
make -j4
cd ../../..

mkdir -p third-party/glad/build
cmake -S third-party/glad -B third-party/glad/build/
cd third-party/glad/build/
make 
cd ../../..

mkdir -p third-party/glfw/build
cmake -S third-party/glfw -B third-party/glfw/build/
cd third-party/glfw/build/
make -j4
cd ../../..

mkdir lib
cp third-party/assimp/build/code/libassimp* lib/
cp third-party/glad/build/libglad.a lib/
cp third-party/glfw/build/src/libglfw3.a lib/
cp third-party/assimp/build/include/assimp/config.h third-party/assimp/include/assimp/