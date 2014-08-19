#include "ShipJoystickController.h"
#include <iostream>


ShipJoystickController::ShipJoystickController( SpaceShip * obj )
  :object( obj )
  {
  }

ShipJoystickController::~ShipJoystickController( )
{
}


//bool ShipJoystickController::buttonPressed (const OIS::JoyStickEvent &arg, int button)
//{
//   switch( button )
//   {
//      case 0:
//         object->setCurrSpeed( object->getMaxSpeed( ) );
//         break;
//      default:
//         break;
//   }
//   return true;
//
////   object->setCurrSpeed( object->getMaxSpeed( ) * (int)(button == 0) );
//}
//
//bool ShipJoystickController::buttonReleased (const OIS::JoyStickEvent &arg, int button)
//{
//   switch( button )
//   {
//      case 0:
//         object->setCurrSpeed( 0 );
//         break;
//      default:
//         break;
//   }
//   return true;
//}
//
//bool ShipJoystickController::axisMoved (const OIS::JoyStickEvent &arg, int axis)
//{
//   float ratio = arg.state.mAxes[ axis ].abs / (float)OIS::JoyStick::MAX_AXIS;
//
////   #ifdef DEBUG
////   std::cout << "joystick ratio " << ratio << std::endl;
////   #endif
//   switch( axis )
//   {
//      case 0:
//         object->setCurrRollAng( object->getMaxRollAng(  ) *  ratio );
//         break;
//      case 1:
//           object->setCurrTiltAng( object->getMaxTiltAng( ) * ratio );
////         object->setCurrRotSpeed( object->getMaxRotSpeed( ) * arg.state.mAxes[ axis ].abs  / (float)OIS::JoyStick::MAX_AXIS );
//         //object->setCurrRotSpeed( object->getMaxRotSpeed( ) );
//         break;
//      default:
//      break;
//   }
//   return true;
//}


bool ShipJoystickController::doHandle( )
{
    object->setCurrRollFrac( getStickData( 0 ) );
    object->setCurrPitchSpeedFraction( getStickData( 1 ) );

    //object->setCurrSpeed( object->getMaxSpeed( ) * getBtnDown( 0 ) );
    object->accelerate( getBtnDown( 0 ) );
    object->setRolling( getBtnDown( 10 ) || getBtnDown( 11 ) );

    return true;
}
