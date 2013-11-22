#ifndef HGUARD_NETRUSH_ZONEVIEW_SPHERICAL_HPP__
#define HGUARD_NETRUSH_ZONEVIEW_SPHERICAL_HPP__

#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>

#include "api.hpp"

namespace netrush {
namespace zoneview {
	
	/** Spherical coordinates vector, used for spherical coordinates and transformations. 
		Some example values:
			( radius = 1.0, theta = 0.0deg , phi = 0.0deg  ) <=> Y unit vector in cartesian space
			( radius = 1.0, theta = 90.0deg, phi = 0.0deg  ) <=> Z unit vector in cartesian space
			( radius = 1.0, theta = 90.0deg , phi = 90.0deg ) <=> X unit vector in cartesian space
	*/
	struct SphereVector
	{
		Ogre::Real   radius; ///< Rho or Radius is the distance from the center of the sphere.
		Ogre::Radian theta;	 ///< Theta is the angle around the x axis (latitude angle counterclockwise), values range from 0 to PI.
		Ogre::Radian phi;    ///< Phi is the angle around the y axis (longitude angle counterclockwise), values range from 0 to 2PI.
		
		NETRUSH_ZONEVIEW_API static const SphereVector ZERO;
		NETRUSH_ZONEVIEW_API static const SphereVector UNIT_X;
		NETRUSH_ZONEVIEW_API static const SphereVector UNIT_Y;
		NETRUSH_ZONEVIEW_API static const SphereVector UNIT_Z;
		NETRUSH_ZONEVIEW_API static const SphereVector NEGATIVE_UNIT_X;
		NETRUSH_ZONEVIEW_API static const SphereVector NEGATIVE_UNIT_Y;
		NETRUSH_ZONEVIEW_API static const SphereVector NEGATIVE_UNIT_Z;

		SphereVector() = default;
		SphereVector( Ogre::Real radius, Ogre::Radian theta, Ogre::Radian phi )
			: radius( std::move(radius) ), theta( std::move(theta) ), phi( std::move(phi) )
		{}

		explicit SphereVector( const Ogre::Vector3& cartesian_vec )
		{
			*this = from_cartesian( cartesian_vec );
		}


		/** @return a relative Cartesian vector coordinate from this relative spherical coordinate. */
		Ogre::Vector3 to_cartesian() const
		{
			Ogre::Vector3 result;
			result.x = radius * Ogre::Math::Cos( phi ) * Ogre::Math::Sin( theta );
			result.z = radius * Ogre::Math::Sin( phi ) * Ogre::Math::Sin( theta );
			result.y = radius * Ogre::Math::Cos( theta );
			return result;
		}

		/** @return a relative spherical coordinate from a cartesian vector. */
		static SphereVector from_cartesian( const Ogre::Vector3& cartesian )
		{
			SphereVector result;
			result.radius = cartesian.length();
			result.phi = Ogre::Math::ATan( cartesian.z / cartesian.x );
			result.theta = Ogre::Math::ACos( cartesian.y / result.radius );
			return result;
		}

		/** @return a relative rotation from the provided axis to the axis corresponding to this relative spherical vector. */
		Ogre::Quaternion rotation_from( const Ogre::Vector3& axis ) const
		{
			const auto relative_direction = to_cartesian();
			return axis.getRotationTo( relative_direction );
		}

		friend SphereVector operator-( const SphereVector& value ) 
		{
			SphereVector result;
			result.radius = -value.radius;
			result.theta  = -value.theta;
			result.phi    = -value.phi;
			return result; 
		}

		friend SphereVector operator+( const SphereVector& left, const SphereVector& right )
		{ 
			SphereVector result;
			result.radius = left.radius + right.radius;
			result.theta  = left.theta + right.theta;
			result.phi    = left.phi + right.phi; 
			return result;
		}

		friend SphereVector operator-( const SphereVector& left, const SphereVector& right )
		{ 
			return left + (-right); 
		}
		
		SphereVector& operator+=( const SphereVector& other )
		{ 
			*this = *this + other;
			return *this;
		}

		SphereVector& operator-=( const SphereVector& other )
		{
			*this = *this - other;
			return *this;
		}

		/// Rotation of the position around the relative center of the sphere.
		friend SphereVector operator*( const SphereVector& sv, const Ogre::Quaternion& rotation )
		{
			auto cartesian = sv.to_cartesian();
			cartesian = rotation * cartesian;
			return SphereVector::from_cartesian( cartesian );
		}

		/// Rotation of the position around the relative center of the sphere.
		friend SphereVector operator*( const Ogre::Quaternion& rotation, const SphereVector& sv ) { return sv * rotation; }

		/// Rotation of the position around the relative center of the sphere.
		SphereVector& operator*=( const Ogre::Quaternion& rotation ) 
		{
			*this = *this * rotation;
			return *this;
		}


	};
	
}}


#endif
