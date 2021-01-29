#include <catch2/catch.hpp>
#include "transform/vector.hh"

SCENARIO( "[Vector3] Vector members can be modified by members x, y, and z, in addition to the array operator.", "[Vector3]" )
{
	GIVEN( "A Vector3, initialized to zero." )
	{
		transform::Vector3i v = transform::Vector3i().zero();

		REQUIRE( v.x == 0 );
		REQUIRE( v.y == 0 );
		REQUIRE( v.z == 0 );

		WHEN( "x and y are changed" ) {
			v.x = 2;
			v.y = 3;
			v.z = 4;

			THEN( "the change is reflected in the array operator" ) {
				REQUIRE( v[0] == 2 );
				REQUIRE( v[1] == 3 );
				REQUIRE( v[2] == 4 );
			}
		}

		WHEN( "the array is modified" ) {
			v[0] = 2;
			v[1] = 3;
			v[2] = 4;

			THEN( "the change is reflected in the member variables" ) {
				REQUIRE( v.x == 2 );
				REQUIRE( v.y == 3 );
				REQUIRE( v.z == 4 );
			}
		}
	}
}

SCENARIO( "[Vector3] Vector math functions return approriate values.", "[Vector3]" )
{
	GIVEN( "A pair of Vector3, initialized to {1,2}, and {3,4} respectively." )
	{
		transform::Vector3f a = transform::Vector3f(1,2,3);
		transform::Vector3f b = transform::Vector3f(4,5,6);

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 2 );
		REQUIRE( a.z == 3 );

		REQUIRE( b.x == 4 );
		REQUIRE( b.y == 5 );
		REQUIRE( b.z == 6 );

		WHEN( "the dot product is calculated" ) {
			THEN( "the result is 32" ) {
				REQUIRE( a.dot(b) == 32 );
			}
		}

		WHEN( "the magnitude of b is calculated" ) {
			THEN( "the result is approximately 8.775" ) {
				REQUIRE( b.mag() == Approx( 8.77496f ));
			}
		}

		WHEN( "the projection is calculated" ) {
			transform::Vector3f proj = a.project(b);

			THEN( "the result is approximately {1.66,2.08}" ) {
				REQUIRE( proj.x == Approx( 1.66234f ) );
				REQUIRE( proj.y == Approx( 2.07792f ) );
			}
		}

		WHEN( "the rejection is calculated" ) {
			transform::Vector3f proj = a.reject(b);

			THEN( "the result is approximately {-0.66,-0.08}" ) {
				REQUIRE( proj.x == Approx( -0.66234f ) );
				REQUIRE( proj.y == Approx( -0.07792f ).epsilon(0.0001) );
			}
		}
	}
}

SCENARIO( "[Vector3] Vector comparison functions return approriately.", "[Vector3]" )
{
	GIVEN( "A pair of Vector3, both initialized to {2,4,6}" )
	{
		transform::Vector3i a = transform::Vector3i(2, 4, 6);
		transform::Vector3i b = a;

		WHEN( "compared for equality" ) {
			bool equal = (a == b);
			THEN( "they are shown as equal" ) {
				REQUIRE( equal );
			}
		}

		WHEN( "compared for inequality" ) {
			bool inequal = (a != b);
			THEN( "they are shown to be equal" ) {
				REQUIRE( !inequal );
			}
		}
	}

	GIVEN( "A pair of Vector3, initialized to {1,2,3} and {4,5,6} respectively." )
	{
		transform::Vector3f a = transform::Vector3f(1,2,3);
		transform::Vector3f b = transform::Vector3f(4,5,6);

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 2 );
		REQUIRE( a.z == 3 );

		REQUIRE( b.x == 4 );
		REQUIRE( b.y == 5 );
		REQUIRE( b.z == 6 );

		WHEN( "compared for equality" ) {
			bool equal = (a == b);
			THEN( "they are shown to be not equal" ) {
				REQUIRE( !equal );
			}
		}

		WHEN( "compared for inequality" ) {
			bool inequal = (a != b);
			THEN( "they are shown to be not equal" ) {
				REQUIRE( inequal );
			}
		}

		WHEN( "a is compared to b" ) {
			transform::Vector3b gt = transform::Vector3b(a > b);
			bool result = (gt == transform::Vector3b(0, 0, 0));

			THEN( "a is not greater than b" ) {
				REQUIRE( result );
			}
		}
	}
}
