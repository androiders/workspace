SET(AppName superspacerace)

#add libraries here

SET(INC /usr/include/)

include_directories(SYSTEM ${INC}bullet ${INC}/OGRE)


add_executable (${AppName} 
src/DynamicGameObject.cpp  
src/InputManager.h            
src/ResourceManager.h
src/DynamicGameObject.h    
src/JoystickHandler.cpp       
src/SceneNodeToObjectMapper.cpp
src/GameManager.cpp        
src/JoystickHandler.h         
src/SceneNodeToObjectMapper.h
src/GameManager.h          
src/main.cpp                  
src/ShipJoystickController.cpp
src/GameObject.cpp         
src/ObjectCameraFollower.cpp  
src/ShipJoystickController.h
src/GameObject.h           
src/ObjectCameraFollower.h    
src/SpaceShip.cpp
src/GamePhysics.cpp        
src/PhysicsObject.cpp         
src/SpaceShip.h
src/GamePhysics.h          
src/PhysicsObject.h           
src/StaticGameObject.cpp
src/GameWorld.cpp          
src/PickSystem.cpp            
src/StaticGameObject.h
src/GameWorld.h            
src/PickSystem.h              
src/UpdateFrameListener.cpp
src/GraphicsManager.cpp    
src/RaceTarget.cpp            
src/UpdateFrameListener.h
src/GraphicsManager.h      
src/RaceTarget.h
src/InputManager.cpp       
src/ResourceManager.cpp)

target_link_libraries(${AppName} OgreMain OIS boost_system OgreOverlay BulletDynamics BulletCollision LinearMath )

