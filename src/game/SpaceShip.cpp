#include "SpaceShip.h"
#include "ShipStructure.h"
#include "FlightModel.h"
#include "Components/ActionList.h"
#include "Components/IComponent.h"

namespace game
{
	using namespace std::placeholders;
	SpaceShip::SpaceShip(b2Body* body) : GameObject(body),
							mStructure( make_unique<ShipStructure>() ),
							mFlightModel( make_unique<FlightModel>() ),
							mStepListener( addStepListener(std::bind(onShipStep, this)) ),
							mImpactListener( addImpactListener(std::bind(onShipImpact, this, _1, _2)) )
	{
		// init
		mStructure->foreachComponent([this](IComponent& c){ this->addPropertyObject(c.name(), &c); });
	}

	SpaceShip::~SpaceShip()
	{

	}

	void SpaceShip::processActions(ActionList& actions)
	{
		// now act based on the generated actions
		actions.act( *mFlightModel );
		mStructure->foreachComponent([](IComponent& cmp, ActionList& al){ al.act(cmp); }, std::ref(actions));
	}

	void SpaceShip::onShipStep()
	{
		ActionList lst;
		mStructure->update(lst);

		processActions(lst);

		mFlightModel->update_movement( *mBody );
	}

	void SpaceShip::onShipImpact(GameObject* other, const ImpactInfo& info)
	{
		/// \todo sophisticated damage behaviour
		Damage damage(DamageType::BLUNT, info.impulse * 0.0008);
		mStructure->hit(damage, info.position, -info.normal);
	}
}
