#include "GameManager.h"
#include "UpdateFrameListener.h"
#include <iostream>

GameManager::GameManager( )
{
    running = false;
}

GameManager::~GameManager( )
{
    //delete device;
    //delete driver;
    //delete scenemgr;
	delete world;
	delete inputManager;
	delete graphicsManager;
#ifdef DEBUG
  std::cout << "destroyed game manager " << std::endl;
#endif

}

void GameManager::initializeGame( )
{
    //setupVideo( );
    graphicsManager = new GraphicsManager( 640, 480 );
    ResourceManager::getInstance()->initialize( graphicsManager );
    //pickSystem = new PickSystem( this );
    inputManager = new InputManager( this );
    //physicsSystem = new GamePhysics( );

    //graphicsManager->setupVideo( );
    //createPlayer( );
    world = new GameWorld( this );
    //world->addTerrain( );
    world->createPlayer( );
    world->addStaticObjects();
    //world->fakeWorld( );

   //enable the input frame listener
    graphicsManager->getRoot( )->addFrameListener( inputManager );
    graphicsManager->getRoot( )->addFrameListener( new UpdateFrameListener( this ) );

    //check return values and show dialog
    inputManager->initJoystick();
    inputManager->initKeyboard();

}

void GameManager::runGame( )
{
   running = true;

   ShipJoystickController *js = new ShipJoystickController( world->getPlayer( ) ); //really set up somwhere else
   inputManager->setJoystickHandler( js );


//int cnt = 0;

   graphicsManager->startRenderLoop( );

    // draw everything
//    while(graphicsManager->update( ) && cnt < 10000 )
//    {

//InputManager:://        float time = graphicsManager->getFrameTime( );
//        inputManager->getInput( );
//        physicsSystem->update( time ); //consider moving physics to game world!
//        world->update( time );
//cnt++;
//    }

}

void GameManager::updateWorld( float time )
{
   world->update( time );
}


void GameManager::endGame( )
{
    running = false;

}
