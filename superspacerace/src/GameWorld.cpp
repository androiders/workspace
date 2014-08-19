#include "GameWorld.h"
#include "GameManager.h"
#include <OGRE/Ogre.h>
#include <iostream>
#include <cstdlib>
#include "ResourceManager.h"

GameWorld::GameWorld( GameManager * gmngr )
{
    mSceneManager = gmngr->getGraphicsManager( )->getSceneManager( );
    mCamera = gmngr->getGraphicsManager()->getCamera( );
    mPhysics = gmngr->getPhysicsSystem( );
    mObjectMapper = new SceneNodeToObjectMapper( );

//    ResourceManager::getInstance( )->createTexture( "stars.jpg" );
    mSceneManager->setSkyBox( true, "skybox2" );
}

GameWorld::~GameWorld( )
{
}

void GameWorld::addTerrain( )
{
   // irr::video::IImage * hm = driver->createImageFromFile( "models/heightmap.bmp" );
    //irr::video::IImage * tex = driver->createImageFromFile( "models/texture.jpg" );

    //irr::scene::IAnimatedMesh * mesh = scenemgr->addTerrainMesh("terrain",tex,hm);
    // /*irr::scene::IAnimatedMeshSceneNode* node =*/ scenemgr->addAnimatedMeshSceneNode( mesh );

//    scenemgr->addLightSceneNode( 0, irr::core::vector3df( 0, 280, 0 ) );

//    /*irr::scene::ITerrainSceneNode * terr =*/ scenemgr->addTerrainSceneNode("models/heightmap.bmp",0,getNextNodeId( ),
//                                            irr::core::vector3df ( 0.0f, 0.0f, 0.0f ),
//                                            irr::core::vector3df ( 0.0f, 0.0f, 0.0f ),
//                                            irr::core::vector3df ( 100.0f, 2.0f, 100.0f ));
}


void GameWorld::createPlayer( )
{

      Ogre::Entity * ent       = ResourceManager::getInstance( )->createEntity("Fighter", "fighter.mesh" );

      Ogre::SceneNode *node = ResourceManager::getInstance()->createSceneNodeFromEntity( ent, "FighterNode" );
      //#ifdef DEBUG
      //node->setDebugDisplayEnabled( true );
      //#endif

    // if everything worked, add a texture and disable lighting
    if (node)
    {
        mPlayer = ResourceManager::getInstance()->createSpaceShip( node );

        mGameObjects.push_back( mPlayer );
        mPlayer->setName( "Space Ship" );
        mObjectMapper->registerObject(mPlayer, node );

    mCamHandler = new ShipCameraFollower( mCamera, mPlayer, 150.0f );
    mCamHandler->setSpeedFac( mPlayer->getMaxRotSpeed( ) );

    }


}

void GameWorld::fakeWorld( )
{
//    for( int i = 0; i < 1000; ++i )
//    {
//        irr::scene::IAnimatedMesh * mesh = scenemgr->addSphereMesh( "sphere", rand( ) % 50 + 10 );
//        irr::scene::IAnimatedMeshSceneNode* sphere = scenemgr->addAnimatedMeshSceneNode( mesh );
//        irr::core::vector3df pos( float( rand( ) % 10000 - 5000 ), float( rand( ) % 10000 - 5000 ), float( rand( ) % 10000 - 5000 ) );
//        sphere->setPosition( pos );
//    }
}

void GameWorld::addStaticObjects( )
{

//    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().load(
//            "_missing_material_", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::Entity * ent       = ResourceManager::getInstance( )->createEntity("Thorus", "Torus.006.mesh" );
//    ent->setMaterialName( "_missing_material" );

//    ent->setMaterial( material );
    Ogre::SceneNode *node = ResourceManager::getInstance()->createSceneNodeFromEntity( ent, "TorusNode" );
    node->setScale(3,3,3);

//    irr::scene::IAnimatedMesh * mesh = scenemgr->addSphereMesh( "sphere", 50.0 );
//    irr::scene::IAnimatedMeshSceneNode* sphere = scenemgr->addAnimatedMeshSceneNode( mesh );
//    irr::scene::ITriangleSelector * sel = scenemgr->createOctTreeTriangleSelector( mesh, sphere );
//    sphere->setTriangleSelector( sel );
//    sel->drop( );
//
//    if( sphere )
//    {
//        sphere->setID( getNextNodeId( ) );
//        refptr::RefPtr< GameObject > sphereo = new GameObject( sphere );
//        gameObjects.push_back( sphereo );
//        //refptr::RefPtr< PhysicsObject > po = new PhysicsObject( );
//        //sphereo->setPhysicsObject( po.pointer( ) );
//        //physics->addRigidBody( po->getRigidBody( ) );
//        sphereo->setName( "Sphereo" );
//        objectMapper->registerObject( sphereo.pointer( ), sphere );
//        #ifdef DEBUG
//         sphere->setDebugDataVisible( irr::scene::EDS_BBOX );
//        #endif
//
//        irr::scene::ISceneNodeAnimator * anim = scenemgr->createRotationAnimator( irr::core::vector3df( 0, 0, 0.1f ) );
//        sphere->addAnimator( anim );
//        anim->drop( );
//    }
//
//    mesh = scenemgr->getMesh( "models/staticmodels/barrel01.3ds");
//    irr::scene::IAnimatedMeshSceneNode * barrel = scenemgr->addAnimatedMeshSceneNode( mesh, sphere );
//    sel = scenemgr->createOctTreeTriangleSelector( mesh, barrel );
//    barrel->setTriangleSelector( sel );
//    sel->drop( );
//
//    if( barrel )
//    {
//        barrel->setID( getNextNodeId( ) );
//        barrel->setMaterialTexture(0, driver->getTexture("models/staticmodels/pavorb1.jpg"));
//        barrel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//        barrel->setScale( irr::core::vector3df( 0.2, 0.2, 0.2 ) );
//
//        #ifdef DEBUG
//        barrel->setDebugDataVisible( irr::scene::EDS_BBOX );
//        #endif
//
//        refptr::RefPtr< GameObject > barrelo = new GameObject( barrel );
//        gameObjects.push_back( barrelo );
//        barrelo->setPosition( 0, 50, 0 );
//        barrelo->setName( "Barrelo" );
//        objectMapper->registerObject( barrelo.pointer( ), barrel );
//    }

}

GameObject * GameWorld::getObjectFromNode( const Ogre::SceneNode * node )
{
    if( node == 0 )
        return 0;

    return mObjectMapper->getObject( node );
}

void GameWorld::update( float t )
{
    for( unsigned int i = 0; i < mGameObjects.size( ); i++)
        mGameObjects[i]->update( t );

   if( mCamHandler == 0 )
	   return;

    mCamHandler->update( t );


}
