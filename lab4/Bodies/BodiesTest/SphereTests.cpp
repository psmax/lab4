#include "stdafx.h"
#include "../Bodies/Sphere.h"

/* —фера
	имеет радиус
	имеет объем
	имеет плотность
*/

static const double EXPECTED_RADIUS = 3.5;
static const double EXPECTED_DENSITY = 8920;

struct Sphere_fixture
{
	CSphere sphere;

	Sphere_fixture()
		:sphere(EXPECTED_RADIUS, EXPECTED_DENSITY)

	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Sphere, Sphere_fixture)

BOOST_AUTO_TEST_CASE(Has_radius)
{
	BOOST_CHECK_EQUAL(sphere.GetRadius(), EXPECTED_RADIUS);
}

BOOST_AUTO_TEST_CASE(Has_volume)
{
	const double EXPECTED_VOLUME = 4 * M_PI / 3 * pow(EXPECTED_RADIUS, 3);
	BOOST_CHECK_EQUAL(sphere.GetVolume(), EXPECTED_VOLUME);
	CBody & sphereAsBody = sphere;
	BOOST_CHECK_EQUAL(sphereAsBody.GetVolume(), EXPECTED_VOLUME);
}

BOOST_AUTO_TEST_CASE(Has_density)
{
	BOOST_CHECK_EQUAL(sphere.GetDensity(), EXPECTED_DENSITY);
}

BOOST_AUTO_TEST_CASE(Has_weight)
{
	const double EXPECTED_WEIGHT = sphere.GetVolume() * sphere.GetDensity();
	BOOST_CHECK_EQUAL(sphere.GetMass(), EXPECTED_WEIGHT);
}

BOOST_AUTO_TEST_CASE(Has_info)
{
	const std::string info = sphere.GetInformation();
	std::ostringstream expectedInfo;

	expectedInfo << "Sphere with radius " << sphere.GetRadius();
	expectedInfo << " and density " << sphere.GetDensity();

	BOOST_CHECK_EQUAL(expectedInfo.str(), info);
}

BOOST_AUTO_TEST_SUITE_END()
