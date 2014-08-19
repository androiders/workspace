#include "GameObject.h"

const Ogre::Vector3 GameObject::smOrigForward = Ogre::Vector3::NEGATIVE_UNIT_Z;

const Ogre::Vector3 GameObject::smOrigRight = Ogre::Vector3::UNIT_X;

const Ogre::Vector3 GameObject::smOrigUp = Ogre::Vector3::UNIT_Y;

GameObject::GameObject( Ogre::SceneNode * pNode )
{
    mNode = pNode;
    mPhysObj = 0;
}

GameObject::~GameObject()
{
    //    delete node;
}

void GameObject::setPosition( float x, float y, float z )
{
    Ogre::Vector3 pos( x, y, z );
    mNode->setPosition( pos );
}

void GameObject::move( float x, float y, float z )
{
    mNode->translate( x, y, z );
}

void GameObject::move( const Ogre::Vector3 & pTrans )
{
    mNode->translate( pTrans );
}


void GameObject::setPosition( const Ogre::Vector3 & pPos )
{
    mNode->setPosition( pPos );
}

// void GameObject::setPosition( const Vec3::Vec3f & pos )
// {
//     setPosition( pos.x, pos.y, pos.z );
//}

void GameObject::setOrientation( const Ogre::Quaternion & pRot )
{
    mNode->setOrientation( pRot );
}

void GameObject::rotate( const Ogre::Quaternion & pRot )
{
    mNode->rotate( pRot );
}

const Ogre::Vector3 GameObject::getPosition() const
{
    return mNode->getPosition( );
}

const Ogre::Quaternion & GameObject::getOrientation() const
{
    return mNode->getOrientation( );
}

void GameObject::setName( const std::string & pName )
{
    mName = pName;
}

const std::string & GameObject::getName() const
{
    return mName;
}

void GameObject::update( float t )
{
    if( mPhysObj == 0 )
        return;

    setPosition( mPhysObj->getPosition( ) );
}

//void GameObject::setAnimationRange(int pStart, int pEnd )
//{
//    node->setFrameLoop( pStart, pEnd );
//}


//void GameObject::setSceneNode( irr::scene::ISceneNode * pNode )
//{
//    node = pNode;
//}
