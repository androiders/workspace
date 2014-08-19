#include "UpdateFrameListener.h"

UpdateFrameListener::UpdateFrameListener( GameManager * pGameMngr )
{
   mGameManager = pGameMngr;
}

UpdateFrameListener::~UpdateFrameListener( )
{

}

      /**
       * OGRE frame listener
       */
bool UpdateFrameListener::frameStarted( const Ogre::FrameEvent & pEvent )
{
   return true;
}

bool UpdateFrameListener::frameRenderingQueued( const Ogre::FrameEvent & pEvent )
{
   return true;
}

bool UpdateFrameListener::frameEnded( const Ogre::FrameEvent & pEvent )
{
   mGameManager->updateWorld( pEvent.timeSinceLastFrame );
   return true;
}
