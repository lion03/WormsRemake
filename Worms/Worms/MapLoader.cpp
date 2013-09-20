#include "MapLoader.h"
#include <sstream>
#include "ResourceManager.h"

MapLoader::~MapLoader(void)
{



}

/**
\brief	Loads a map.

\param [in,out]	root	If non-null, the root.

\return	The map.
*/

ClipperLib::Polygons MapLoader::loadMap(TiXmlElement*root)
{



	TiXmlElement* pathElement = root->FirstChildElement();

	bool realtive = false;

	bool absolute = false;

	ClipperLib::Polygons retPoly;
	while (pathElement)
	{
		std::string path(pathElement->Attribute("d"));
		std::stringstream strStream(path);
		std::string buff;
		std::vector<std::string> parsed;
		ClipperLib::Polygon tempPoly;
		while (std::getline(strStream,buff,' '))
		{
			if(buff != "m" && buff != "z" && buff != "L" && buff != "l" && buff != "z")
			{
				sf::Vector2i point = strToVec(buff);
				if(absolute){
					tempPoly.push_back(ClipperLib::IntPoint(point.x, point.y));
					absolute = false;
					continue;
				}
				else
				{
					ClipperLib::IntPoint lastPoin = tempPoly.back();
					tempPoly.push_back(ClipperLib::IntPoint(lastPoin.X + point.x , lastPoin.Y + point.y));
				}
			}else if(buff == "m" || buff == "L" || buff == "l"){
				absolute = true;
			}
			//parsed.push_back(buff);
		}
		retPoly.push_back(tempPoly);
		pathElement = pathElement->NextSiblingElement();
	}

	//root->Attribute("d");

	return retPoly;
}

/**
\brief	Converts a str to a vector.

\param	str	The.

\return	str as a sf::Vector2i.
*/

sf::Vector2i MapLoader::strToVec(const std::string&str)
{
	std::stringstream ss(str);

	std::string buff;
	std::vector<int> temp;
	while (std::getline(ss,buff,','))
	{
		temp.push_back(std::stoi(buff));
	}

	return sf::Vector2i(temp[0],temp[1]);
}

/**
\brief	Initializes a new instance of the MapLoader class.

\param	pathToMapFile	The path to map file.
*/

MapLoader::MapLoader(const std::string &pathToMapFile)
{
	
	std::string fullPath(pathToMapFile);

	m_MapFile.LoadFile(fullPath.c_str());

	TiXmlElement* root = m_MapFile.FirstChildElement()->FirstChildElement();

	while (root)
	{
		if(root->ValueTStr() == "g")
			ResourceManager<GameMap>::getInstence()->registerResource(loadMap(root),root->Attribute("id"));

		root = root->NextSiblingElement();
	}

}

/**
\brief	Initializes a new instance of the Map class.

\param	mapPolygon	The map polygon.
*/

MapLoader::Map::Map(const GameMap&mapPolygons){

	
	std::vector< p2t::CDT* > cdts;
	std::vector<std::vector<p2t::Point*> > polylines;


	for (unsigned int i = 0; i < mapPolygons.size() ; i++)
	{


		std::vector<p2t::Point*> polyline;
		std::vector<p2t::Point> polyline1;
		//m_EdgesShape.push_back(tempChain);

		for (unsigned int j = 0; j < mapPolygons[i].size(); j++)
		{
			polyline.push_back(new p2t::Point(ROUND_TO_NEAREST_F((float)mapPolygons[i][j].X),ROUND_TO_NEAREST_F((float)mapPolygons[i][j].Y)));

		}

		cdts.back()->Triangulate();


		//m_triangles.push_back(cdts.back()->GetTriangles());

		auto tri = cdts.back()->GetTriangles();
		sf::VertexArray tempVarr(sf::Triangles);
		for (unsigned int i = 0; i < tri.size(); i++)
		{

			tempVarr.append(sf::Vertex(sf::Vector2f((tri[i]->GetPoint(0)->x),(tri[i]->GetPoint(0)->y)),sf::Vector2f(tri[i]->GetPoint(0)->x,tri[i]->GetPoint(0)->y)));
			tempVarr.append(sf::Vertex(sf::Vector2f((tri[i]->GetPoint(1)->x),(tri[i]->GetPoint(1)->y)),sf::Vector2f(tri[i]->GetPoint(1)->x,tri[i]->GetPoint(1)->y)));
			tempVarr.append(sf::Vertex(sf::Vector2f((tri[i]->GetPoint(2)->x),(tri[i]->GetPoint(2)->y)),sf::Vector2f(tri[i]->GetPoint(2)->x,tri[i]->GetPoint(2)->y)));

		}

		for (unsigned int i = 0; i < polyline.size(); i++)
		{
			delete polyline[i];
		}
		m_theMap.push_back(tempVarr);
	}

}

/**
 \brief	Draws.

 \param [in,out]	target	Target for the.
 \param	states			  	The states.
 */

void MapLoader::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < m_theMap.size(); i++)
	{
		target.draw(m_theMap[i],states);
	}
}

