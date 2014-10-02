/*
 * mash.h
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */

#ifndef MASH_H_
#define MASH_H_

#define MAX_NR_OF_BREAKS 10

typedef enum
{
	LinearTemp,
	SingleInfusion,
	MultiStepInfusion
} MashType;

typedef struct _mashProfile
{
	MashType type;
	uint8_t nrOfBreaks;
	uint8_t breakTimes[MAX_NR_OF_BREAKS];
	uint8_t breakTemps[MAX_NR_OF_BREAKS];
	uint8_t totalMashTime;
	uint8_t linearStartTemp;
	uint8_t linearStopTemp;
	BOOL useMashOut;
} MashProfile;


BOOL setupMash(MashProfile * profile);

//private functions

void setNumberOfMashBreaks(MashProfile * profile);

void setMashType(MashProfile * profile);

void setMashTimesLoop(MashProfile * profile);

void setMashTempsLoop(MashProfile * profile);

void setMashLinearStartTemp(MashProfile * profile);

void setMashLinearStopTemp(MashProfile * profile);

void setMashTimeLoop(MashProfile * profile, uint8_t index);

void setMashTempLoop(MashProfile * profile, uint8_t index);

void setUseMashOut(MashProfile * profile);

//print lcd functions
void printMashType(uint8_t x, uint8_t y, MashType type);

void printUseMashOut(uint8_t yesorno);



#endif /* MASH_H_ */
