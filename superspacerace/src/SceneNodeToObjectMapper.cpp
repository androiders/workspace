#include "SceneNodeToObjectMapper.h"

SceneNodeToObjectMapper::SceneNodeToObjectMapper( )
{
}

GameObject * SceneNodeToObjectMapper::getObject( unsigned int id )
{
   std::map< unsigned int, GameObject * >::iterator it = theMap.find( id );
    if( it == theMap.end( ) )
        return 0;

    return (*it).second;
}

GameObject * SceneNodeToObjectMapper::getObject( const Ogre::SceneNode * node )
{
  return 0;//getObject( Ogre::any_cast< unsigned int >( node->getUserAny( ) ) );
}

bool SceneNodeToObjectMapper::registerObject( GameObject * obj, unsigned int id )
{
    if( objectExists( id ) )
        return false;

    theMap[ id ] = obj;
    return true;
}

bool SceneNodeToObjectMapper::registerObject( GameObject * obj, Ogre::SceneNode * node )
{
  return false;//registerObject( obj, Ogre::any_cast< unsigned int >( node->getUserAny( ) ) );
}

bool SceneNodeToObjectMapper::objectExists( unsigned int id )
{
    std::map< unsigned int , GameObject * >::iterator it = theMap.find( id );
    return it != theMap.end( );
}

bool SceneNodeToObjectMapper::objectExists( const Ogre::SceneNode * node )
{
  return false;//objectExists( Ogre::any_cast< unsigned int >( node->getUserAny( ) ) );
}

SceneNodeToObjectMapper::~SceneNodeToObjectMapper( )
{
    theMap.clear( );
}
