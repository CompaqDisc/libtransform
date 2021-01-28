#include <catch2/catch.hpp>
#include <transform/vector.hh>

SCENARIO( "[Vector2] Vector members can be modified by members x and y, in addition to the array operator.", "[Vector2]" )
{
	GIVEN( "A Vector2, initialized to zero." )
	{
		transform::Vector2i v = transform::Vector2i().zero();

		REQUIRE( v.x == 0 );
		REQUIRE( v.y == 0 );

		WHEN( "x and y are changed" ) {
			v.x = 2;
			v.y = 3;

			THEN( "the change is reflected in the array operator" ) {
				REQUIRE( v[0] == 2 );
				REQUIRE( v[1] == 3 );
			}
		}

		WHEN( "the array is modified" ) {
			v[0] = 2;
			v[1] = 3;

			THEN( "the change is reflected in the member variables x and y" ) {
				REQUIRE( v.x == 2 );
				REQUIRE( v.y == 3 );
			}
		}
	}
}

SCENARIO( "[Vector2] Vector math functions return approriate values.", "[Vector2]" )
{
	GIVEN( "A pair of Vector2, initialized to {1,2}, and {3,4} respectively." )
	{
		transform::Vector2f a = transform::Vector2f(1,2);
		transform::Vector2f b = transform::Vector2f(3,4);

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 2 );

		REQUIRE( b.x == 3 );
		REQUIRE( b.y == 4 );

		WHEN( "the dot product is calculated" ) {
			THEN( "the result is 11" ) {
				REQUIRE( a.dot(b) == 11 );
			}
		}

		WHEN( "the magnitude of b is calculated" ) {
			THEN( "the result is 5" ) {
				REQUIRE( b.mag() == 5 );
			}
		}

		WHEN( "the projection is calculated" ) {
			auto proj = a.project(b);

			THEN( "the result is approximately {1.32,1.76}" ) {
				REQUIRE( proj.x == Approx( 1.32f ) );
				REQUIRE( proj.y == Approx( 1.76f ) );
			}
		}

		WHEN( "the rejection is calculated" ) {
			auto proj = a.reject(b);

			THEN( "the result is approximately {-0.34,0.24}" ) {
				REQUIRE( proj.x == Approx( -0.32f ) );
				REQUIRE( proj.y == Approx(  0.24f ) );
			}
		}
	}
}

SCENARIO( "[Vector2] Vector comparison functions return approriately.", "[Vector2]" )
{
	GIVEN( "A pair of Vector2, both initialized to {2,4}" )
	{
		transform::Vector2i a = transform::Vector2i(2, 4);
		transform::Vector2i b = a;

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

	GIVEN( "A pair of Vector2, initialized to {1,2} and {3,4} respectively." )
	{
		transform::Vector2f a = transform::Vector2f(1,2);
		transform::Vector2f b = transform::Vector2f(3,4);

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 2 );

		REQUIRE( b.x == 3 );
		REQUIRE( b.y == 4 );

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
			transform::Vector2i gt = transform::Vector2i(a > b);
			bool result = (gt == transform::Vector2f(0, 0));

			THEN( "a is not greater than b" ) {
				REQUIRE( result );
			}
		}
	}
}