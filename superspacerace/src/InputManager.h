#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <OIS/OISJoyStick.h>
//#include <refptr/Referenced.h>
//#include <plib/js.h>
#include "JoystickHandler.h"
#include "ShipJoystickController.h"

class GameManager;

/**
 * Global input handling system. Attaches itself to the device in
 * the constructor. The main entry point is
 * handleEvent(...) which distributes the events to different sub handlers
 */

class PickSystem;

class InputManager : /*public refptr::Referenced,*/ public Ogre::FrameListener//, public OIS::KeyListener
{
    public:

        InputManager( GameManager * gmangr );

        bool initJoystick();

        //needed?
        bool initKeyboard();

      /**
       * OGRE frame listener
       */
        bool frameStarted( const Ogre::FrameEvent & pEvent );

        bool frameRenderingQueued( const Ogre::FrameEvent & pEvent );

        bool frameEnded( const Ogre::FrameEvent & pEvent );

      /**
       * OIS KeyListener
       */
//      bool keyPressed(const OIS::KeyEvent &e);// { return true; }
//
//      bool keyReleased(const OIS::KeyEvent &e);// { return true; }
//
//
//      void getInput( );

//      void setJoystickHandler( OIS::JoyStickListener * pJl );
      void setJoystickHandler( JoystickHandler * pHandler );

        ~InputManager( );

    private:

//        PickSystem * pickSystem;

        OIS::InputManager * mInputManager;

        OIS::Keyboard * mKeyboard;

        OIS::JoyStick * mJoystick;

        JoystickHandler * jHandler;

        bool mContinue;

};



#endif // INPUTMANAGER_H_INCLUDED
