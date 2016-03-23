#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <Box2D/Dynamics/b2World.h>
#include <memory>
#include <vector>

namespace game
{
	class GameObject;

	/*! \class GameWorld
		\brief Main class for the game world.
		\details
		\todo separate interface and implementation here!
	*/
	class GameWorld
	{
	public:
		void step( float dt );
	private:
		/// remove all game objects that are no longer considered alive from the object list.
		void clear_objects();

		std::unique_ptr<b2World> mPhysicWorld;
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
	};
}

#endif // GAMEWORLD_H_INCLUDED
