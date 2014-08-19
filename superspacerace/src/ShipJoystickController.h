#ifndef SHIPJOYSTICKCONTROLLER_H_INCLUDED
#define SHIPJOYSTICKCONTROLLER_H_INCLUDED

#include "JoystickHandler.h"
//#include <refptr/RefPtr.h>
#include <OIS/OIS.h>
#include "SpaceShip.h"

/**
 * Class for handling a ship like a space ship controlled by a joystick :)
 * Assumes joystick is calibrated correctly.
 */

class ShipJoystickController : public JoystickHandler
{
    public:

      ShipJoystickController( SpaceShip * obj );

      virtual ~ShipJoystickController( );

//      bool 	buttonPressed (const OIS::JoyStickEvent &arg, int button);
//
//      bool 	buttonReleased (const OIS::JoyStickEvent &arg, int button);
//
//      bool 	axisMoved (const OIS::JoyStickEvent &arg, int axis);


    protected:
      bool doHandle( );

    private:

        SpaceShip * object;

};



#endif // SHIPJOYSTICKCONTROLLER_H_INCLUDED
