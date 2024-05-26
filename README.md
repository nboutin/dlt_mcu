# DLT for MCU

## Configuration

### CPM

Add to .bashrc

```bash
export CPM_SOURCE_CACHE=$HOME/.cache/CPM
```

### Build options

* DLT_WITH_ECU_ID
* DLT_WITH_SERIAL
* DLT_WITH_FLOAT

## Build with CMake

```console
cmake -S . -B build -G Ninja
cmake --build build
(cd build/test/unit_test && ctest)
```

## CPM local package override

```console
cmake -S . -B build -G Ninja -DCPM_<dep>_SOURCE=../<dep>
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DCPM_cutie_SOURCE=C:/data/dev/Cutie -DCPM_buffer_mcu_SOURCE=C:/data/dev/buffer_mcu -DCPM_ring_buffer_mcu_SOURCE=C:/data/dev/ring_buffer_mcu
```
