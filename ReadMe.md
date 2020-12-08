# Embedded Calculation
This repository contains the work of Pierre-Yves Jezegou (FIPA 2021) for the course : "Calcul Intensif Embarqué"  
([Reference Repository](https://gitlab.ensta-bretagne.fr/reynetol/embedded-computation))

__:exclamation: Codes are Provided as is :exclamation:__

## Requirement
GCC G++ &#8805; 10  
CMAKE &#8805; 3.16

## Compilation:

```bash
cd <TD_FOLDER> && mkdir build && cd build
cmake ../. && cmake --build . -j$(nproc)
```

## TD1 (KA/0-1: Setup/IO-init-cast-ref)

C++20 Toolchain setup and Introduction to C++ 20

#### Installation of GCC and G++ 10 (Ubuntu 20.04):
```bash
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt install gcc-10 g++-10
```
Setting up GCC-10 as default compiler for CMAKE (to copy at the end of ~/.bashc):
```bash
export CC="<path_to_GCC-10>"  # usualy: "/usr/bin/gcc-10"
export CXX="<path_to_G++-10>" # usualy: "/usr/bin/g++-10"
```

## TD2 (KA/2: Functions)

## TD3 (KA/3: Lambdas)

## TD4 (KA/4: Vectors)

## TD5 (KA/4: Vectors)

## TD6 (KA/5: Classes&OperatorOverloading)

## TD7 (KA/6: SignalToolBox WIP)

## Signal Processing (KA/7-8-9: DFT/FFT/STFT)

# Autor:
<table>
  <tr>
    <td>JÉZÉGOU Pierre-Yves</td>
    <td>FIPA 2021</td>
  </tr>
</table>

# LICENCE
[MIT LICENCE](./LICENSE.md)
