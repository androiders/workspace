#ifndef GAMEPHYSICS_H_INCLUDED
#define GAMEPHYSICS_H_INCLUDED

#include <bullet/btBulletDynamicsCommon.h>
//#include <refptr/Referenced.h>

class GamePhysics //: public refptr::Referenced
{
    public:
        GamePhysics( );

        void init( );

        void update( float time );

        void addRigidBody( btRigidBody * body );

        ~GamePhysics( );

    protected:


        int maxProxies;

        btAxisSweep3* broadphase;

        btDefaultCollisionConfiguration* collisionConfiguration;

        btCollisionDispatcher* dispatcher;

        btSequentialImpulseConstraintSolver* solver;

        btDiscreteDynamicsWorld* dynamicsWorld;
};


#endif // GAMEPHYSICS_H_INCLUDED
