#pragma once
#include "External/Clipper/clipper.hpp"
#include "External/TinyXML/tinystr.h"
#include "External/TinyXML/tinyxml.h"
#include "External/poly2tri/poly2tri.h"
#include "Macros.h"
#include <SFML/Graphics.hpp>
class MapLoader
{
public:

	typedef ClipperLib::Polygons GameMap;

	MapLoader(const std::string &pathToMapFile);

	virtual ~MapLoader(void);

	GameMap loadMap(TiXmlElement* root);



	class Map : public sf::Drawable
	{
	public:
		Map(const GameMap& mapPolygons);
		~Map(){};

	protected:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		
		std::vector<sf::VertexArray> m_theMap;

	};



private:

	sf::Vector2i strToVec(const std::string& str);

	TiXmlDocument m_MapFile;
};

