/**
\file	Ground.h

\brief	Declares the ground class.
*/

#pragma once
#pragma warning(disable: 4244)
#pragma warning(disable: 4150)
#pragma warning(disable: 4305)
#pragma warning(disable: 4172)
#include <Box2D/Box2D.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "External/Clipper/clipper.hpp"
#include "External/poly2tri/poly2tri.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Macros.h"
#include "External/TinyXML/tinystr.h"
#include "External/TinyXML/tinyxml.h"
#include "MapLoader.h"

/**
\brief	Ground.

\sa	GameObject
*/

class Ground :  public GameObject
{

private:

	b2BodyDef m_GroundBodyDef;  ///< The ground body definition

	std::list<std::vector<p2t::Point> > m_Edges;  ///<the edges

	std::vector<std::vector<p2t::Triangle*> > m_triangles; ///<the triangles
	std::list<b2ChainShape> m_EdgesShape;  ///< The edges shape
	std::list<b2Fixture*> m_EdgeFixtures;   ///< The edge fixtures
	std::vector<sf::VertexArray> m_draw;

	std::shared_ptr<sf::Texture> m_groundTexture;

public:

	/**
	\brief	Applies the force.

	\param	impulse	The impulse.
	\param	point  	The point.
	*/

	virtual void applyForce(const b2Vec2& impulse, const b2Vec2& point){}

	/**
	\brief	Initializes a new instance of the Ground class.

	\param [in,out]	world			 	If non-null, the world.
	\param [in,out]	destroyer		 	If non-null, the destroyer.
	\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
	*/

	Ground(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*> * mainGameObjectVec,const MapLoader::GameMap &map):GameObject(destroyer,mainGameObjectVec)
	{

		m_groundTexture = ResourceManager<sf::Texture>::getInstence()->getResource("GND");
		entety.name = typeid(*this).name();
		entety.object = ( this);

		setBody( world->CreateBody(&m_GroundBodyDef));
		getBody()->SetUserData((void*)&entety);
		m_GroundBodyDef.position = b2Vec2(0.f,0.f);
#ifdef _DEBUG
		rebuildGround(*ResourceManager<MapLoader::GameMap>::getInstence()->getResource("map3").get());
#else
		rebuildGround(map);
#endif

	}

	/**
	\brief	Sets clip off polygon.

	\param	poly	The polygon.
	*/

	virtual void setClipOffPoly(const ClipperLib::Polygons &poly){clipOffPoly = poly;}

	/**
	\brief	Finalizes an instance of the Ground class.
	*/

	virtual ~Ground(void)
	{
		//getBody()->GetWorld()->DestroyBody(getBody());

		clearFixtures();
		clearShapes();
		clearTriangles();
		clearEdges();
	}	

	/**
	\brief	Updates this object.
	*/

	virtual void update(){

		if(clipOffPoly.size() > 0){
			clipOff(clipOffPoly);
			clipOffPoly.clear();
		}

	}

	/**
	\brief	Clip off.

	\param	clipper	The clipper.

	\return	null if it fails, else.
	*/

	virtual std::vector<b2ChainShape*> clipOff(const ClipperLib::Polygons &clipper){

		std::vector<std::vector<p2t::Point*> > tempEdges;
		std::vector<std::vector<p2t::Triangle*> > temptriangles;


		ClipperLib::Polygons oldGround;
		ClipperLib::Polygons newGround;


		for (auto it = m_Edges.begin(); it != m_Edges.end(); it++)
		{
			ClipperLib::Polygon groundChunk;
			//

			for (unsigned int j = 0; j < (*it).size(); j++)
			{

				groundChunk.push_back(ClipperLib::IntPoint((long long)ROUND_TO_NEAREST_F((*it)[j].x*100.f),(long long)ROUND_TO_NEAREST_F((*it)[j].y*100.f)));

			}

			ClipperLib::Polygons cleanGroundChunck;
			//ClipperLib::CleanPolygon(groundChunk,groundChunk);
			ClipperLib::SimplifyPolygon(groundChunk,cleanGroundChunck,ClipperLib::pftNonZero);

			for (unsigned int i = 0; i < cleanGroundChunck.size(); i++)
			{
				oldGround.push_back(cleanGroundChunck[i]);
			}


		}


		ClipperLib::Polygons temp = clipper;
		ClipperLib::Polygons BrokenPolys ;
		//ClipperLib::CleanPolygons(oldGround,cleandPolys);
		ClipperLib::Clipper c;
		ClipperLib::SimplifyPolygons(oldGround,oldGround,ClipperLib::pftNonZero);
		//ClipperLib::CleanPolygons(oldGround,oldGround);
		c.AddPolygons(oldGround,ClipperLib::ptSubject);
		ClipperLib::SimplifyPolygons(temp,temp,ClipperLib::pftNonZero);
		//ClipperLib::CleanPolygons(temp,temp);
		c.AddPolygons(temp,ClipperLib::ptClip);
		c.Execute(ClipperLib::ctDifference,newGround);
		ClipperLib::SimplifyPolygons(newGround,newGround,ClipperLib::pftNonZero);
		//ClipperLib::CleanPolygons(newGround,newGround);
		c.Clear();


		rebuildGround(newGround);
		std::vector<b2ChainShape*> ret;
		return ret;
	}


private:

	/**
	\brief	Rebuild ground.

	\param	polygons	The polygons.
	*/

	virtual void rebuildGround(const ClipperLib::Polygons & polygons){
		clearTriangles();
		clearFixtures();
		clearEdges();
		clearShapes();
		clearDrawEdges();
		std::vector< p2t::CDT* > cdts;
		std::vector<std::vector<p2t::Point*> > polylines;
		for (unsigned int i = 0; i < polygons.size() ; i++)
		{


			std::vector<p2t::Point*> polyline;
			std::vector<p2t::Point> polyline1;
			b2ChainShape tempChain;// = new b2ChainShape();
			//m_EdgesShape.push_back(tempChain);
			std::vector<b2Vec2> groundVert;

			for (unsigned int j = 0; j < polygons[i].size(); j++)
			{
				groundVert.push_back(b2Vec2(ROUND_TO_NEAREST_F(SCALE_DOWN((float)polygons[i][j].X)),ROUND_TO_NEAREST_F(SCALE_DOWN((float)polygons[i][j].Y))));
				polyline.push_back(new p2t::Point(ROUND_TO_NEAREST_F((float)polygons[i][j].X),ROUND_TO_NEAREST_F((float)polygons[i][j].Y)));
				polyline1.push_back(p2t::Point(ROUND_TO_NEAREST_F(SCALE_DOWN((float)polygons[i][j].X)),ROUND_TO_NEAREST_F(SCALE_DOWN((float)polygons[i][j].Y))));

			}
			m_Edges.push_back(polyline1);




			tempChain.CreateLoop(&groundVert[0],groundVert.size());
			//m_EdgesShape.push_back(tempChain);
			b2FixtureDef tempFixDef;

			tempFixDef.userData =  (void*)&entety;
			tempFixDef.friction = 10.f;
			tempFixDef.shape = &tempChain;
			tempFixDef.filter.categoryBits = GameObject::GROUND;
			tempFixDef.filter.maskBits = GameObject::OBJECT | GameObject::PLAYER | GameObject::PROJECTILE;
			getBody()->CreateFixture(&tempFixDef);

			//m_EdgeFixtures.push_back();

			cdts.push_back(new p2t::CDT(polyline));

			cdts.back()->Triangulate();


			//m_triangles.push_back(cdts.back()->GetTriangles());

			auto tri = cdts.back()->GetTriangles();
			sf::VertexArray tempVarr(sf::Triangles);
			for (unsigned int i = 0; i < tri.size(); i++)
			{

				tempVarr.append(sf::Vertex(sf::Vector2f(SCALE_DOWN(tri[i]->GetPoint(0)->x),SCALE_DOWN(tri[i]->GetPoint(0)->y)),sf::Vector2f(tri[i]->GetPoint(0)->x,tri[i]->GetPoint(0)->y)));
				tempVarr.append(sf::Vertex(sf::Vector2f(SCALE_DOWN(tri[i]->GetPoint(1)->x),SCALE_DOWN(tri[i]->GetPoint(1)->y)),sf::Vector2f(tri[i]->GetPoint(1)->x,tri[i]->GetPoint(1)->y)));
				tempVarr.append(sf::Vertex(sf::Vector2f(SCALE_DOWN(tri[i]->GetPoint(2)->x),SCALE_DOWN(tri[i]->GetPoint(2)->y)),sf::Vector2f(tri[i]->GetPoint(2)->x,tri[i]->GetPoint(2)->y)));

			}

			for (unsigned int i = 0; i < polyline.size(); i++)
			{
				delete polyline[i];
			}
			m_draw.push_back(tempVarr);

			/*
			for (int i = 0; i < cdts.size(); i++)
			{
			delete cdts[i];
			}

			cdts.clear();
			*/
		}

		for (unsigned int i = 0; i < cdts.size(); i++)
		{

			delete cdts[i];
		}

		cdts.clear();
	}

	/**
	\brief	Clears the triangles.
	*/

	virtual void clearTriangles(){

		for (unsigned int i = 0; i < m_triangles.size(); i++)
		{
			for (unsigned int j = 0; j < m_triangles.at(i).size(); j++)
			{
				delete m_triangles[i][j];
			}
		}
		m_triangles.clear();

	}

	virtual void clearDrawEdges(){

		for (unsigned int i = 0; i < m_draw.size(); i++)
		{
			m_draw[i].clear();
		}
		m_draw.clear();

	}

	/**
	\brief	Clears the edges.
	*/

	virtual void clearEdges(){

		for (auto it = m_Edges.begin(); it != m_Edges.end(); it++)
		{
			for (unsigned int j = 0; j < (*it).size(); j++)
			{
				//delete (*it)[j];
			}
		}

		m_Edges.clear();

	}

	/**
	\brief	Clears the fixtures.
	*/

	virtual void clearFixtures(){


		auto it = getBody()->GetFixtureList();

		while (it)
		{
			auto temp = it->GetShape();
			getBody()->DestroyFixture(it);

			it = getBody()->GetFixtureList();


		}

		/*
		for (auto it = m_EdgeFixtures.begin(); it != m_EdgeFixtures.end(); it++)
		{

		getBody()->DestroyFixture((*it));
		it = m_EdgeFixtures.erase(it);
		if(it == m_EdgeFixtures.end())
		break;
		}

		m_EdgeFixtures.clear();
		*/

	}

	/**
	\brief	Clears the shapes.
	*/

	virtual void clearShapes(){
		for (auto it = m_EdgesShape.begin(); it != m_EdgesShape.end(); it++)
		{

			//delete (*it);

		}
		m_EdgesShape.clear();
	}

	std::string m_name; ///< The name

	ClipperLib::Polygons clipOffPoly;   ///< The clip off polygon



protected:

	/**
	\brief	Draws.

	\param [in,out]	target	Target for the.
	\param	states			  	The states.
	*/

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const{


		sf::Transform tarnsform;
		tarnsform.scale(0.5,0.5);
		states.texture = m_groundTexture.get();

		for (unsigned int i = 0; i < m_draw.size(); i++)
		{
			target.draw(m_draw[i],states);
		}
	}

};

/**
// End of Ground.h
*/

