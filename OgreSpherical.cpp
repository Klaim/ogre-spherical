#include "spherical.hpp"


namespace netrush {
namespace zoneview {

	const SphereVector SphereVector::ZERO( 0.f, Ogre::Radian( 0.f ), Ogre::Radian( 0.f ) );
	const SphereVector SphereVector::UNIT_X( Ogre::Vector3::UNIT_X );
	const SphereVector SphereVector::UNIT_Y( Ogre::Vector3::UNIT_Y );
	const SphereVector SphereVector::UNIT_Z( Ogre::Vector3::UNIT_Z );
	const SphereVector SphereVector::NEGATIVE_UNIT_X( Ogre::Vector3::NEGATIVE_UNIT_X );
	const SphereVector SphereVector::NEGATIVE_UNIT_Y( Ogre::Vector3::NEGATIVE_UNIT_Y );
	const SphereVector SphereVector::NEGATIVE_UNIT_Z( Ogre::Vector3::NEGATIVE_UNIT_Z );

}}