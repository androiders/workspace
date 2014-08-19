#include "PickSystem.h"
#include <iostream>
#include "GameManager.h"

PickSystem::PickSystem( GameManager * gmngr )
{
//    collisionManager = gmngr->getGraphicsManager()->getSceneManager( )->getSceneCollisionManager( );
    sceneManager = gmngr->getGraphicsManager()->getSceneManager( );
}

std::vector< Ogre::SceneNode* > & PickSystem::getPickedNodes( )
{
    return pickedNodes;
}

void PickSystem::pick( int x, int y )
{
    pickedNodes.clear( );
    Ogre::Ray  ray;// = collisionManager->getRayFromScreenCoordinates( irr::core::position2d<int>(x,y) );
    pick( sceneManager->getRootSceneNode( ), ray );

    std::cout << "picked nodes: " << pickedNodes.size( ) << std::endl;
}

void PickSystem::pick( const Ogre::SceneNode * root,  const Ogre::Ray & ray )
{
//    irr::core::list< irr::scene::ISceneNode *> children = root->getChildren( );
//    irr::core::list< irr::scene::ISceneNode *>::Iterator it = children.begin( );
//
//    for (; it != children.end(); ++it)
//    {
//      irr::scene::ISceneNode* current = *it;
//
//      if ( current->isVisible( ) )
//      {
//         const irr::core::aabbox3df& box = current->getTransformedBoundingBox();
//
//         // do intersection test in object space
//         if (!box.intersectsWithLine(ray))
//            continue;
//
//          //check if the ray intersects the triangle selector if any
//         irr::scene::ITriangleSelector * sel = current->getTriangleSelector( );
//         if( !sel )
//             continue;
//
//          int out = 0;
//          irr::core::triangle3df tri;
//          sel->getTriangles( &tri, 1, out, ray );
//          if( out == 0 )
//              continue;
//          else
//              //insertNode( current );
//              pickedNodes.push_back( current );
//
//      }
//
//      pick( current, ray );
//   }
}

Ogre::SceneNode * PickSystem::getClosestNode( int x, int y )
{
    if( pickedNodes.size( ) == 0 )
        return 0;

    return pickedNodes[0];
}


PickSystem::~PickSystem( )
{
    pickedNodes.clear( );
}
