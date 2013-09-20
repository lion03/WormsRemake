/**
\file	PlayState.cpp

\brief	Implements the play state class.
*/

#include "PlayState.h"
#include "ContatctListener.h"
#include "Team.h"
#include <SFML/OpenGL.hpp>
#include <sstream>
//PlayState PlayState::m_PlayState;

PlayState::PlayState(void):m_NumOfTeams(2)
{



}

/**
\brief	Finalizes an instance of the PlayState class.
*/

PlayState::~PlayState(void)
{



}

/**
\brief	Initialises this object.

\param [in,out]	game	If non-null, the game.
*/

void PlayState::Init(GameEngine* game)
{
	font.loadFromFile("ariblk.ttf");
	m_switchTeam = false;
	world = new b2World(b2Vec2(0.0,9.8));
	contactListener = new ContatctListener(world); // TODO: delete
	world->SetContactListener(contactListener);
	m_mainView.zoom(100.f);
	m_mainView.setCenter(13.66f,7.68f);
	destroyer = new ObjectDetroyer(&mainObjectList); // TODO: delete
	// = new Ground(world,destroyer);
	//worm = new Worm(world,destroyer);
	mainObjectList.push_back(new Ground(world,destroyer,&mainObjectList,m_GameMap)); // TODO: delete
	//mainObjectList.push_back();
	//Worm* temp = new Worm(world,destroyer,&mainObjectList, sf::Vector2f(900.f,1920/2-10.f));
	for (unsigned int i = 0; i < m_NumOfTeams; i++)
	{
		switch (i)
		{
		case 0:
			m_Teams.push_back(new Team(world,destroyer,&mainObjectList,8)); // TODO: delete in dtor
			m_TeamsHealth.push_back(sf::Text("",font));
			m_TeamsHealth.back().setPosition(30.f,30.f);
			break;
		case 1:
			m_Teams.push_back(new Team(world,destroyer,&mainObjectList,8,sf::Color::Red)); // TODO: delete in dtor
			m_TeamsHealth.push_back(sf::Text("",font));
			m_TeamsHealth.back().setColor(sf::Color::Red);
			m_TeamsHealth.back().setPosition(30.f,60.f);
			break;
		case 2:
			m_Teams.push_back(new Team(world,destroyer,&mainObjectList,8,sf::Color::Yellow)); // TODO: delete in dtor
			m_TeamsHealth.push_back(sf::Text("",font));
			m_TeamsHealth.back().setColor(sf::Color::Yellow);
			m_TeamsHealth.back().setPosition(30.f,90.f);
			break;
		case 3:
			m_Teams.push_back(new Team(world,destroyer,&mainObjectList,8,sf::Color::Green)); // TODO: delete in dtor
			m_TeamsHealth.push_back(sf::Text("",font));
			m_TeamsHealth.back().setColor(sf::Color::Green);
			m_TeamsHealth.back().setPosition(30.f,120.f);
			break;
		default:
			break;
		}
	}
	m_Teams.front()->setActive();
	//temp->setActive();
	//mainObjectList.push_back(temp);

	//m_Worms.push_back(temp);
	wormIterator = m_Worms.begin();

	m_MiniMap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	index = 0;
#ifdef _DEBUG
	debugDraw = new EEDebugDraw3();
	debugDraw->LinkTarget(*game->getWindow());
	world->SetDebugDraw(debugDraw);
#endif
	game->getWindow()->setActive();
}

/**
\brief	Updates the given game.

\param [in,out]	game	If non-null, the game.
*/

void PlayState::Update(GameEngine* game)
{

	//debugDraw->setWindow(game->getWindow());
	for(auto it = mainObjectList.begin() ; it != mainObjectList.end() ; ++it){

		(**it).update();

	}

	world->Step(1/60.f, 8, 3);
	int teamsAlive = 0;
	for (int i = 0; i < m_Teams.size(); i++)
	{

		std::stringstream ss;
		ss << m_Teams[i]->getTeamHealth();
		m_TeamsHealth[i].setString(ss.str());
		if(!m_Teams[i]->isDead())
			++teamsAlive;
	}

	bool suicide = m_Teams[index]->getSuicid();
	if((m_switchTeam || suicide)  && teamsAlive >1){
		disableCurrTeam();
		if((ProjectileCounter::getInstance().getLiveProjectileCount() == 0 && m_switchTeam) ||
			suicide){
			swichToNextTeam();

			setFocuseOnActiveWorm(*game->getWindow());
		}

	}
	else if(teamsAlive <=1)
	{
		game->Quit();
	}

	destroyer->killAll();


}

/**
\brief	Draws the given game.

\param [in,out]	game	If non-null, the game.
*/

void PlayState::Draw(GameEngine* game)
{


	sf::Transform transform;
	transform.scale(sf::Vector2f(100.f,100.f));
	sf::RenderStates states;
	states.transform = transform;
	//game->getWindow();
#ifdef _DEBUG
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;

	debugDraw->SetFlags(flags);
	world->DrawDebugData();
#endif
	for(auto it = mainObjectList.begin() ; it != mainObjectList.end() ; ++it){
		game->getWindow()->draw((**it),states);

	}


	sf::View CurrView(game->getWindow()->getView());

	m_ArsenalView.getSize();

	game->getWindow()->setView(game->getWindow()->getDefaultView());

	for (unsigned int i = 0; i < m_Teams.size(); i++){
		game->getWindow()->draw(*m_Teams.at(i));
		game->getWindow()->draw(m_TeamsHealth[i]);
	}

	game->getWindow()->setView(CurrView);


}

/**
\brief	Clean up.
*/

void PlayState::CleanUp(void)
{

	for (auto it = world->GetJointList(); it ; it = world->GetJointList())
	{
		world->DestroyJoint(it);
	}



	for (auto it = m_Teams.begin(); it != m_Teams.end() ; ++it)
	{
		delete *it;
	}

	/*
	for (auto it = world->GetBodyList(); it ; it = world->GetBodyList())
	{
	world->DestroyBody(it);
	}
	*/


	m_Teams.clear();


	while(!mainObjectList.empty())
	{
		auto it = mainObjectList.front();

		delete it;
		//mainObjectList.pop_front();


		//it = mainObjectList.erase(it);

	}

	delete contactListener;

	delete destroyer;

	delete world;
#ifdef _DEBUG
	delete debugDraw;
#endif
}

/**
\brief	Pauses this object.
*/

void PlayState::Pause(void)
{
}

/**
\brief	Resumes this object.
*/

void PlayState::Resume(void)
{
}

/**
\brief	Handles the events described by game.

\param [in,out]	game	If non-null, the game.
*/

void PlayState::HandleEvents(GameEngine*game)
{
	sf::Event Event;
	if( game->getWindow()->pollEvent(Event))
	{
		EventDispatcher::getInstance()->notifyAll(Event);

		if((Event.type == sf::Event::KeyPressed && Event.key.code  == sf::Keyboard::Escape))
			game->Quit();

		if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left){

			ClipperLib::Polygons exp(1);

			sf::RenderWindow window;

			sf::Vector2f tempVec = game->getWindow()->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*game->getWindow()).x,sf::Mouse::getPosition(*game->getWindow()).y));

			for (float i = 0.f; i < b2_pi*2.f; i+= b2_pi/10.f)
			{
				exp[0].push_back(ClipperLib::IntPoint((int)(30.f*cosf(i))+tempVec.x,(int)(30.f*sinf(i))+tempVec.y));
			}

			//ground->clipOff(exp);

		}

		if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Right){

			sf::Vector2f tempVec = game->getWindow()->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*game->getWindow()).x,sf::Mouse::getPosition(*game->getWindow()).y));

			//sf::Vector2f tempVec(sf::Mouse::getPosition(*game->getWindow()).x,sf::Mouse::getPosition(*game->getWindow()).y);

			Projectile* newProjectile = new Projectile(world,destroyer,&mainObjectList,1.f);

			newProjectile->setPosition(tempVec.x,tempVec.y);

			mainObjectList.push_back(newProjectile);

			//sfBall.setPosition(tempVec.x,tempVec.y);
		}

		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape){
			game->Quit();
		}

		if(Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Space){

			m_switchTeam = true;

		}

		if(Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Tab){

			setFocuseOnActiveWorm(*game->getWindow());

		}

		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::A){
			sf::View tempView(game->getWindow()->getView());
			tempView.move(-10.f,0.f);
			game->getWindow()->setView(tempView);
		}
		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::D){
			sf::View tempView(game->getWindow()->getView());
			tempView.move(10.f,0.f);
			game->getWindow()->setView(tempView);
		}
		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::W){
			sf::View tempView(game->getWindow()->getView());
			tempView.move(0.f,-10.f);
			game->getWindow()->setView(tempView);
		}
		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::S){
			sf::View tempView(game->getWindow()->getView());
			tempView.move(0.f,10.f);
			game->getWindow()->setView(tempView);
		}

		if (Event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, Event.size.width, Event.size.height);
			game->getWindow()->setView(sf::View(visibleArea));
		}

		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Q){
			sf::View tempView(game->getWindow()->getView());
			tempView.zoom(0.5f);
			game->getWindow()->setView(tempView);
		}
		if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Z){
			sf::View tempView(game->getWindow()->getView());
			tempView.zoom(1.5f);
			game->getWindow()->setView(tempView);
		}
	}
}

/**
\brief	Sets focuse on active worm.
*/

void PlayState::setFocuseOnActiveWorm(sf::RenderTarget &target)
{
	sf::View currView(target.getView());

	if(m_Teams[index]->getActiveWorm()){
		b2Vec2 wormPos = m_Teams[index]->getActiveWorm()->getBodyPos();

		currView.setCenter(SCALE_UP(wormPos.x),SCALE_UP(wormPos.y));
		//currView.zoom(1.f);

		target.setView(currView);
	}
}

/**
\brief	Swich to next team.
*/

void PlayState::swichToNextTeam(void)
{
	do
	{
		++index;
		if(index >= m_Teams.size())
			index = 0;
	}while (m_Teams[index]->isDead());

	m_Teams[index]->setActive();

	m_switchTeam = false;


}

/**
\brief	Disables the curr team.
*/

void PlayState::disableCurrTeam(void)
{
	m_Teams[index]->setActive(false);

}

