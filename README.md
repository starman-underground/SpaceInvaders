# Configure CMake
mkdir build
cmake -B build

# Build Command
cmake --build build

## Speeding up builds

### Linux
cmake --build build -j ${nproc}

### Mac OS
cmake --build build -j ${sysctl -n hw.ncpu}

# Run Command
./build/bin/SpaceInvaders
