/*
 * RaceTarget.h
 *
 *  Created on: 2 dec 2012
 *      Author: androiders
 */

#ifndef RACETARGET_H_
#define RACETARGET_H_

#include "GameObject.h"

class RaceTarget: public GameObject
{
    public:
        RaceTarget(Ogre::SceneNode * pNode);
        virtual ~RaceTarget();
};

#endif /* RACETARGET_H_ */
