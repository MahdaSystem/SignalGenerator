#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SignalGenerator.h"

int main(void) {
  FILE * fp;
  Type_FloatingPointDataType *samples = malloc(10000 * sizeof(Type_FloatingPointDataType));

  // Begin First Program (Waveforms seprately) 
  uint32_t myNumberOfSamples = 10000;
  fp = fopen("Sawtooth.txt", "w+");
  SawtoothGeneratorInit(0, 10, 5, 10000, 4.71238898038468985769, 0);
	for (uint32_t Counter = 0; Counter < myNumberOfSamples ; Counter++)
        fprintf(fp,"%f\n",SawtoothGeneratorOneSample());
	fclose(fp);
	printf("Sawtooth Finished!!!\n");

  fp = fopen("Sinus.txt", "w+");
  SinusGeneratorInit(10, 10, 10, 10000, 3.14159265358979323846, 1);
  for (uint32_t sampleIndex = 0; sampleIndex < (myNumberOfSamples * 2); sampleIndex++)
    fprintf(fp, "%lf\n", SinusGeneratorOneSample());
  fclose(fp);
  printf("Sinus Finished!\n");

  fp = fopen("Ramp.txt", "w+");
  RampGeneratorInit(5, 5, 10000);
  for (uint32_t sampleIndex = 0; sampleIndex < myNumberOfSamples; sampleIndex++)
    fprintf(fp, "%lf\n", RampGeneratorOneSample());
  fclose(fp);
  printf("Ramp Finished!\n");

  fp = fopen("Triangle.txt", "w+");
  TriangleGeneratorInit(5, 10, 5, 10000, 0, 0);
  for (uint32_t sampleIndex = 0; sampleIndex < myNumberOfSamples; sampleIndex++)
    fprintf(fp, "%lf\n", TriangleGeneratorOneSample());
  fclose(fp);
  printf("Triangle Finished!\n");

  fp = fopen("Square.txt", "w+");
  SquareGeneratorInit(35,0, 5, 10, 10000, 1.57079632679489661923, 0);
  for (uint32_t sampleIndex = 0; sampleIndex < myNumberOfSamples; sampleIndex++)
    fprintf(fp, "%lf\n", SquareGeneratorOneSample());
  fclose(fp);
  printf("Square Finished!\n");
  // End of First Program (Waveforms seprately) 

  // Begin Second Program (Waveforms together) 
  Type_FloatingPointDataType LastSample = 0;
  fp = fopen("Software.txt", "w+");
  SawtoothGeneratorInit(0, 10, 50, 10000, 0, 0);
	for (uint32_t Counter = 0; Counter < 2000 ; Counter++) {
        LastSample = SawtoothGeneratorOneSample();
        fprintf(fp,"%f\n",LastSample);
  }
  SinusGeneratorInit(LastSample, 3, 20, 10000, 0, 0);
  for (uint32_t Counter = 0; Counter < 2000 ; Counter++) {
        LastSample = SinusGeneratorOneSample();
        fprintf(fp,"%f\n",LastSample);
  }
  RampGeneratorInit(LastSample, 10, 10000);
  for (uint32_t Counter = 0; Counter < 2000 ; Counter++) {
        LastSample = RampGeneratorOneSample();
        fprintf(fp,"%f\n",LastSample);
  }
  SquareGeneratorInit(70,LastSample, 5, 20, 10000, 0, 0);
  for (uint32_t Counter = 0; Counter < 2000 ; Counter++) {
        LastSample = SquareGeneratorOneSample();
        fprintf(fp,"%f\n",LastSample);
  }
  TriangleGeneratorInit(LastSample, 7, 50, 10000, 0, 0);
  for (uint32_t Counter = 0; Counter < 2000 ; Counter++) {
        LastSample = TriangleGeneratorOneSample();
        fprintf(fp,"%f\n",LastSample);
  }
	fclose(fp);
	printf("Finished!!!\n");  
  // End of Second Program (Waveforms together) 

  free(samples);
  while (1)
    ;
}
