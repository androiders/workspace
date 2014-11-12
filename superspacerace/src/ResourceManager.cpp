#include "ResourceManager.h"
//#include <Ogre/Ogre.h>
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>

ResourceManager * ResourceManager::theInstance = 0;

ResourceManager * ResourceManager::getInstance( )
{
   if( !theInstance )
      theInstance = new ResourceManager( );

   return theInstance;
}

ResourceManager::ResourceManager( )
{
   mInitialized = false;
   //initialize( );
}

ResourceManager::~ResourceManager( )
{
}

void ResourceManager::initialize( GraphicsManager * pGmngr )
{


   mGraphicsManager = pGmngr;

   Ogre::ConfigFile cf;

   cf.load("Resources.cfg");
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
    Ogre::String secName = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
    for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin();
          i != settings->end(); ++i)
      {
        Ogre::String typeName = i->first;
        Ogre::String archName = i->second;
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
          archName, typeName, secName);
      }
    }
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);



    Ogre::OverlayManager & om = Ogre::OverlayManager::getSingleton();
    Ogre::Overlay* thisOverlay = om.getByName("nojoystick");
    thisOverlay->show();

//    = static_cast<Ogre::Overlay*>(Ogre::OverlayManager::getSingletonPtr()->getByName("NoJoystick"));

    mNextNodeId = -1;
   mInitialized = true;
}

unsigned int ResourceManager::getNextNodeId( )
{
   return ++mNextNodeId;
}

Ogre::MaterialPtr ResourceManager::createTexture( const std::string & pTextureName )
{
       Ogre::TexturePtr shipTex =
       Ogre::TextureManager::getSingleton( ).load( pTextureName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
       Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
       pTextureName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

      material->getTechnique(0)->getPass(0)->createTextureUnitState(pTextureName);
      //material->getTechnique(0)->getPass(0)->setLightingEnabled(true);
      //material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

      return material;
}

Ogre::Entity * ResourceManager::createEntity( const std::string & pName, const std::string & pMeshName )
{
   return mGraphicsManager->getSceneManager( )->createEntity( pName, pMeshName );
}

Ogre::SceneNode * ResourceManager::createSceneNodeFromEntity( //Ogre::Entity * pEntity,
        Ogre::MovableObject * pEntity, const std::string & pNodeName, Ogre::SceneNode * pParent )
{
    Ogre::SceneNode * lParent = pParent;
    if( lParent == 0 )
        lParent = mGraphicsManager->getSceneManager( )->getRootSceneNode( );

    Ogre::SceneNode * lNode = lParent->createChildSceneNode( pNodeName );
    lNode->attachObject( pEntity );
    lNode->_updateBounds( );

    unsigned int nodeId = getNextNodeId( );
    Ogre::Any id( nodeId );
    //lNode->setUserAny( id );

    return lNode;
}

//Ogre::SceneNode * ResourceManager::createSceneNodeFromEntity( Ogre::Entity * pEntity,
//                                                            const std::string & pNodeName,
//                                                            Ogre::SceneNode * pParent )
//{
//   Ogre::SceneNode * lParent = pParent;
//   if( lParent == 0 )
//      lParent = mGraphicsManager->getSceneManager( )->getRootSceneNode();
//
//   Ogre::SceneNode * lNode = lParent->createChildSceneNode( pNodeName );
//   lNode->attachObject( pEntity );
//
//   unsigned int nodeId = getNextNodeId();
//   Ogre::Any id( nodeId );
//   //lNode->setUserAny( id );
//
//   return lNode;
//}

SpaceShip * ResourceManager::createSpaceShip( Ogre::SceneNode * pNode )
{
   return new SpaceShip( pNode );
}

Ogre::ParticleSystem * ResourceManager::createParticleSystem( const std::string & pName,
        const std::string & pResourceName )
{
    return mGraphicsManager->getSceneManager( )->createParticleSystem( pName,
            pResourceName );
}

//Ogre::ScebneNode * ResourceManager::createSceneNode( const std::string & pMeshName,
//                                                     const std::string & pTextureName )
//{
//}

