#include "SpaceShip.h"
#include <iostream>
#include "ResourceManager.h"

SpaceShip::SpaceShip( Ogre::SceneNode * pNode ) :
    GameObject( pNode )
{
    //mForward = Ogre::Vector3( 0, 0, -1.0 );
    //mRight = Ogre::Vector3( 1.0, 0, 0 );

    mMaxSpeed = 10;
    mMaxRotSpeed = 5.0f;
    //mMaxPitchSpeed = 10.0;
    //mMaxRollSpeed = 10.0;
    mMaxRollAng = Ogre::Math::PI / 2.0;
    mCurrRollAng = 0;
    mCurrSpeed = 0;
    mRolling = false;
    mAccelerating = false;
    mAcceleration = 1.0;

    mEngine1Particles = ResourceManager::getInstance( )->createParticleSystem( "engine1", "ShipEngine" );
     Ogre::SceneNode * lEn1 = ResourceManager::getInstance( )->createSceneNodeFromEntity( mEngine1Particles, "Engine1",
             pNode );
     mEngine1Particles->setKeepParticlesInLocalSpace( true );
     mEngine2Particles = ResourceManager::getInstance( )->createParticleSystem( "engine2", "ShipEngine" );
     Ogre::SceneNode * lEn2 = ResourceManager::getInstance( )->createSceneNodeFromEntity( mEngine2Particles, "Engine2",
             pNode );
     mEngine2Particles->setKeepParticlesInLocalSpace( true );

     lEn1->setPosition( -7, -1, 15 );
     lEn2->setPosition( 7, -1, 15 );
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::update( float t )
{
    float lTmpSpeed = 0;
    if(mAccelerating)
    {
        lTmpSpeed = mCurrSpeed + t * mAcceleration;
        mCurrSpeed = lTmpSpeed > mMaxSpeed ? mMaxSpeed : lTmpSpeed;
    }
    else
    {
        lTmpSpeed = mCurrSpeed - t * mAcceleration/2.0;
        mCurrSpeed = lTmpSpeed < 0 ? 0 : lTmpSpeed;
    }

    Ogre::Vector3 lGasDir = smOrigForward;
    float thrust = -mCurrSpeed/mMaxSpeed;
    mEngine1Particles->getEmitter( 0 )->setDirection( lGasDir * thrust );
    mEngine2Particles->getEmitter( 0 )->setDirection( lGasDir * thrust );


    static float lOldRollAng = 0;
    Ogre::Vector3 lForward = getDirection();

    float lRollAng = 0;

    if( isRolling( ) )
        lRollAng = mRollSpeed * t;
    else
        lRollAng = mCurrRollAng - lOldRollAng;

    lOldRollAng = mCurrRollAng;
    Ogre::Quaternion lRoll = Ogre::Quaternion( Ogre::Radian( lRollAng ), lForward );
    Ogre::Quaternion lPitch = Ogre::Quaternion( Ogre::Radian( mPitchSpeed * t ), smOrigRight );

    rotate( lPitch );
    setOrientation( lRoll * getOrientation( ) );

    lForward = getDirection();
    move( lForward * mCurrSpeed );
}
