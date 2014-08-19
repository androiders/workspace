#include "GamePhysics.h"

GamePhysics::GamePhysics( )
{
    init( );
}

GamePhysics::~GamePhysics( )
{
        // Clean up behind ourselves like good little programmers
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;

}

void GamePhysics::init( )
{
     // Build the broadphase
    maxProxies = 1024;
    btVector3 worldAabbMin(-10000,-10000,-10000);
    btVector3 worldAabbMax(10000,10000,10000);
    broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);

    // Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    // The actual physics solver
    solver = new btSequentialImpulseConstraintSolver;

    // The world.
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-10,0));


    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);

//    btCollisionShape* fallShape = new btSphereShape(1);


    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);


//    btDefaultMotionState* fallMotionState =
//            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
//    btScalar mass = 1;
//    btVector3 fallInertia(0,0,0);
//    fallShape->calculateLocalInertia(mass,fallInertia);
//    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
//    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
//    dynamicsWorld->addRigidBody(fallRigidBody);


}

void GamePhysics::update( float time )
{
    dynamicsWorld->stepSimulation(1/60.f,10);
}

void GamePhysics::addRigidBody( btRigidBody * body )
{
    dynamicsWorld->addRigidBody( body );
}

