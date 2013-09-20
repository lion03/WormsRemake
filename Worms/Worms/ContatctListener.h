/**
 \file	ContatctListener.h

 \brief	Declares the contatct listener class.
 */

#pragma once
#include <Box2D/Box2D.h>
#include <map>
#include <typeinfo>
#include "Ground.h"
#include "Projectile.h"

/**
 \brief	Projectile ground.

 \param [in,out]	gameObjectA	If non-null, the game object a.
 \param [in,out]	gameObjectB	If non-null, the game object b.
 */

void projectileGround(GameObject* gameObjectA, GameObject* gameObjectB){

	Projectile *projec = dynamic_cast<Projectile*>(gameObjectA);
	Ground *ground = dynamic_cast<Ground*>(gameObjectB);
	projec->explode();
	ground->setClipOffPoly(projec->getExpPoly());
	
	projec->entety.dead = true;


	projec->killObject(projec);

}

/**
 \brief	Projectile detonate.

 \param [in,out]	projectile	If non-null, the projectile.
 */

void projectileDetonate(GameObject* projectile){

	Projectile *projec = dynamic_cast<Projectile*>(projectile); ///< The projec
	projec->explode();
	projec->entety.dead = true;
	projec->killObject(projec);
}

/**
 \brief	Ground projectile.

 \param [in,out]	gameObjectA	If non-null, the game object a.
 \param [in,out]	gameObjectB	If non-null, the game object b.
 */

void GroundProjectile(GameObject* gameObjectA, GameObject* gameObjectB){
	projectileGround(gameObjectB,gameObjectA);
}

/**
 \brief	Contatct listener.

 \sa	b2ContactListener
 */

class ContatctListener : public b2ContactListener
{

private:


public:

	/**
	 \brief	Begins a contact.
	
	 \param [in,out]	contact	If non-null, the contact.
	 */

	virtual void BeginContact(b2Contact * contact){
		//we assume that all of the collided objects shear the same base class

		if(contact->GetFixtureA()->IsSensor()){
			GameObject::Entety *typeA = static_cast<GameObject::Entety*>(contact->GetFixtureA()->GetUserData());
			if((*typeA).dead)
				return;
			auto tree = m_SingleHitMap.find(typeA->name);//find the proper function

			if(tree!= m_SingleHitMap.end()){
				auto foo = tree->second;
				if(foo)
					foo(typeA->object);//execute function
			}
		} 
		else if(contact->GetFixtureB()->IsSensor())
		{
			GameObject::Entety *typeB = static_cast<GameObject::Entety*>(contact->GetFixtureB()->GetUserData());
			
			if(!typeB)
				return;
			
			if((*typeB).dead)
				return;
			auto tree = m_SingleHitMap.find(typeB->name);//find the proper function

			if(tree!= m_SingleHitMap.end()){
				auto foo = tree->second;
				if(foo)
					foo(typeB->object);//execute function
			}
		}
		else{
			GameObject::Entety *typeA = static_cast<GameObject::Entety*>(contact->GetFixtureA()->GetUserData()); 
			GameObject::Entety *typeB = static_cast<GameObject::Entety*>(contact->GetFixtureB()->GetUserData());

			if((!typeA|| !typeB) ||(  (*typeA).dead || (*typeB).dead))
				return;

			auto tree = m_hitMap.find(std::make_pair(typeA->name,typeB->name));//find the proper function

			if(tree!= m_hitMap.end()){
				auto foo = tree->second;
				if(foo)
					foo(typeA->object,typeB->object);//execute function
			}
		}
	}

	/**
	 \brief	Ends a contact.
	
	 \param [in,out]	b2Contact	If non-null, the 2 contact.
	 */

	virtual void EndContact(b2Contact * b2Contact){



	}

	/**
	 \brief	Initializes a new instance of the ContatctListener class.
	
	 \param [in,out]	world	If non-null, the world.
	 */

	ContatctListener(b2World *world)
	{
		world->SetContactListener(this);
		//register functions 
		m_hitMap.insert(std::make_pair(std::make_pair(std::string(typeid(Projectile).name()),std::string(typeid(Ground).name())),&projectileGround));
		m_hitMap.insert(std::make_pair(std::make_pair(std::string(typeid(Ground).name()),std::string(typeid(Projectile).name())),&GroundProjectile));
		m_SingleHitMap.insert(std::make_pair(std::string(typeid(Projectile).name()),&projectileDetonate));

	}



	virtual ~ContatctListener(void)
	{
	}



private:

	/**
	 \brief	Defines an alias representing the game object*.
	 */

	typedef void (*DoubleHitFunctionPtr)(GameObject*, GameObject*);

	/**
	 \brief	Defines an alias representing the double hit map.
	 */

	typedef std::map< std::pair<std::string,std::string>, DoubleHitFunctionPtr > DoubleHitMap;
	typedef void (*SingleHitFunctionPtr)(GameObject*);

	/**
	 \brief	Defines an alias representing the single hit map.
	 */

	typedef std::map< std::string, SingleHitFunctionPtr > SingleHitMap;


	DoubleHitMap m_hitMap;  ///< The hit map
	SingleHitMap m_SingleHitMap;	///< The single hit map


};

/**
// End of ContatctListener.h
 */

