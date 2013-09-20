/*
* Poly2Tri Copyright (c) 2009-2010, Poly2Tri Contributors
* http://code.google.com/p/poly2tri/
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
* * Neither the name of Poly2Tri nor the names of its contributors may be
*   used to endorse or promote products derived from this software without specific
*   prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//#define GLFW_DLL
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
#include "TinyXML/tinyxml.h"
#include "Loader.h"
#include "Render.h"
using namespace std;


using namespace p2t;
using namespace sf;

void Init();
void ShutDown(int return_code);
void MainLoop(const double zoom);
void Draw(const double zoom);
void DrawMap(const double zoom);
void ConstrainedColor(bool constrain);
double StringToDouble(const std::string& s);
double Random(double (*fun)(double), double xmin, double xmax);
double Fun(double x);

/// Dude hole examples
vector<Point*> CreateHeadHole();
vector<Point*> CreateChestHole();

float rotate_y = 0,
	rotate_z = 0;
const float rotations_per_tick = .2;

/// Screen center x
double cx = 0.0;
/// Screen center y
double cy = 0.0;

/// Constrained triangles

vector<vector<Triangle*> > triangles;
/// Triangle map1
list<Triangle*> map1;
/// Polylines
vector< vector<Point*> > polylines;
b2Body *grondb2;
b2Body *ball;
b2World *world;
/// Draw the entire triangle map?
bool draw_map = false;
/// Create a random distribution of points?
bool random_distribution = false;

template <class C> void FreeClear( C & cntr ) {
	for ( typename C::iterator it = cntr.begin(); 
		it != cntr.end(); ++it ) {
			delete * it;
	}
	cntr.clear();
}

int main(int argc, char* argv[])
{


	int num_points = 0;
	double max, min;
	double zoom = 1.0;

	world = new b2World(b2Vec2(0.0,9.8));

	double init_time = glfwGetTime();


	double dt = glfwGetTime() - init_time;

	//triangles = cdt->GetTriangles();
	//map1 = cdt->GetMap();

	cout << "Number of points = " << num_points << endl;
	cout << "Number of triangles = " << triangles.size() << endl;
	cout << "Elapsed time (ms) = " << dt*1000.0 << endl;

	MainLoop(zoom);

	// Cleanup

	//delete cdt;

	// Free points
	for(int i = 0; i < polylines.size(); i++) {
		vector<Point*> poly = polylines[i];
		FreeClear(poly);
	}

	ShutDown(0);
	return 0;
}

void Init()
{





	/*
	const int window_width = 800,
	window_height = 600;

	if (glfwInit() != GL_TRUE)
	ShutDown(1);
	// 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
	if (glfwOpenWindow(window_width, window_height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
	ShutDown(1);

	glfwSetWindowTitle("Poly2Tri - C++");
	glfwSwapInterval(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	*/
}

void ShutDown(int return_code)
{
	glfwTerminate();
	exit(return_code);
}

void MainLoop(const double zoom)
{
	Loader loader;
	AnimationDB::getAnimationDB();
	ContatctListener contactListener(world);
	std::vector<GameObject*> mainObjectList;


	ObjectDetroyer destroyer(&mainObjectList);
	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"PolyToTri",sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(800,600),"PolyToTri", sf::Style::Default, sf::ContextSettings(32));

	window.setVerticalSyncEnabled(true);
	sf::Texture texture;
	texture.loadFromFile("free-grass-texture-024.jpg");
	DebugDraw debugDraw(&window);
	//Projectile sfBall(world,&destroyer);

	Ground ground(world,&destroyer);
	Worm worm(world,&destroyer);
	mainObjectList.push_back(&worm);
	mainObjectList.push_back(&ground);
	world->SetDebugDraw(&debugDraw);
	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{

			EventDispatcher::notifyAll(Event);

			if(Event.type == sf::Event::Closed)
				window.close();

			if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left){

				ClipperLib::Polygons exp(1);
				sf::Vector2f tempVec = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));

				for (float i = 0.f; i < 3.141592654f*2.f; i+= 3.141592654f/10.f)
				{
					exp[0].push_back(ClipperLib::IntPoint((int)(30.f*cosf(i))+tempVec.x,(int)(30.f*sinf(i))+tempVec.y));
				}

				ground.clipOff(exp);

			}

			if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Right){

				sf::Vector2f tempVec = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));

				Projectile* newProjectile = new Projectile(world,&destroyer,&window);

				newProjectile->setPosition(tempVec.x,tempVec.y);

				mainObjectList.push_back(newProjectile);

				//sfBall.setPosition(tempVec.x,tempVec.y);
			}

			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape){
				window.close();	
			}

			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::A){
				sf::View tempView(window.getView());
				tempView.move(-10.f,0.f);
				window.setView(tempView);
			}
			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::D){
				sf::View tempView(window.getView());
				tempView.move(10.f,0.f);
				window.setView(tempView);
			}
			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::W){
				sf::View tempView(window.getView());
				tempView.move(0.f,-10.f);
				window.setView(tempView);
			}
			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::S){
				sf::View tempView(window.getView());
				tempView.move(0.f,10.f);
				window.setView(tempView);
			}

			if (Event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, Event.size.width, Event.size.height);
				window.setView(sf::View(visibleArea));
			}

			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Q){
				sf::View tempView(window.getView());
				tempView.zoom(0.5f);
				window.setView(tempView);
			}
			if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Z){
				sf::View tempView(window.getView());
				tempView.zoom(1.5f);
				window.setView(tempView);
			}
		}
		window.clear();

		sf::RenderStates states;
		states.texture = &texture;

		for(auto it = mainObjectList.begin() ; it != mainObjectList.end() ; ++it){

			window.draw((**it),states);

		}

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_centerOfMassBit;

		debugDraw.SetFlags(flags);

		world->DrawDebugData();
		window.display();


		world->Step(1/30.f, 8, 3);

		for(auto it = mainObjectList.begin() ; it != mainObjectList.end() ; ++it){

			(**it).update();

		}

		destroyer.killAll();
	}


}

void ResetZoom(double zoom, double cx, double cy, double width, double height)
{
	double left = -width / zoom;
	double right = width / zoom;
	double bottom = -height / zoom;
	double top = height / zoom;

	// Reset viewport
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Reset ortho view
	glOrtho(left, right, bottom, top, 1, -1);
	glTranslatef(-cx, -cy, 0);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void Draw(const double zoom)
{
	/*
	// reset zoom
	Point center = Point(cx, cy);

	ResetZoom(zoom, center.x, center.y, 800, 600);

	for (int i = 0; i < triangles.size(); i++) {
	Triangle& t = *triangles[i];
	Point& a = *t.GetPoint(0);
	Point& b = *t.GetPoint(1);
	Point& c = *t.GetPoint(2);

	// Red
	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glVertex2f(c.x, c.y);
	glEnd();
	}
	/*
	// green
	glColor3f(0, 1, 0);

	for(int i = 0; i < polylines.size(); i++) {
	vector<Point*> poly = polylines[i];
	glBegin(GL_LINE_LOOP);
	for(int j = 0; j < poly.size(); j++) {
	glVertex2f(poly[j]->x, poly[j]->y);
	}
	glEnd();
	}

	*/
}

void DrawMap(const double zoom)
{
	/*
	// reset zoom
	Point center = Point(cx, cy);

	ResetZoom(zoom, center.x, center.y, 800, 600);

	list<Triangle*>::iterator it;
	for (it = map1.begin(); it != map1.end(); it++) {
	Triangle& t = **it;
	Point& a = *t.GetPoint(0);
	Point& b = *t.GetPoint(1);
	Point& c = *t.GetPoint(2);

	ConstrainedColor(t.constrained_edge[2]);
	glBegin(GL_LINES);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glEnd( );

	ConstrainedColor(t.constrained_edge[0]);
	glBegin(GL_LINES);
	glVertex2f(b.x, b.y);
	glVertex2f(c.x, c.y);
	glEnd( );

	ConstrainedColor(t.constrained_edge[1]);
	glBegin(GL_LINES);
	glVertex2f(c.x, c.y);
	glVertex2f(a.x, a.y);
	glEnd( );
	}
	*/
}

void ConstrainedColor(bool constrain)
{
	if (constrain) {
		// Green
		glColor3f(0, 1, 0);
	} else {
		// Red
		glColor3f(1, 0, 0);
	}
}

vector<Point*> CreateHeadHole() {

	vector<Point*> head_hole;
	/*
	head_hole.push_back(new Point(325, 437));
	head_hole.push_back(new Point(320, 423));
	head_hole.push_back(new Point(329, 413));
	head_hole.push_back(new Point(332, 423));
	*/
	return head_hole;
}

vector<Point*> CreateChestHole() {

	vector<Point*> chest_hole;
	/*
	chest_hole.push_back(new Point(320.72342,480));
	chest_hole.push_back(new Point(338.90617,465.96863));
	chest_hole.push_back(new Point(347.99754,480.61584));
	chest_hole.push_back(new Point(329.8148,510.41534));
	chest_hole.push_back(new Point(339.91632,480.11077));
	chest_hole.push_back(new Point(334.86556,478.09046));
	*/
	return chest_hole;

}



double StringToDouble(const std::string& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
}

double Fun(double x)
{
	return 2.5 + sin(10 * x) / x;
}

double Random(double (*fun)(double), double xmin = 0, double xmax = 1)
{
	static double (*Fun)(double) = NULL, YMin, YMax;
	static bool First = true;

	// Initialises random generator for first call
	if (First)
	{
		First = false;
		srand((unsigned) time(NULL));
	}

	// Evaluates maximum of function
	if (fun != Fun)
	{
		Fun = fun;
		YMin = 0, YMax = Fun(xmin);
		for (int iX = 1; iX < RAND_MAX; iX++)
		{
			double X = xmin + (xmax - xmin) * iX / RAND_MAX;
			double Y = Fun(X);
			YMax = Y > YMax ? Y : YMax;
		}
	}

	// Gets random values for X & Y
	double X = xmin + (xmax - xmin) * rand() / RAND_MAX;
	double Y = YMin + (YMax - YMin) * rand() / RAND_MAX;

	// Returns if valid and try again if not valid
	return Y < fun(X) ? X : Random(Fun, xmin, xmax);
}