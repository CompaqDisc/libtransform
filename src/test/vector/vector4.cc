#include <catch2/catch.hpp>
#include "transform/vector.hh"

SCENARIO( "[Vector4] Vector members can be modified by members x, y, and z, in addition to the array operator.", "[Vector4]" )
{
	GIVEN( "A Vector4, initialized to zero." )
	{
		transform::Vector4i v = transform::Vector4i().zero();

		REQUIRE( v.x == 0 );
		REQUIRE( v.y == 0 );
		REQUIRE( v.z == 0 );
		REQUIRE( v.w == 0 );

		WHEN( "x and y are changed" ) {
			v.x = 2;
			v.y = 3;
			v.z = 4;
			v.w = 5;

			THEN( "the change is reflected in the array operator" ) {
				REQUIRE( v[0] == 2 );
				REQUIRE( v[1] == 3 );
				REQUIRE( v[2] == 4 );
				REQUIRE( v[3] == 5 );
			}
		}

		WHEN( "the array is modified" ) {
			v[0] = 2;
			v[1] = 3;
			v[2] = 4;
			v[3] = 5;

			THEN( "the change is reflected in the member variables" ) {
				REQUIRE( v.x == 2 );
				REQUIRE( v.y == 3 );
				REQUIRE( v.z == 4 );
				REQUIRE( v.w == 5 );
			}
		}
	}
}

SCENARIO( "[Vector4] Vector math functions return approriate values.", "[Vector4]" )
{
	GIVEN( "A pair of Vector4, initialized to {1,2,3,4}, and {5,6,7,8} respectively." )
	{
		transform::Vector4f a = transform::Vector4f(1,2,3,4);
		transform::Vector4f b = transform::Vector4f(5,6,7,8);

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 2 );
		REQUIRE( a.z == 3 );
		REQUIRE( a.w == 4 );

		REQUIRE( b.x == 5 );
		REQUIRE( b.y == 6 );
		REQUIRE( b.z == 7 );
		REQUIRE( b.w == 8 );

		WHEN( "the dot product is calculated" ) {
			THEN( "the result is 70" ) {
				REQUIRE( a.dot(b) == 70 );
			}
		}

		WHEN( "the magnitude of b is calculated" ) {
			THEN( "the result is approximately 13.191" ) {
				REQUIRE( b.mag() == Approx( 13.190905958f ));
			}
		}

		WHEN( "the projection is calculated" ) {
			transform::Vector4f proj = a.project(b);

			THEN( "the result is approximately {2.01,2.41}" ) {
				REQUIRE( proj.x == Approx( 2.01149f ) );
				REQUIRE( proj.y == Approx( 2.41379f ) );
			}
		}

		WHEN( "the rejection is calculated" ) {
			transform::Vector4f proj = a.reject(b);

			THEN( "the result is approximately {-1.01,-0.41}" ) {
				REQUIRE( proj.x == Approx( -1.01149f ) );
				REQUIRE( proj.y == Approx( -0.41379f ) );
			}
		}
	}
}

SCENARIO( "[Vector4] Vector comparison functions return approriately.", "[Vector4]" )
{
	GIVEN( "A pair of Vector4, both initialized to {2,4,6,8}" )
	{
		transform::Vector4i a = transform::Vector4i(2, 4, 6, 8);
		transform::Vector4i b = a;

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

	GIVEN( "A pair of Vector4, initialized to {1,2,3,4} and {5,6,7,8} respectively." )
	{
		transform::Vector4f a = transform::Vector4f(1,2,3,4);
		transform::Vector4f b = transform::Vector4f(5,6,7,8);

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 2 );
		REQUIRE( a.z == 3 );
		REQUIRE( a.w == 4 );

		REQUIRE( b.x == 5 );
		REQUIRE( b.y == 6 );
		REQUIRE( b.z == 7 );
		REQUIRE( b.w == 8 );

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
			transform::Vector4b gt = transform::Vector4b(a > b);
			bool result = (gt == transform::Vector4b(0, 0, 0, 0));

			THEN( "a is not greater than b" ) {
				REQUIRE( result );
			}
		}
	}
}
