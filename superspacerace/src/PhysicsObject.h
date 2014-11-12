#ifndef PHYSICSOBJECT_H_INCLUDED
#define PHYSICSOBJECT_H_INCLUDED
#include <bullet/btBulletDynamicsCommon.h>
//#include <refptr/Referenced.h>
#include <OGRE/Ogre.h>


class PhysicsObject //: public refptr::Referenced
{
    public:

        //creation should be handled by a factory. In maybe gamephysics class...
        PhysicsObject( );

        btRigidBody * getRigidBody( )
        { return fallRigidBody; }

        Ogre::Vector3 getPosition( );

    protected:

        ~PhysicsObject( );

        btCollisionShape* fallShape;

        btDefaultMotionState* fallMotionState;

        btRigidBody* fallRigidBody;
};


#endif // PHYSICSOBJECT_H_INCLUDED
