
#include "JoystickHandler.h"
#include <iostream>

JoystickHandler::JoystickHandler( int pJoyNum )
{

}

JoystickHandler::~JoystickHandler( )
{

}

void JoystickHandler::setJoyStickState( const OIS::JoyStickState & pState )
{
   mState = pState;
}


bool JoystickHandler::handle( )
{
//    read( );

    return doHandle( );
}

float JoystickHandler::getStickData( int stickNum )
{
    if( stickNum < 0 || stickNum >= (int)mState.mAxes.size( ) )
        return 0;

    float value =  mState.mAxes[ stickNum ].abs / (double)OIS::JoyStick::MAX_AXIS;
//      #ifdef DEBUG
//      std::cout << "joystick value " << value << std::endl;
//      #endif

    return value;
}

int JoystickHandler::getBtnDown( int btnNum )
{
    if( btnNum < 0 )
        return 0;

   return mState.mButtons[ btnNum ];
//   return 1;//mState.ButtonDown( btnNum );
}

