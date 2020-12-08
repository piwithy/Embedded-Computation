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

#### Build and Run:
```bash
cd TD1 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./calculation_td1
```

##### Output:
```
argc: 1 argv: ./calculation_td1
Hello World!
x:      1       3       5       7       9       11      13      15      17
y:      66      3       5       7       9       11      13      15      17
Swap! x<->y
x:      66      3       5       7       9       11      13      15      17
y:      1       3       5       7       9       11      13      15      17
Move: x->y: X0 66
```

## TD2 (KA/2: Functions)

Introduction on Functions

#### Build and Run:
```bash
cd TD2 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./TD2
```

##### Output:
```
Hello, World!
[ (1,1), (1.7,3), (3.24,1) ]
[ -3, -1, 1, 3, 5, 7, 9 ]
[ 3, 5, 7, 9 ]
(1+i) + (1-i) = (2,0)
(1+i) - (1-i) = (0,2)
(1+i) * (1-i) = (2,0)
(1+i) / (1-i) = (0,1)
[ (1,0), (-1,1.22465e-16) ]
```

## TD3 (KA/3: Lambdas)

Introduction on Lambdas Expressions

#### Build and Run:
```bash
cd TD3 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./TD3
```

##### Output:
```
Hello World!
Proud to be Lambda !
++Factor= 4
8 div 7 ? false
42 div 2 ? true
```


## TD4 (KA/4: Vectors)

Introduction of `std::vector<Type>`

#### Build and Run:
```bash
cd TD4 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./TD4
```

##### Output:
```
Hello, World!
vec=[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
vec.size=11     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=12     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=13     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=14     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=15     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=16     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=17     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=18     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=19     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=20     vec.capacity=20 vec.max_size=1152921504606846975
vec.size=21     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=22     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=23     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=24     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=25     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=26     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=27     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=28     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=29     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=30     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=31     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=32     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=33     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=34     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=35     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=36     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=37     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=38     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=39     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=40     vec.capacity=40 vec.max_size=1152921504606846975
vec.size=41     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=42     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=43     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=44     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=45     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=46     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=47     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=48     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=49     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=50     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=51     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=52     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=53     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=54     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=55     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=56     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=57     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=58     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=59     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=60     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=61     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=62     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=63     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=64     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=65     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=66     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=67     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=68     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=69     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=70     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=71     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=72     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=73     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=74     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=75     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=76     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=77     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=78     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=79     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=80     vec.capacity=80 vec.max_size=1152921504606846975
vec.size=81     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=82     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=83     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=84     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=85     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=86     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=87     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=88     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=89     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=90     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=91     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=92     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=93     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=94     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=95     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=96     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=97     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=98     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=99     vec.capacity=160        vec.max_size=1152921504606846975
vec.size=100    vec.capacity=160        vec.max_size=1152921504606846975
vec=[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
vec.size=100    vec.capacity=100        vec.max_size=1152921504606846975
```

## TD5 (KA/4: Vectors)

Continuation on `std::vector<typename>`. Introduction of the vectors manipulation functions

#### Build and Run:
```bash
cd TD5 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./TD5
```

##### Output:
```
vec_sum: 8.38965e+08
v_ec max: 50
calcul  m= 50.0062      std= 28.8659
theorie m= 50           std= 28.8675
```

## TD6 (KA/5: Classes&OperatorOverloading)

Introduction on Classes in C++

#### Build and Run:
```bash
cd TD6 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./tests/TEST
```

##### Output:
```
===============================================================================
All tests passed (111 assertions in 3 test cases)
```

## TD7 (KA/6: SignalToolBox WIP)

Construction of a C++ Signal ToolBox

##### Header

```c++
constexpr size_t N = 256;
typedef std::complex<double> Complex;

std::vector<double> makeTimeVector(double Fs, std::size_t size);

std::vector<double> makeFrequencyVector(double Fs, std::size_t size);

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f);

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm);

constexpr std::array<Complex, N> rect_window();

constexpr std::array<Complex, N> cosine_window(double a0);

constexpr std::array<Complex, N> hann_window();

constexpr std::array<Complex, N> hamming_window();

constexpr std::array<Complex, N> blackman_window();

template<typename T>
std::vector<T> generate_random_vector(double inf, double sup, std::size_t size);

std::vector<double> toReal(const std::vector<Complex> &x);

std::vector<double> toImag(const std::vector<Complex> &x);

std::vector<Complex> toComplex(const std::vector<double> &x);

double sin(double f, double t, double phi = 0);

void windowing(const std::array<double, N> &w, std::vector<Complex> &s);

std::vector<double> psd(const std::vector<Complex> &dft);
```

#### Build and Run:
```bash
cd TD6 && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./tests/TEST
```

##### Output:
```
Test Vector: [-0.236468, -0.192966, -0.193747, 0.12682]
Test Time: [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9, 7, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9, 8, 8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9, 9, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9]
Test Frequency: [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990]
Complex Vector: [(0,0), (0,1), (1,1), (1,0)]
Re(Complex Vector): [0, 0, 1, 1]
Im(Complex Vector): [0, 1, 1, 0]
Complex From Real: [(0,0), (0,0), (1,0), (1,0)]
Sin Vector: [0, -2.44929e-16, -4.89859e-16, -7.34788e-16, -9.79717e-16, -1.22465e-15, -1.46958e-15, -1.71451e-15, -1.95943e-15, -2.20436e-15, -2.44929e-15, 4.4112e-15, -2.93915e-15, 3.92135e-15, -3.42901e-15, -1.07794e-14, -3.91887e-15, -1.12692e-14, -4.40873e-15, -1.17591e-14, -4.89859e-15, 1.96191e-15, 8.82241e-15, -1.27388e-14, -5.8783e-15, 9.82193e-16, 7.84269e-15, 1.47032e-14, -6.85802e-15, 2.47592e-18, -2.15587e-14, -1.46982e-14, -7.83774e-15, -2.9399e-14, -2.25385e-14, -1.5678e-14, -8.81746e-15, -1.95696e-15, -2.35182e-14, -1.66577e-14, -9.79717e-15, -3.13584e-14, 3.92382e-15, -1.76374e-14, 1.76448e-14, -3.91639e-15, -2.54776e-14, 9.8046e-15, -1.17566e-14, 2.35256e-14, 1.96439e-15, -1.95968e-14, 1.56854e-14, -5.87583e-15, 2.94064e-14, 7.84517e-15, -1.3716e-14, 2.15662e-14, 4.95185e-18, 3.52872e-14, -4.31175e-14, -6.46787e-14, -2.93965e-14, -5.09577e-14, -1.56755e-14, -3.72367e-14, -5.87979e-14, -2.35157e-14, -4.50769e-14, -9.7947e-15, -3.13559e-14, -5.29171e-14, -1.76349e-14, -3.91961e-14, -3.91392e-15, -2.54751e-14, -4.70363e-14, -1.17541e-14, -3.33153e-14, 1.96686e-15, -1.95943e-14, -4.11556e-14, -6.27168e-14, 2.94089e-14, 7.84764e-15, -1.37136e-14, -3.52748e-14, -5.6836e-14, 3.52896e-14, 1.37284e-14, -7.83279e-15, -2.9394e-14, -5.09552e-14, 4.11704e-14, 1.96092e-14, -1.95201e-15, -2.35132e-14, -4.50744e-14, 4.70512e-14, 2.549e-14]
Random Vector: [3.38544, 8.67436, 1.49852, 5.63336, 4.17453]
```

## Signal Processing (KA/7-8-9: DFT/FFT/STFT)

### signal_utils
(signal tool box)

common.h
```c++
typedef std::complex<double> Complex;
constexpr size_t N = 512;
typedef std::chrono::microseconds Duration;

template<std::size_t DIM>
constexpr std::array<std::size_t, DIM> bit_reverse_array();

template<std::size_t DIM>
constexpr std::array<Complex, DIM / 2> twiddle_factors();
```

signal_utils.h
```c++
template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v);

std::vector<double> makeTimeVector(double Fs, std::size_t size);

std::vector<double> makeFrequencyVector(double Fs, std::size_t size);

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f);

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm);


std::vector<double> psd(const std::vector<Complex> &dft);


std::vector<double> toReal(const std::vector<Complex> &x);

template<typename Tcontainer, typename Tsignal>
std::vector<Tcontainer> generate_random_vector(Tsignal inf, Tsignal sup, std::size_t size);


template<typename F,
        typename ... Args>
Duration::rep wall_time_profile(F &&fun, Args &&... args);

template<typename F,
        typename ... Args>
Duration::rep cpu_time_profile(F &&fun, Args &&... args);

std::pair<typename std::chrono::milliseconds::rep, typename std::chrono::milliseconds::rep>
average_stddev(const std::vector<typename std::chrono::milliseconds::rep> &data);

template<typename F,
        typename ... Args>
Duration::rep wall_time_average_profile(std::size_t nRuns, F &&fun, Args &&... args);


template<typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &s, const std::array<T, SIZE> &a);


template<typename T>
std::tuple<bool, int, double> epsilon_vector_compare(const std::string &title, std::vector<T> x, std::vector<T> y);

template<typename F,
        typename ... Args>
void peakDetection(const std::string &title, double Fs, std::vector<Complex> &signal, F &&fun, Args &&... args);

void windowing(const std::array<double, N> &w, std::vector<Complex> &s);
```

dft/dft.h
```c++
template<std::size_t DIM>
constexpr std::array<Complex, DIM * DIM> make_nroot_lut();

template<typename T>
std::vector<Complex> naive_dft(const std::vector<T> &X);

template<typename T>
std::vector<Complex> lut_dft(const std::vector<T> &X, std::array<Complex, N> &lut);

template<typename T>
std::vector<Complex> recursive_fft(const std::vector<T> &X);
```

fft/fft.h
```c++
void v_rect_dit_fft(std::vector<Complex> &x);

void v_rect_dit_fft_array(Complex *x, std::size_t x_size);

void ite_dit_fft(std::vector<Complex> &x);

void ite_dit_fft_array(Complex *x, std::size_t x_size);

void v_rect_dif_fft(std::vector<Complex> &x);

void v_rect_dif_fft_array(Complex *x, std::size_t x_size);

void ite_dif_fft(std::vector<Complex> &x);

void ite_dif_fft_array(Complex *x, size_t x_size);
```

stft/stft.h
```c++
void placeholder();
```

SignalProcessing
(executable)
#### Build and Run:
```bash
cd signal_processing && mkdir build && cd build
cmake ../. && cmake --build . -j $(nproc)
./SignalProcessing
```

##### Output*:
```
Version 1.0
Testing FFT!
 ----- FFT COMPUTING | SINUS: f=889Hz sampled at 22050Hz -----
DIT RECUR FFT VEC ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----
DIT RECUR FFT ARR ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----
DIT ITER  FFT VEC ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----
DIT ITER  FFT ARR ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----

DIF RECUR FFT VEC ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----
DIF RECUR FFT ARR ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----
DIF ITER  FFT VEC ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 53        Max frequency --> 2282.52 Hz,  Max Value : 18659.7 -----
DIF ITER  FFT ARR ----- Fs : 22050 Hz,  Resolution : 43.0664     Max index --> 21        Max frequency --> 904.395 Hz,  Max Value : 41640.6 -----
 ----- FFT SPEED TEST | RANDOM VECTOR size N=512 -----
DIT RECUR FFT VEC ----- 100 runs: average = 75 µs, stdev = 4 µs.
DIT RECUR FFT ARR ----- 100 runs: average = 44 µs, stdev = 2 µs.
DIT ITER  FFT VEC ----- 100 runs: average = 17 µs, stdev = 5 µs.
DIT ITER  FFT ARR ----- 100 runs: average = 20 µs, stdev = 1 µs.

DIF RECUR FFT VEC ----- 100 runs: average = 75 µs, stdev = 8 µs.
DIF RECUR FFT ARR ----- 100 runs: average = 63 µs, stdev = 2 µs.
DIF ITER  FFT VEC ----- 100 runs: average = 20 µs, stdev = 1 µs.
DIF ITER  FFT ARR ----- 100 runs: average = 19 µs, stdev = 1 µs.
DIF ITER Vector, Array are same ? --> false      distinct = 343  accuracy = 33%  max delta = 135
```
*on my machine


# Autor:
<table>
  <tr>
    <td>JÉZÉGOU Pierre-Yves</td>
    <td>FIPA 2021</td>
  </tr>
</table>

# LICENCE
[MIT LICENCE](./LICENSE.md)
