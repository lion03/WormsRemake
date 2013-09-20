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

#include "Render.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <SFML/OpenGL.hpp>
#endif

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "Macros.h"
using namespace std;
#define RATIO SCALE
EEDebugDraw3::EEDebugDraw3(void):
	pixmeters(RATIO),//arbitrary value dependant on the program needs
	radegrees(57.2957795f),//degrees per radian,a physical constant
	m_target(0x0)
{
	AppendFlags(static_cast<uint32>(32));//set all drawing bits to 1(not all 32 are relevant but it's ok)
}
void EEDebugDraw3::LinkTarget(sf::RenderTarget& gtarget)
{
	m_target=&gtarget;
}
void EEDebugDraw3::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape shape;
	shape.setOutlineColor(EEColor(color));
	shape.setOutlineThickness(1);
	shape.setFillColor(sf::Color::Transparent);
	shape.setPointCount(vertexCount);
	for(int i=0;i<vertexCount;++i)
		{shape.setPoint(i,EEVector(vertices[i]));}
	m_target->draw(shape);
}
void EEDebugDraw3::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape shape;
	shape.setFillColor(EEColor(color));
	shape.setPointCount(vertexCount);
	for(int i=0;i<vertexCount;++i)
	{shape.setPoint(i,EEVector(vertices[i]));}
	m_target->draw(shape);
}
void EEDebugDraw3::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape shape;
	shape.setOutlineColor(EEColor(color));
	shape.setOutlineThickness(1);
	shape.setFillColor(sf::Color::Transparent);
	shape.setRadius(radius*pixmeters);
	shape.setOrigin(sf::Vector2f(radius*pixmeters,radius*pixmeters));//set origin to middle or position setter below would not work correctly
	shape.setPosition(EEVector(center));
	m_target->draw(shape);
}
void EEDebugDraw3::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape shape;
	shape.setFillColor(EEColor(color));
	shape.setRadius(radius*pixmeters);
	shape.setOrigin(sf::Vector2f(radius*pixmeters,radius*pixmeters));
	shape.setPosition(EEVector(center));
	m_target->draw(shape);
}
void EEDebugDraw3::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[2];//const sized c styled array, safe enough in here
	line[0].color=EEColor(color);
	line[0].position=EEVector(p1);
	line[1].color=EEColor(color);
	line[1].position=EEVector(p2);
	m_target->draw(line,2,sf::Lines);
}