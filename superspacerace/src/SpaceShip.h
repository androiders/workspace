#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "GameObject.h"

class SpaceShip: public GameObject
{
    public:

        SpaceShip( Ogre::SceneNode * pNode );

        virtual ~SpaceShip();

        virtual void update( float t );

        bool getRolling() const
        {
            return mRolling;
        }

        void setRolling( bool pRolling )
        {
            mRolling = pRolling;
        }

        bool isRolling() const
        {
            return mRolling;
        }

        void setCurrSpeed( float cs )
        {
            mCurrSpeed = std::min<float>( cs, mMaxSpeed );
        }

        void accelerate( bool accelerate )
        {
            mAccelerating = accelerate;
        }

        bool isAccelerating() const
        {
            return mAccelerating;
        }

        float getMaxSpeed() const
        {
            return mMaxSpeed;
        }

        float getMaxRotSpeed( ) const
        {
            return mMaxRotSpeed;
        }

        void setCurrPitchSpeedFraction( float frac )
        {
            mPitchSpeed = std::min<float>( frac * mMaxRotSpeed, mMaxRotSpeed );
        }

        float getMaxRollAng() const
        {
            return mMaxRollAng;
        }

        void setCurrRollFrac( float pFrac )
        {
            mCurrRollAng = std::min<float>( pFrac * mMaxRollAng, mMaxRollAng );
            mRollSpeed = std::min<float>( pFrac * mMaxRotSpeed, mMaxRotSpeed );
        }

        float getRollAng( ) const
        {
            return mRollSpeed;
        }

    private:

        float mPitchSpeed;

//        float mMaxPitchSpeed;

//        float mMaxRollSpeed;

        float mMaxRotSpeed;

        float mMaxRollAng;

        float mCurrRollAng;

        float mRollSpeed;

        float mMaxSpeed;

        float mCurrSpeed;

        float mAcceleration;

        //Ogre::Vector3 mForward, mRight;

        bool mRolling;

        bool mAccelerating;

        Ogre::ParticleSystem * mEngine1Particles;

        Ogre::ParticleSystem * mEngine2Particles;

        Ogre::ParticleSystem * mPlasmaCanonParticleSystem;
};

#endif // SPACESHIP_H_INCLUDED
