#ifndef PICKSYSTEM_H_INCLUDED
#define PICKSYSTEM_H_INCLUDED

#include <OGRE/Ogre.h>
//#include <refptr/Referenced.h>
#include <vector>


class GameManager;


/**
 * ray based picking system to be used on scene nodes
 * which has a triangle selector set. Other nodes will
 * not be able to be picked. BBs are tested for fast rejection
 */
class PickSystem //: public refptr::Referenced
{
    public:

        PickSystem( GameManager * gmngr );

        std::vector< Ogre::SceneNode* > & getPickedNodes( );

        /**
         * Makes a picking run and find all objects that
         * collides with the ray from screen coords x, y
         */
        void pick( int x, int y );

        /**
         * returns the scene node closest to camera
         * from the ray starting att screen coords x y
         */
        Ogre::SceneNode * getClosestNode( int x, int y );

//        irr::scene::ISceneCollisionManager * getCollisionManager( )
//        { return collisionManager; }

    protected:

        ~PickSystem( );

        void pick( const Ogre::SceneNode * root,  const Ogre::Ray & ray );

//        irr::scene::ISceneCollisionManager * collisionManager;

        Ogre::SceneManager * sceneManager;

        std::vector< Ogre::SceneNode* > pickedNodes;
};


#endif // PICKSYSTEM_H_INCLUDED
