#pragma once
#include <cstdlib>
#include <cmath>
#include <GL/glfw.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "poly2tri/poly2tri.h"
#include "Ground.h"
#include "Clipper/clipper.hpp"
#include <Box2D/Box2D.h>
#include "ContatctListener.h"
#include "ObjectDetroyer.h"
#include "Worm.h"
using namespace std;


using namespace p2t;
using namespace sf;

class Controller
{
public:

	Controller(void):m_objectDestroyer(&m_mainObjectList)
	{

		m_world = new b2World(b2Vec2(0.f,9.8));

		m_contactListener = new ContatctListener(m_world);

	}

	virtual ~Controller(void)
	{
	}

	void MainGameLoop(void)
	{
	}

private:

	b2World* m_world;

	std::vector<GameObject*> m_mainObjectList;

	ObjectDetroyer m_objectDestroyer;

	ContatctListener* m_contactListener;
};

