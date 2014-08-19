#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

//#include <refptr/Referenced.h>
//#include <refptr/RefPtr.h>
#include "GameObject.h"
#include "GameWorld.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "PickSystem.h"
//#include "GamePhysics.h"
#include "ResourceManager.h"
#include <vector>

class GameManager //: public refptr::Referenced
{
    public:

        GameManager( );

        void initializeGame( );

        void runGame( );

        void endGame( );

        void updateWorld( float time );

//        const InputManager * getInputManager( ) const
//        { return inputManager.pointer( ); }
//
//        InputManager * getInputManager( )
//        { return inputManager.pointer( ); }

        const GraphicsManager * getGraphicsManager( ) const
        { return graphicsManager; }

        GraphicsManager * getGraphicsManager( )
        { return graphicsManager; }

        PickSystem * getPickSystem( )
        { return pickSystem; }

        const PickSystem * getPickSystem( ) const
        { return pickSystem; }

        GamePhysics * getPhysicsSystem( )
        { return physicsSystem; }

        ~GameManager( );

    private:

        bool running;

        GameWorld * world;

        InputManager * inputManager;

        GraphicsManager * graphicsManager;

        ResourceManager * resourceManager;

        PickSystem * pickSystem;

        GamePhysics * physicsSystem;
};


#endif // GAMEMANAGER_H_INCLUDED
