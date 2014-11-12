#include "GraphicsManager.h"
#include <iostream>
#include <OGRE/Overlay/OgreOverlaySystem.h>

GraphicsManager::GraphicsManager( int resx, int resy, int bpp )
{
   frameTime = 0;
   currentFPS = 0;
   prevTime = 0;
   setupVideo( resx, resy, bpp );
}

GraphicsManager::~GraphicsManager( )
{
   delete mRoot;
#ifdef DEBUG
   std::cout << "destroyed graphics manager" << std::endl;
#endif
}

void GraphicsManager::setupVideo( int xres, int yres, int bpp )
{
      // start up the engine
      mRoot = new Ogre::Root();

//      if(!mRoot->restoreConfig() && mRoot->showConfigDialog())
//          throw Ogre::Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");
//      mRoot->showConfigDialog();
      Ogre::RenderSystem *rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
                                            // or use "OpenGL Rendering Subsystem"
      mRoot->setRenderSystem(rs);
//        rs->setConfigOption("Full Screen", "Yes");
      rs->setConfigOption("Full Screen", "No");
      rs->setConfigOption("Video Mode", "1280 x 960 @ 32-bit colour");


      mRenderWindow = mRoot->initialise(true, "Super Space Race");

      mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default SceneManager");
      mCamera = mSceneManager->createCamera("Camera");
      mCamera->setPosition(Ogre::Vector3(0,50,200));
      mCamera->lookAt(Ogre::Vector3(0,0,0));
      mCamera->setNearClipDistance( 5 );
      mViewport = mRenderWindow->addViewport(mCamera);
      mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) /
                              Ogre::Real(mViewport->getActualHeight()));
      mSceneManager->setAmbientLight( Ogre::ColourValue( 1, 1, 1 ) );
      Ogre::Light* l1 = mSceneManager->createLight("l1");
      l1->setType(Ogre::Light::LT_POINT);
      l1->setDiffuseColour(Ogre::ColourValue::Blue);
      l1->setDiffuseColour(0.8f, 0.3f, 0.3f); // this will be a red light
      l1->setSpecularColour(1.0f, 1.0f, 1.0f);
      l1->setPosition(1000,1000,1000);
      l1->setVisible(true);
      Ogre::SceneNode * sn = mSceneManager->getRootSceneNode()->createChildSceneNode("light1");
      sn->attachObject(l1);

      Ogre::OverlaySystem* m_pOverlaySystem = new Ogre::OverlaySystem();
      mSceneManager->addRenderQueueListener(m_pOverlaySystem);

}

void GraphicsManager::startRenderLoop( )
{
   mRoot->startRendering( );
}

bool GraphicsManager::update( )
{

   // In order to do framerate independent movement, we have to know
   // how long it was since the last frame
   int time = 0;//device->getTimer()->getTime();

   mRoot->renderOneFrame( );

   frameTime = ( time - prevTime ) / 1000.0f;
   prevTime = time;
   currentFPS = 1.0f / frameTime;

   Ogre::WindowEventUtilities::messagePump();
   return true;

}

/**
 * returns the time in seconds since last frame;
 */
float GraphicsManager::getFrameTime( )
{
   return frameTime;
}

/**
 * returns the crrent frames per second
 */
float GraphicsManager::getFPS( )
{
   return currentFPS;
}
