#include "InputManager.h"
#include "GameManager.h"
#include "PickSystem.h"
#include <iostream>

InputManager::InputManager( GameManager * gmangr )
{
//    collisionMngr = gmangr->getGraphicsManager()->getSceneManager( )->getSceneCollisionManager( );
//    gmangr->getGraphicsManager( )->getDevice( )->setEventReceiver( this );
//    pickSystem = gmangr->getPickSystem( );

//    clickedNode = 0;
//    hoveredNode = 0;

//    jsInit( );

   size_t windowHnd = 0;
   std::ostringstream windowHndStr;
   OIS::ParamList pl;
   Ogre::RenderWindow *win = gmangr->getGraphicsManager( )->getRenderWindow( );

   win->getCustomAttribute("WINDOW", &windowHnd);
   windowHndStr << windowHnd;
   pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
   mInputManager = OIS::InputManager::createInputSystem(pl);
   mJoystick = 0;
   mKeyboard = 0;
   mContinue = true;
}

InputManager::~InputManager( )
{
  if( mKeyboard ) 
    {
      mInputManager->destroyInputObject( mKeyboard );
      mKeyboard = 0;
    }
  if( mJoystick )
    {
      mInputManager->destroyInputObject( mJoystick );
      mJoystick = 0;
    }
  
  OIS::InputManager::destroyInputSystem(mInputManager);  
 #ifdef DEBUG
  std::cout << "destroyed input manager " << std::endl;
#endif
}

bool InputManager::initJoystick()
{
    bool retVal = true;
    try
    {
        mJoystick = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));
    }
    catch (const OIS::Exception &e)
    {
        retVal = false;
    #ifdef DEBUG
        std::cout << e.eText() << std::endl;
    #endif
    }
    return retVal;
}

bool InputManager::initKeyboard()
{
    bool retVal = true;
    try
    {
        mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
    }
    catch (const OIS::Exception &e)
    {
        retVal = false;
        #ifdef DEBUG
            std::cout << e.eText() << std::endl;
        #endif
    }
    return retVal;
}


void InputManager::setJoystickHandler(  JoystickHandler * pHandler  )
{
   jHandler = pHandler;
}

bool InputManager::frameStarted( const Ogre::FrameEvent & pEvent )
{
//    if(mMouse)
//            mMouse->capture();
   if(mKeyboard)
   {
      mKeyboard->capture();
      mContinue = !mKeyboard->isKeyDown( OIS::KC_ESCAPE );
   }

//
   if( mJoystick )
   {
      mJoystick->capture( );
      jHandler->setJoyStickState( mJoystick->getJoyStickState( ) );
      jHandler->handle();
   }


//       jHandler->handle( );

   return mContinue;
}

bool InputManager::frameRenderingQueued( const Ogre::FrameEvent & pEvent )
{
   return true;
}

bool InputManager::frameEnded( const Ogre::FrameEvent & pEvent )
{
   return true;
}

//bool InputManager::keyPressed(const OIS::KeyEvent &e)
//{
//   //bool ok = true;
//
//   switch (e.key)
//   {
//      case OIS::KC_ESCAPE:
//         mContinue = false;
//         break;
//      default:
//          break;
//   }
//
//   return mContinue;
//}
//
//bool InputManager::keyReleased(const OIS::KeyEvent &e )
//{
//   return true;
//}
//
//
//void InputManager::getInput( )
//{
//
//    jHandler->handle( );
//    int btn;
//    float axes[3];
//    joy->read( & btn, axes );
//
//        #ifdef DEBUG
//        std::cout << "joy read: " << btn << " " << axes[0] << " " << axes[1] << " " << axes[2] << std::endl;
//        #endif
//
//}

//bool InputManager::OnEvent( const irr::SEvent & event )
//{
//    switch( event.EventType )
//    {
//
//        case( irr::EET_KEY_INPUT_EVENT ) :
//            return handleKeyEvent( event.KeyInput );
//            break;
//
//        case( irr::EET_MOUSE_INPUT_EVENT ) :
//            return handleMouseEvent( event.MouseInput );
//            break;
//
//        default:
//            break;
//    }
//
//    return false;
//
//}
//
//bool InputManager::handleKeyEvent( const irr::SEvent::SKeyInput & key )
//{
//    return false;
//}
//
//bool InputManager::handleMouseEvent( const irr::SEvent::SMouseInput & mouse )
//{
//    //std::cout << "mouse input: " << mouse.X << " " << mouse.Y << " " << mouse.Event << std::endl;
//
//    if( mouse.Event == irr::EMIE_LMOUSE_PRESSED_DOWN )
//    {
//        pickSystem->pick( mouse.X, mouse.Y );
//        irr::scene::ISceneNode * n = pickSystem->getClosestNode( mouse.X, mouse.Y );
//        clickedNode = collisionMngr->getSceneNodeFromScreenCoordinatesBB( irr::core::position2d< int >( mouse.X, mouse.Y ) );
//        if( n != 0 && clickedNode != 0 )
//            std::cout << "irr node: " << clickedNode->getID( ) << " my node " << n->getID( ) << std::endl;
//
//    }
//    if( mouse.Event == irr::EMIE_MOUSE_MOVED )
//    {
//        hoveredNode = collisionMngr->getSceneNodeFromScreenCoordinatesBB( irr::core::position2d< int >( mouse.X, mouse.Y ) );
//    }
//
////    std::cout << "mouse input: " << mouse.X << " " << mouse.Y << " " << mouse.Event << std::endl;
//    return false;
//
//}
