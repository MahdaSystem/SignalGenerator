#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H
#include <math.h>
#include <stdint.h>

#define INCLUDE_DAMPING 1
#define USE_DOUBLE 0
#define INCLUDE_AMPLITUDE 1
#define INCLUDE_OFFSET 1
#define INCLUDE_PHASE 1
#define INCLUDE_SINLOOKUPTABLE 1

#if USE_DOUBLE
typedef Type_FloatingPointDataType double;
#else
#define Type_FloatingPointDataType float
#endif // USE_DOUBLE

typedef struct Struct_Parameters_s {
  Type_FloatingPointDataType offset;
  Type_FloatingPointDataType amplitude;
  Type_FloatingPointDataType omega;
  Type_FloatingPointDataType samplingFrequency;
  Type_FloatingPointDataType phase;
  Type_FloatingPointDataType dampingFactor;
} Type_Parameters;

void SinusGeneratorInit(Type_FloatingPointDataType offset,
                        Type_FloatingPointDataType amplitude,
                        Type_FloatingPointDataType frequency,
                        Type_FloatingPointDataType samplingFrequency,
                        Type_FloatingPointDataType phase,
                        Type_FloatingPointDataType dampingFactor);

Type_FloatingPointDataType SinusGeneratorOneSample(void);

void SawtoothGeneratorInit(Type_FloatingPointDataType offset,
                           Type_FloatingPointDataType amplitude,
                           Type_FloatingPointDataType frequency,
                           Type_FloatingPointDataType samplingFrequency,
                           Type_FloatingPointDataType phase,
                           Type_FloatingPointDataType dampingFactor);

Type_FloatingPointDataType SawtoothGeneratorOneSample(void);

void RampGeneratorInit(Type_FloatingPointDataType offset,
                       Type_FloatingPointDataType slope,
                       Type_FloatingPointDataType samplingFrequency);

Type_FloatingPointDataType RampGeneratorOneSample(void);

void TriangleGeneratorInit(Type_FloatingPointDataType offset,
                           Type_FloatingPointDataType amplitude,
                           Type_FloatingPointDataType frequency,
                           Type_FloatingPointDataType samplingFrequency,
                           Type_FloatingPointDataType phase,
                           Type_FloatingPointDataType dampingFactor);

Type_FloatingPointDataType TriangleGeneratorOneSample(void);

void SquareGeneratorInit(Type_FloatingPointDataType dutyCycle,
                         Type_FloatingPointDataType offset,
                         Type_FloatingPointDataType amplitude,
                         Type_FloatingPointDataType frequency,
                         Type_FloatingPointDataType samplingFrequency,
                         Type_FloatingPointDataType phase,
                         Type_FloatingPointDataType dampingFactor);

Type_FloatingPointDataType SquareGeneratorOneSample(void);
#endif
