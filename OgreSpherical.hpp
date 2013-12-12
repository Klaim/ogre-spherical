#ifndef HGUARD_OGRE_SPHERICAL_HPP__
#define HGUARD_OGRE_SPHERICAL_HPP__

#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace Ogre {
	
	/** Spherical coordinates vector, used for spherical coordinates and transformations. 
		Some example values:
			( radius = 1.0, theta = 0.0deg  , phi = 0.0deg  ) <=> Y unit vector in cartesian space
			( radius = 1.0, theta = 90.0deg , phi = 0.0deg  ) <=> Z unit vector in cartesian space
			( radius = 1.0, theta = 90.0deg , phi = 90.0deg ) <=> X unit vector in cartesian space
	*/
	struct SphereVector
	{
		Real   radius; ///< Rho or Radius is the distance from the center of the sphere.
		Radian theta;  ///< Theta is the angle around the x axis (latitude angle counterclockwise), values range from 0 to PI.
		Radian phi;    ///< Phi is the angle around the y axis (longitude angle counterclockwise), values range from 0 to 2PI.
		
		// NOTE: if you need to expose these constants through a shared library api, add the export/import macro before each of 
		// the following lines.
		static const SphereVector ZERO;
		static const SphereVector UNIT_X;
		static const SphereVector UNIT_Y;
		static const SphereVector UNIT_Z;
		static const SphereVector NEGATIVE_UNIT_X;
		static const SphereVector NEGATIVE_UNIT_Y;
		static const SphereVector NEGATIVE_UNIT_Z;

		/// Default Constructor: no initialization of the values is performed.
		SphereVector() {} 
		
		SphereVector( Real radius, Radian theta, Radian phi )
			: radius( std::move(radius) ), theta( std::move(theta) ), phi( std::move(phi) )
		{}

		/** Construction from a cartesian vector: the spherical vector will have the same relative position
			but in spherical coordinates.
			@see from_cartesian()
		*/
		explicit SphereVector( const Vector3& cartesian_vec )
		{
			*this = from_cartesian( cartesian_vec );
		}


		/** @return a relative Cartesian vector coordinate from this relative spherical coordinate. */
		Vector3 to_cartesian() const
		{
			Vector3 result;
			result.x = radius * Math::Cos( phi ) * Math::Sin( theta );
			result.z = radius * Math::Sin( phi ) * Math::Sin( theta );
			result.y = radius * Math::Cos( theta );
			return result;
		}

		/** @return a relative spherical coordinate from a cartesian vector. */
		/** @return a relative spherical coordinate from a cartesian vector. */
		static SphereVector from_cartesian( const Ogre::Vector3& cartesian )
		{
			SphereVector result = SphereVector::ZERO;
			result.radius = cartesian.length();
			if( result.radius == 0 )
				return result;
			result.phi    = Math::ATan2( cartesian.x, cartesian.z );
			result.theta  = Math::ATan2( Math::Sqrt( Math::Sqr( cartesian.x ) + Math::Sqr( cartesian.z ) ), cartesian.y );
			return result;
		}

		/** @return a relative rotation from the provided axis to the axis corresponding to this relative spherical vector. */
		Quaternion rotation_from( const Vector3& axis ) const
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
		friend SphereVector operator*( const SphereVector& sv, const Quaternion& rotation )
		{
			auto cartesian = sv.to_cartesian();
			cartesian = rotation * cartesian;
			return SphereVector::from_cartesian( cartesian );
		}

		/// Rotation of the position around the relative center of the sphere.
		friend SphereVector operator*( const Quaternion& rotation, const SphereVector& sv ) { return sv * rotation; }

		/// Rotation of the position around the relative center of the sphere.
		SphereVector& operator*=( const Quaternion& rotation ) 
		{
			*this = *this * rotation;
			return *this;
		}
		
		friend bool operator==( const SphereVector& left, const SphereVector& right )
		{
			return left.radius == right.radius
				&& left.phi == right.phi
				&& left.theta == right.theta
				;
		}

		friend bool operator!=( const SphereVector& left, const SphereVector& right )
		{
			return !( left == right );
		}


	};
	
}


#endif
