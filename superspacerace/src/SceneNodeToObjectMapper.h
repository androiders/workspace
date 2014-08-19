#ifndef SCENENODETOOBJECTMAPPER_H_INCLUDED
#define SCENENODETOOBJECTMAPPER_H_INCLUDED

//#include <refptr/Referenced.h>
//#include <refptr/RefPtr.h>
#include <OGRE/OgreAny.h>
#include <map>
#include "GameObject.h"

class SceneNodeToObjectMapper //: public refptr::Referenced
{
    public:

        SceneNodeToObjectMapper( );

        GameObject * getObject( unsigned int id );

        GameObject * getObject( const Ogre::SceneNode * node );

        bool registerObject( GameObject * obj, unsigned int id );

        bool registerObject( GameObject * obj, Ogre::SceneNode * node );

        bool objectExists( const Ogre::SceneNode * node );

        bool objectExists( unsigned int id );

        ~SceneNodeToObjectMapper( );

    protected:

        std::map< unsigned int,  GameObject * > theMap;

};


#endif // SCENENODETOOBJECTMAPPER_H_INCLUDED
