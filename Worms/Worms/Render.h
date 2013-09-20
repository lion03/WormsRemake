/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
struct b2AABB;

class EEDebugDraw3 : public b2Draw
{
private:
	sf::RenderTarget * m_target;
	//inliners for colour and point conversions
	inline sf::Color EEColor(const b2Color& gCol)
	{
		return sf::Color(static_cast<sf::Uint8>(255*gCol.r),
			static_cast<sf::Uint8>(255*gCol.g),
			static_cast<sf::Uint8>(255*gCol.b));
	}
	inline sf::Vector2f EEVector(const b2Vec2& gVec){return sf::Vector2f(gVec.x*pixmeters,gVec.y*pixmeters);}
	const float pixmeters,radegrees;//constants for point and degree conversions
public:
	EEDebugDraw3(void);
	virtual ~EEDebugDraw3(void){};
	void LinkTarget(sf::RenderTarget& gtarget);
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	virtual void DrawTransform(const b2Transform &xf){};
};
