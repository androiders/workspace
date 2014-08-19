#include "ObjectCameraFollower.h"
#include <iostream>

ShipCameraFollower::ShipCameraFollower( Ogre::Camera * pCam, SpaceShip * pObj, float pDistance, float pAbove )
{
    camera = pCam;

    mDistanceVector = GameObject::smOrigForward * -pDistance;
    mDistanceVector += GameObject::smOrigUp * pAbove;

    speedFac = 1.0;
    setObject( pObj );

    update( 1.0 );
}

ShipCameraFollower::~ShipCameraFollower()
{
    camera = 0;
    object = 0;
}

void ShipCameraFollower::setObject( SpaceShip * pObj )
{
    object = pObj;

    update( 1.0 );
//    Ogre::Vector3 lObjPos = object->getPosition();
//    camera->setPosition( lObjPos + mDistanceVector );
//    Ogre::Vector3 lCamPos = camera->getPosition();
//    Ogre::Vector3 lDir = lObjPos - lCamPos;
//    lDir.normalise();
//    camera->setDirection( lDir );
//    mBasicOrientation = camera->getOrientation();
//    camera->setOrientation( Ogre::Quaternion( ) );
}

void ShipCameraFollower::update( float time )
{
    if( object == 0 )
        return;

    align( time );
}

/**
 * Aligns the camera with the object
 * using the distence
 */
void ShipCameraFollower::align( float time )
{
    Ogre::Quaternion lObjTrans = object->getOrientation( );
    Ogre::Quaternion lCamTrans = camera->getOrientation( );

    Ogre::Quaternion lSlerp;
    lSlerp = lSlerp.Slerp(time * speedFac, lCamTrans, lObjTrans );
    camera->setOrientation( lSlerp );
    Ogre::Vector3 lPos = object->getPosition() + lSlerp * mDistanceVector;

    camera->setPosition( lPos );
}
