/*
 * mash.h
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */

#ifndef MASH_H_
#define MASH_H_

#define MAX_NR_OF_BREAKS 10

enum
{
	LinearTemp,
	SingleInfusione,
	MultiStepInfusion
} MashType;

typedef struct _mashProfile
{
	MashType type;
	uint8_t nrOfBreaks;
	uint8_t breakTimes[MAX_NR_OF_BREAKS];
	uint8_t breakTemps[MAX_NR_OF_BREAKS];
	uint8_t totalMashTime;
} MashProfile;




//private functions

uint8_t setNumberOfMashBreaks(MashProfile * profile);

void setMashTimesLoop(MashProfile * profile);

void setMashTempsLoop(MashProfile * profile);

//TODO: implement
void setMashType(MashProfile * profile);

uint8_t setMashTimeLoop();

uint8_t setMashTempLoop();

#endif /* MASH_H_ */
