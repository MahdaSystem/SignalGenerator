#include "SignalGenerator.h"
#include "Sine.h"
#include <stdio.h>

static Type_Parameters SinusParameters;
static Type_FloatingPointDataType SinusTime = 0;
static uint32_t SinusSamplingIndex = 0;

static Type_Parameters SawtoothParameters;
static Type_FloatingPointDataType SawtoothTime = 0;
static uint32_t SawtoothOnePeriodSamplingIndex = 0;
static uint32_t SawtoothSamplingIndex = 0;

static Type_FloatingPointDataType RampOffset = 0;
static Type_FloatingPointDataType RampSlope = 0;
static Type_FloatingPointDataType RampSamplingFrequency = 0;
static uint32_t RampSamplingIndex = 0;
static Type_FloatingPointDataType RampTime = 0;

static Type_Parameters TriangleParameters;
static Type_FloatingPointDataType TriangleTime = 0;
static uint32_t TriangleOnePeriodSamplingIndex = 0;
static int8_t TriangleUpGoing = -1;
static uint32_t TriangleSamplingIndex = 0;

static Type_Parameters SquareParameters;
static Type_FloatingPointDataType SquareDutyCycle = 0;
static Type_FloatingPointDataType SquareTime = 0;
static uint32_t SquareOnePeriodSamplingIndex = 0;
static uint32_t SquareSamplingIndex = 0;

void SinusGeneratorInit(Type_FloatingPointDataType offset,
                        Type_FloatingPointDataType amplitude,
                        Type_FloatingPointDataType frequency,
                        Type_FloatingPointDataType samplingFrequency,
                        Type_FloatingPointDataType phase,
                        Type_FloatingPointDataType dampingFactor) {

  SinusTime = 0;
#if INCLUDE_PHASE
  SinusSamplingIndex = (phase / 6.28318530717958647692 * samplingFrequency / frequency);
#else
  SinusSamplingIndex = 0;
#endif
  SinusParameters.omega = 2 * 3.14159265358979323846 * frequency;
  SinusParameters.offset = offset;
  SinusParameters.amplitude = amplitude;
  SinusParameters.samplingFrequency = samplingFrequency;
  SinusParameters.phase = phase;
  SinusParameters.dampingFactor = dampingFactor;
};

Type_FloatingPointDataType SinusGeneratorOneSample(void) {
  SinusTime = SinusSamplingIndex / SinusParameters.samplingFrequency;
  SinusSamplingIndex++;
  return (
#if INCLUDE_OFFSET
      SinusParameters.offset +
#endif // INCLUDE_OFFSET
      (
#if INCLUDE_AMPLITUDE
          SinusParameters.amplitude *
#endif // INCLUDE_AMPLITUDE
#if INCLUDE_DAMPING
          exp(-1 * SinusParameters.dampingFactor * SinusTime) * /* Damp: */
#endif                                                          // INCLUDE_DAMPING
#if INCLUDE_SINLOOKUPTABLE
          sinus[((uint32_t)(((SinusParameters.omega * SinusTime)) * (Type_FloatingPointDataType)15915.49430918953357688837)) % 100000]));
#else  // INCLUDE_SINLOOKUPTABLE
          sin((SinusParameters.omega * SinusTime))));
#endif // INCLUDE_SINLOOKUPTABLE
};

void SawtoothGeneratorInit(Type_FloatingPointDataType offset,
                           Type_FloatingPointDataType amplitude,
                           Type_FloatingPointDataType frequency,
                           Type_FloatingPointDataType samplingFrequency,
                           Type_FloatingPointDataType phase,
                           Type_FloatingPointDataType dampingFactor) {

  SawtoothTime = 0;
#if INCLUDE_DAMPING
  SawtoothSamplingIndex = 0;
#endif
  SawtoothOnePeriodSamplingIndex = 0;
#if INCLUDE_PHASE
  SawtoothOnePeriodSamplingIndex = (phase / 6.28318530717958647692 * samplingFrequency / frequency);
#else
  SawtoothOnePeriodSamplingIndex = 0;
#endif
  SawtoothParameters.omega = 2 * frequency;
  SawtoothParameters.offset = offset;
  SawtoothParameters.amplitude = amplitude;
  SawtoothParameters.samplingFrequency = samplingFrequency;
  SawtoothParameters.phase = phase;
  SawtoothParameters.dampingFactor = dampingFactor;
};

Type_FloatingPointDataType SawtoothGeneratorOneSample(void) {
  SawtoothTime = SawtoothOnePeriodSamplingIndex / SawtoothParameters.samplingFrequency;
  SawtoothOnePeriodSamplingIndex++;
  if ((SawtoothOnePeriodSamplingIndex * SawtoothParameters.omega / SawtoothParameters.samplingFrequency) >= 2.0)
    SawtoothOnePeriodSamplingIndex = 0;
#if INCLUDE_DAMPING
  SawtoothSamplingIndex++;
#endif
  return (
#if INCLUDE_OFFSET
      SawtoothParameters.offset +
#endif // INCLUDE_OFFSET
      (
#if INCLUDE_AMPLITUDE
          SawtoothParameters.amplitude *
#endif // INCLUDE_AMPLITUDE
#if INCLUDE_DAMPING
          /* Damp: */ exp(-1 * SawtoothParameters.dampingFactor * SawtoothSamplingIndex / SawtoothParameters.samplingFrequency) *
#endif // INCLUDE_DAMPING
          ((SawtoothParameters.omega * SawtoothTime) - 1)));
};

void RampGeneratorInit(Type_FloatingPointDataType offset,
                       Type_FloatingPointDataType slope,
                       Type_FloatingPointDataType samplingFrequency) {
  RampTime = 0;
  RampSamplingIndex = 0;
  RampOffset = offset;
  RampSlope = slope;
  RampSamplingFrequency = samplingFrequency;
};

Type_FloatingPointDataType RampGeneratorOneSample(void) {
  RampTime = RampSamplingIndex / RampSamplingFrequency;
  RampSamplingIndex++;
  return (
#if INCLUDE_OFFSET
      RampOffset +
#endif
      (RampTime * RampSlope));
};

void TriangleGeneratorInit(Type_FloatingPointDataType offset,
                           Type_FloatingPointDataType amplitude,
                           Type_FloatingPointDataType frequency,
                           Type_FloatingPointDataType samplingFrequency,
                           Type_FloatingPointDataType phase,
                           Type_FloatingPointDataType dampingFactor) {
  TriangleTime = 0;
#if INCLUDE_DAMPING
  SawtoothSamplingIndex = 0;
#endif
#if INCLUDE_PHASE
  if (phase != 0) {
    TriangleOnePeriodSamplingIndex = ((((Type_FloatingPointDataType)((uint16_t)(phase / 6.28318530717958647692 * 10000))) / 10000) < 0.5) ? ((phase / 6.28318530717958647692) * samplingFrequency / frequency) : ((phase / 6.28318530717958647692 - 0.5) * samplingFrequency / frequency);
    if (TriangleOnePeriodSamplingIndex == 0)
      TriangleUpGoing = ((((Type_FloatingPointDataType)((uint16_t)(phase / 6.28318530717958647692 * 10000))) / 10000) < 0.5) ? (1) : (0);
    else
      TriangleUpGoing = ((((Type_FloatingPointDataType)((uint16_t)(phase / 6.28318530717958647692 * 10000))) / 10000) < 0.5) ? (1) : (-1);
  } else
    TriangleOnePeriodSamplingIndex = 0;
#else
  TriangleOnePeriodSamplingIndex = 0;
#endif
  TriangleParameters.omega = 4 * frequency;
  TriangleParameters.offset = offset;
  TriangleParameters.amplitude = amplitude;
  TriangleParameters.samplingFrequency = samplingFrequency;
  TriangleParameters.phase = phase;
  TriangleParameters.dampingFactor = dampingFactor;
  // printf("%.20f\n%d\n%d\n",phase / 6.28318530717958647692,TriangleOnePeriodSamplingIndex,TriangleUpGoing);
}

Type_FloatingPointDataType TriangleGeneratorOneSample(void) {
  TriangleTime = TriangleOnePeriodSamplingIndex / TriangleParameters.samplingFrequency;
  if (TriangleOnePeriodSamplingIndex == 0)
    TriangleUpGoing = (TriangleUpGoing == -1) ? (1) : (-1);
  TriangleOnePeriodSamplingIndex++;
  if ((TriangleOnePeriodSamplingIndex * TriangleParameters.omega / TriangleParameters.samplingFrequency) >= 2.0) {
    TriangleOnePeriodSamplingIndex = 0;
  }

#if INCLUDE_DAMPING
  TriangleSamplingIndex++;
#endif
  return (
#if INCLUDE_OFFSET
      TriangleParameters.offset +
#endif // INCLUDE_OFFSET
      (
#if INCLUDE_AMPLITUDE
          TriangleParameters.amplitude *
#endif // INCLUDE_AMPLITUDE
#if INCLUDE_DAMPING
          /* Damp: */ exp(-1 * TriangleParameters.dampingFactor * TriangleSamplingIndex / TriangleParameters.samplingFrequency) *
#endif // INCLUDE_DAMPING
          ((TriangleParameters.omega * TriangleTime) - 1) * TriangleUpGoing));
}

void SquareGeneratorInit(Type_FloatingPointDataType dutyCycle,
                         Type_FloatingPointDataType offset,
                         Type_FloatingPointDataType amplitude,
                         Type_FloatingPointDataType frequency,
                         Type_FloatingPointDataType samplingFrequency,
                         Type_FloatingPointDataType phase,
                         Type_FloatingPointDataType dampingFactor) {
  SquareDutyCycle = dutyCycle;
  SquareTime = 0;
#if INCLUDE_DAMPING
  SawtoothSamplingIndex = 0;
#endif
#if INCLUDE_PHASE
  SquareOnePeriodSamplingIndex = (uint32_t)(phase / 6.28318530717958647692 * samplingFrequency / frequency);
#else
  SquareOnePeriodSamplingIndex = 0;
#endif
  SquareParameters.omega = frequency;
  SquareParameters.offset = offset;
  SquareParameters.amplitude = amplitude;
  SquareParameters.samplingFrequency = samplingFrequency;
  SquareParameters.phase = phase;
  SquareParameters.dampingFactor = dampingFactor;
};

Type_FloatingPointDataType SquareGeneratorOneSample(void) {
  SquareTime = SquareOnePeriodSamplingIndex / SquareParameters.samplingFrequency;
  SquareOnePeriodSamplingIndex++;
  if ((SquareOnePeriodSamplingIndex * SquareParameters.omega / SquareParameters.samplingFrequency) >= 1.0) {
    SquareOnePeriodSamplingIndex = 0;
  }

#if INCLUDE_DAMPING
  SquareSamplingIndex++;
#endif
  return (
#if INCLUDE_OFFSET
      SquareParameters.offset +
#endif // INCLUDE_OFFSET
      (
#if INCLUDE_AMPLITUDE
          SquareParameters.amplitude *
#endif // INCLUDE_AMPLITUDE
#if INCLUDE_DAMPING
          /* Damp: */ exp(-1 * SquareParameters.dampingFactor * SquareSamplingIndex / SquareParameters.samplingFrequency) *
#endif // INCLUDE_DAMPING
          (((SquareParameters.omega * SquareTime) < (SquareDutyCycle / 100)) ? (1) : (-1))));
};
