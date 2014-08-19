#ifndef GRAPHICSMANAGER_H_INCLUDED
#define GRAPHICSMANAGER_H_INCLUDED

//#include <irrlicht/irrlicht.h>
#include <OGRE/Ogre.h>
//#include <refptr/Referenced.h>

class GraphicsManager //: public refptr::Referenced
{
    public:

        GraphicsManager( int resx = 800, int resy = 600, int bpp = 24 );

        void setupVideo( int resx = 800, int resy = 600, int bpp = 24 );

        Ogre::SceneManager * getSceneManager( )
        { return mSceneManager; }

         Ogre::Camera * getCamera( )
         { return mCamera; }

         Ogre::RenderWindow * getRenderWindow( )
         { return mRoot->getAutoCreatedWindow( ); }

         Ogre::Root * getRoot( )
         { return mRoot; }

         void startRenderLoop( );

        /**
         * returns the time in seconds since last frame;
         */
        float getFrameTime( );

        /**
         * returns the crrent frames per second
         */
        float getFPS( );

        bool update( );


//    protected:

        ~GraphicsManager( );

    private:

      Ogre::Root *mRoot;

      Ogre::SceneManager * mSceneManager;

      Ogre::Camera * mCamera;

      Ogre::Viewport* mViewport;

      Ogre::RenderWindow * mRenderWindow;

       float currentFPS;

       float frameTime;

       int prevTime;


};

#endif // GRAPHICSMANAGER_H_INCLUDED
