#ifndef UPDATEFRAMELISTENER_H_INCLUDED
#define UPDATEFRAMELISTENER_H_INCLUDED

#include <OGRE/Ogre.h>
#include "GameManager.h"

class UpdateFrameListener : public Ogre::FrameListener
{
   public:

      UpdateFrameListener( GameManager * pGameMngr );

      ~UpdateFrameListener( );

      /**
       * OGRE frame listener
       */
        bool frameStarted( const Ogre::FrameEvent & pEvent );

        bool frameRenderingQueued( const Ogre::FrameEvent & pEvent );

        bool frameEnded( const Ogre::FrameEvent & pEvent );

   private:

      GameManager * mGameManager;
};

#endif // UPDATEFRAMELISTENER_H_INCLUDED
