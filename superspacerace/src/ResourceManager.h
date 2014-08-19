#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

//#include <refptr/Referenced.h>
#include "GraphicsManager.h"
#include "SpaceShip.h"

/**
 * Singleton resource manager
 */

class ResourceManager //: public refptr::Referenced
{
   public:

      static ResourceManager * getInstance( );

      /**
       * TODO: Expand woth more parameters for texture properties
       */
      Ogre::MaterialPtr createTexture( const std::string & textureName );

      Ogre::Entity * createEntity( const std::string & pName, const std::string & pMeshName );

      Ogre::SceneNode * createSceneNodeFromEntity( //Ogre::Entity * pEntity,
                                                         Ogre::MovableObject * pEntity,
                                                         const std::string & pNodeName,
                                                         Ogre::SceneNode * pParent = 0 );
//      Ogre::SceneNode * createSceneNodeFromEntity( Ogre::Entity * pEntity,
//                                                   const std::string & pNodeName,
//                                                   Ogre::SceneNode * pParent = 0 );

//      Ogre::SceneNode * createSceneNode( const std::string & pMeshName,
//                                         const std::string & pTextureName,
//                                         gre::SceneNode * pParent = 0 );

      SpaceShip * createSpaceShip( Ogre::SceneNode * pNode );

      Ogre::ParticleSystem * createParticleSystem( const std::string & pName,
                                                        const std::string & pResourceName );


      void initialize( GraphicsManager * pRmngr );

      bool isInitialized( )
      { return mInitialized; }

   protected:

      ResourceManager( );

      ~ResourceManager( );

      unsigned int getNextNodeId( );


   private:

      bool mInitialized;

      unsigned int mNextNodeId;

      GraphicsManager * mGraphicsManager;

      static ResourceManager * theInstance;

};


#endif // RESOURCEMANAGER_H_INCLUDED
