#pragma once
#include <vector>
#include <list>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "External/poly2tri/poly2tri.h"
#include "Ground.h"
#include "External/Clipper/clipper.hpp"
#include "ObjectDetroyer.h"
#include "Worm.h"
#include "External/TinyXML/tinyxml.h"
#include "Render.h"
#include "gamestate.h"
#include "Projectile.h"
#include <Box2D/Box2D.h>
#include "External/spine/Animation.h"
#include "External/spine/AnimationState.h"
#include "External/spine/AnimationStateData.h"
#include "External/spine/Atlas.h"
#include "External/spine/AtlasAttachmentLoader.h"
#include "External/spine/Attachment.h"
#include "External/spine/AttachmentLoader.h"
#include "External/spine/Bone.h"
#include "External/spine/BoneData.h"
#include "External/spine/RegionAttachment.h"
#include "External/spine/Skeleton.h"
#include "External/spine/SkeletonData.h"
#include "External/spine/SkeletonJson.h"
#include "External/spine/Skin.h"
#include "External/spine/Slot.h"
#include "External/spine/SlotData.h"
#include "External/spine/spine-sfml.h"
#include "Arsenal.h"
#include "MapLoader.h"
#include "ProjectileCounter.h"

class ContatctListener;

/**
 \brief	Play state.

 \sa	GameState
 */

class PlayState : public GameState
{
public:

	/**
	 \brief	Initialises this object.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void Init(GameEngine* game);

	/**
	 \brief	Updates the given game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void Update(GameEngine* game);

	/**
	 \brief	Draws the given game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void Draw(GameEngine* game);

	/**
	 \brief	Handles the events described by game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void HandleEvents(GameEngine* game);

	/**
	 \brief	Clean up.
	 */

	void CleanUp(void);

	/**
	 \brief	Pauses this object.
	 */

	void Pause(void);

	/**
	 \brief	Resumes this object.
	 */

	void Resume(void);

	/**
	 \brief	Finalizes an instance of the PlayState class.
	 */

	virtual ~PlayState(void);

	/**
	 \brief	Gets the instence.
	
	 \return	The instence.
	 */

	static PlayState& getInstence(void){
		static PlayState m_PlayState;
		return m_PlayState;
	}

	virtual void setNumOfPlayers(unsigned int num){m_NumOfTeams = num;}

	virtual void setMap(const MapLoader::GameMap& map){m_GameMap = map;}

private:

	/**
	 \brief	Initializes a new instance of the PlayState class.
	 */

	PlayState(void);

	void setFocuseOnActiveWorm(sf::RenderTarget &target);

	void disableCurrTeam(void);

	void swichToNextTeam(void);

	//static PlayState m_PlayState;
	b2World *world; ///< The world
	//Loader loader;
	ContatctListener* contactListener;  ///< The contact listener
	std::list<GameObject* >mainObjectList;	///< List of main objects
	EEDebugDraw3* debugDraw;	///< The debug draw
	Ground* ground; ///< The ground
	ObjectDetroyer* destroyer;  ///< The destroyer
	Worm* worm; ///< The worm
	sf::View m_MiniMap; ///< The mini map
	sf::View m_mainView;
	sf::View m_ArsenalView; ///< The arsenal view
	std::vector<Worm*> m_Worms; ///< The worms
	unsigned int index;  ///< Zero-based index of the 
	std::vector<Worm*>::iterator wormIterator;
	std::vector<Team*> m_Teams; ///< The teams

	Worm* m_ActiveWorm; ///< The active worm

	sf::Sprite m_BackGround;

	MapLoader::GameMap m_GameMap;

	unsigned int m_NumOfTeams;

	bool m_switchTeam;

	b2Vec2 m_ActiveWormPos;

	std::vector<sf::Text> m_TeamsHealth;

	sf::Font font;  ///< The font

};

/**
// End of PlayState.h
 */

