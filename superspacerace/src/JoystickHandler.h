#ifndef JOYSTICKHANDLER_H_INCLUDED
#define JOYSTICKHANDLER_H_INCLUDED

//#include <refptr/Referenced.h>
#include <OIS/OIS.h>

/**
 * Handler interface for joysticks
 */

 class JoystickHandler //: public refptr::Referenced
 {
     public:
        JoystickHandler( int pJoyNum = 0 );

        /**
         * entry point for the joystick handler. Called every frame.
         * Calls doHandle for subclasses
         */
        bool handle( );

//        int getNumButtons( )
//        { return numButtons; }

//        int getNumAxes( )
//        { return numAxes; }

        //user should always check valid after creation
//        bool valid( )
//        { return id != -1; }

//        int getId( )
//        { return id; }

      void setJoyStickState( const OIS::JoyStickState & pState );

      virtual ~JoystickHandler( );

    protected:

        virtual bool doHandle( ) = 0;

        float getStickData( int stickNum );

        int getBtnDown( int btnNum );

    private:

    OIS::JoyStickState mState;




 };


#endif // JOYSTICKHANDLER_H_INCLUDED
