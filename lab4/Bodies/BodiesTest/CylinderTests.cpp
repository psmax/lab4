#include "stdafx.h"
#include "../Bodies/Cylinder.h"

static const double EXPECTED_RADIUS = 9;
static const double EXPECTED_HEIGHT = 4.5;
static const double EXPECTED_DENSITY = 25000;

struct Cylinder_fixture
{
	CCylinder cylinder;

	Cylinder_fixture()
		: cylinder(EXPECTED_RADIUS, EXPECTED_HEIGHT, EXPECTED_DENSITY)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Cylinder, Cylinder_fixture)

BOOST_AUTO_TEST_CASE(Has_dimensions)
{
	BOOST_CHECK_EQUAL(cylinder.GetHeight(), EXPECTED_HEIGHT);
	BOOST_CHECK_EQUAL(cylinder.GetRadius(), EXPECTED_RADIUS);
}

BOOST_AUTO_TEST_CASE(Has_density)
{
	BOOST_CHECK_EQUAL(cylinder.GetDensity(), EXPECTED_DENSITY);
}

BOOST_AUTO_TEST_CASE(Has_volume)
{
	const double EXPECTED_VOLUME = (M_PI * EXPECTED_RADIUS * EXPECTED_RADIUS) *
		EXPECTED_HEIGHT;
	BOOST_CHECK_EQUAL(cylinder.GetVolume(), EXPECTED_VOLUME);

	CBody &cylinderAsBody = cylinder;
	BOOST_CHECK_EQUAL(cylinderAsBody.GetVolume(), EXPECTED_VOLUME);
}

BOOST_AUTO_TEST_CASE(Has_mass)
{
	const double EXPECTED_MASS = cylinder.GetVolume() * cylinder.GetDensity();
	BOOST_CHECK_EQUAL(cylinder.GetMass(), EXPECTED_MASS);
}

BOOST_AUTO_TEST_CASE(Has_info)
{
	const std::string info = cylinder.GetInformation();
	std::ostringstream expectedInfo;

	expectedInfo << "Cylinder with base radius " << cylinder.GetRadius();
	expectedInfo << ", height " << cylinder.GetHeight();
	expectedInfo << " and density " << cylinder.GetDensity();

	BOOST_CHECK_EQUAL(expectedInfo.str(), info);
}

BOOST_AUTO_TEST_SUITE_END()
