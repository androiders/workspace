#include "PhysicsObject.h"

PhysicsObject::PhysicsObject( )
{
    fallShape = new btSphereShape( 10 );

    btDefaultMotionState* fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
    fallRigidBody = new btRigidBody(fallRigidBodyCI);
    //dynamicsWorld->addRigidBody(fallRigidBody);
}

PhysicsObject::~PhysicsObject( )
{
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;
    delete fallShape;
}

Ogre::Vector3 PhysicsObject::getPosition( )
{

    btTransform trans;
    fallRigidBody->getMotionState()->getWorldTransform(trans);
    Ogre::Vector3 vec( trans.getOrigin().getX( ),
                     trans.getOrigin().getY( ),
                     trans.getOrigin().getZ( ) );

    return vec;
}
