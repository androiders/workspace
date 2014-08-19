#ifndef OBJECTCAMERAFOLLOWER_H_INCLUDED
#define OBJECTCAMERAFOLLOWER_H_INCLUDED

#include <OGRE/Ogre.h>
//#include <refptr/Referenced.h>
#include "SpaceShip.h"

class ShipCameraFollower //: public refptr::Referenced
{
    public:

        ShipCameraFollower( Ogre::Camera * pCam, SpaceShip * pObj, float pBehind = 30.0f, float pAbove = 20.0f );

        void update( float time );

        void setObject( SpaceShip * pObj );

        virtual ~ShipCameraFollower( );

        void setSpeedFac( float pFac )
        {
            speedFac = pFac;
        }

    private:

        void align( float time );

        Ogre::Camera * camera;

        SpaceShip * object;

        /**
         * distance between camera and object
         */
        Ogre::Vector3 mDistanceVector;

        float speedFac;

        Ogre::Quaternion mBasicOrientation;

        //Ogre::Vector3 dir;

};


#endif // OBJECTCAMERAFOLLOWER_H_INCLUDED
