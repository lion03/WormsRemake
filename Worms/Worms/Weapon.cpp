/**
 \file	Weapon.cpp

 \brief	Implements the weapon class.
 */

#include "Weapon.h"
#include "Worm.h"

/**
 \brief	Finalizes an instance of the Weapon class.
 */

Weapon::~Weapon(void)
{
}

/**
 \brief	Initializes a new instance of the Weapon class.

 \param	attachmentName	Name of the attachment.
 \param	burst		  	The burst.
 */

Weapon::Weapon(const std::string &attachmentName,uint8 burst):m_AttachmentName(attachmentName),m_Burst(burst)
{
	
}

/**
 \brief	Sets an attacment.

 \param [in,out]	worm	If non-null, the worm.
 */

void Weapon::setAttacment(Worm *worm)
{
	Skeleton* wormSkeleton = worm->getSkeleton();

	Skeleton_setAttachment(wormSkeleton,"arm item",m_AttachmentName.c_str());
	
}

/**
// End of Weapon.cpp
 */

