#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "GameObject.h"
#include <OGRE/Ogre.h>
//#include <refptr/Referenced.h>
//#include <refptr/RefPtr.h>
#include "StaticGameObject.h"
#include "DynamicGameObject.h"
#include <vector>
#include "SceneNodeToObjectMapper.h"
#include "GamePhysics.h"
#include "SpaceShip.h"
#include "ObjectCameraFollower.h"

class GameManager;

class GameWorld //: public refptr::Referenced
{
    public:

        GameWorld( GameManager * gmngr );

        virtual ~GameWorld( );

        void createPlayer( );

        void addStaticObjects( );

        void fakeWorld( );

        void addTerrain( );

//        GameObject * getObjectFromNode( const irr::scene::ISceneNode * node );

        GameObject * getObjectFromNode( const Ogre::SceneNode * node );

        void update( float t );

        SpaceShip * getPlayer( )
        { return mPlayer; }

    protected:


//        int getNextNodeId( );

        /**
         *No ownership, dont delete in constructor
         */
//        irr::scene::ISceneManager * scenemgr;
         Ogre::SceneManager * mSceneManager;

        /**
         *No ownership, dont delete in destructor
         */
//        irr::video::IVideoDriver* driver;

        GamePhysics * mPhysics;

        /**
         * world owns all objects.
         */
        //std::vector<refptr::RefPtr< StaticGameObject > >  staticGameObjects;

//        std::vector<refptr::RefPtr< DynamicGameObject > > dynamicGameObjects;

        std::vector< GameObject * > mGameObjects;

        SceneNodeToObjectMapper * mObjectMapper;

      Ogre::Camera * mCamera;

//        irr::scene::ICameraSceneNode * camera;

        SpaceShip * mPlayer;

        ShipCameraFollower * mCamHandler;

//        int mSceneNodeIdCnt;
};


#endif // WORLD_H_INCLUDED
