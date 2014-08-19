#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

//#include <refptr/Referenced.h>
//#include <refptr/RefPtr.h>
#include <OGRE/Ogre.h>
#include <string>
#include "PhysicsObject.h"

class GameObject //: public refptr::Referenced
{
    public:

        static const Ogre::Vector3 smOrigForward;

        static const Ogre::Vector3 smOrigRight;

        static const Ogre::Vector3 smOrigUp;

        GameObject( Ogre::SceneNode * pNode );

        virtual ~GameObject();


        void move( float x, float y, float z );

        void move( const Ogre::Vector3 & pTrans );

        void setPosition( float x, float y, float z );

        void setPosition( const Ogre::Vector3 & pPos );

        //void setPosition( const Vec3::Vec3f & pos );

        void setOrientation( const Ogre::Quaternion & pPos );

        void rotate( const Ogre::Quaternion & pRot );

        const Ogre::Vector3 getPosition() const;

        const Ogre::Quaternion & getOrientation() const;

        //    void setAnimationRange(int pStart, int pEnd );

        Ogre::Vector3 getDirection( ) const
        {
            return getOrientation() * smOrigForward;
        }

        Ogre::SceneNode * getNode()
        {
            return mNode;
        }

        //virtual irr::scene::ISceneNode * getNodeBase( ) = 0;

        void setName( const std::string & pName );

        const std::string & getName() const;

        virtual void update( float t );

        void setPhysicsObject( PhysicsObject * po )
        {
            mPhysObj = po;
        }

        PhysicsObject * getPhysicsObject()
        {
            return mPhysObj;
        }

        //  protected:



    private:

        Ogre::SceneNode * mNode;

        PhysicsObject * mPhysObj;

        std::string mName;
};

#endif // GAMEOBJECT_H_INCLUDED
