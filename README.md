# SignalGenerator
This is a C library for generating signals :
* Sinus
* Triangle
* Ramp
* Square
* Sawtooth
## Signal Parameters
Parameters | Range | Type | Sinus | Triangle | Ramp | Square | Sawtooth
:--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
Offset ||F|X|X|X|X|X
Amplitude ||F|X|X||X|X
Frequency ||F|X|X||X|X
Sampling Frequency ||Int|X|X|X|X|X
Phase |0-2π|F|X|X||X|X
Damping Factor ||F|X|X||X|X
Slope ||F|||X||
Duty Cycle |0-100|F||||X|

**Definition** : \
*Damping Factor* : It is a coefficient to raw value of each sample like Amplitude\
DF in ``e^(-(DT*time))``

## How to use
Pass 1 which one you want :
```c
#define INCLUDE_DAMPING 1
#define USE_DOUBLE 0
#define INCLUDE_AMPLITUDE 1
#define INCLUDE_OFFSET 1
#define INCLUDE_PHASE 1
#define INCLUDE_SINLOOKUPTABLE 1
```
In this Library for calculating *Sinus* wave there are two ways:
1. using `sin` function in `math.h`
2. using an array saving 100k samples of one cycle from sinus wave

In order to use second option enable `#define INCLUDE_SINLOOKUPTABLE` 

For each Signals two functions provided : **Init** and **OneSample** \
**Init** functions set signal's parameters and should be called at first \
**OneSample** functions give one sample of signal and can be called consecutively 
### Tests
Two tests provided [both in main.c] :
1. Generating the signals separately
2. Generating the the signals together in order to the last sample of previous signal is the offset of next signal
