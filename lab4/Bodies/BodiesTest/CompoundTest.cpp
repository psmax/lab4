#include "stdafx.h"
#include <memory>
#include "../Bodies/Compound.h"

#include "../Bodies/Sphere.h"
#include "../Bodies/Cone.h"
#include "../Bodies/Cylinder.h"
#include "../Bodies/Parallelepiped.h"

using namespace std;

struct Compound_fixture
{
	CCompound comp;

	CSphere sphere;
	CCone cone;
	CCylinder cylinder;
	CParallelepiped par;

	Compound_fixture()
		: sphere(10, 5), cone(10, 15, 60), cylinder(10, 15, 30), par(10, 15, 20, 50)
	{
		comp.AddBody(make_shared<CSphere>(sphere));
		comp.AddBody(make_shared<CCone>(cone));
		comp.AddBody(make_shared<CCylinder>(cylinder));
		comp.AddBody(make_shared<CParallelepiped>(par));
	}
};

BOOST_FIXTURE_TEST_SUITE(Compound, Compound_fixture)

BOOST_AUTO_TEST_CASE(Has_volume)
{
	double volume = comp.GetVolume();
	double expectedVolume = sphere.GetVolume() + cone.GetVolume() + cylinder.GetVolume() + par.GetVolume();
	BOOST_CHECK_EQUAL(volume, expectedVolume);
}

BOOST_AUTO_TEST_CASE(Has_mass)
{
	double mass = comp.GetMass();
	double expectedMass = sphere.GetMass() + cone.GetMass() + cylinder.GetMass() + par.GetMass();
	BOOST_CHECK_EQUAL(mass, expectedMass);
}

BOOST_AUTO_TEST_CASE(Has_density)
{
	double density = comp.GetDensity();
	double expectedVolume = sphere.GetVolume() + cone.GetVolume() + cylinder.GetVolume() + par.GetVolume();
	double expectedMass = sphere.GetMass() + cone.GetMass() + cylinder.GetMass() + par.GetMass();
	double expectedDensity = expectedMass / expectedVolume;
	BOOST_CHECK_EQUAL(density, expectedDensity);
}

BOOST_AUTO_TEST_CASE(Has_information)
{
	const std::string info = comp.GetInformation();
	std::ostringstream expectedInfo;

	expectedInfo << "Compound body composed of " << comp.GetContentsCount() << " bodies" << endl;
	expectedInfo << "With mass " << comp.GetMass();
	expectedInfo << ", volume " << comp.GetVolume();
	expectedInfo << " and density " << comp.GetDensity() << endl;
	expectedInfo << "Contents:" << endl;
	expectedInfo << sphere.GetInformation() << endl;
	expectedInfo << cone.GetInformation() << endl;
	expectedInfo << cylinder.GetInformation() << endl;
	expectedInfo << par.GetInformation() << endl;

	BOOST_CHECK_EQUAL(expectedInfo.str(), info);
}

BOOST_AUTO_TEST_CASE(Test_empty_compound)
{
	CCompound compound;
	CBody &compoundAsBody = compound;

	{
		bool exceptionCaught = false;
		try
		{
			compoundAsBody.GetDensity();
		}
		catch (const runtime_error &e)
		{
			(void)e;
			exceptionCaught = true;
		}
		BOOST_CHECK(exceptionCaught);
	}

	BOOST_CHECK_EQUAL(compoundAsBody.GetVolume(), 0);
	BOOST_CHECK_EQUAL(compoundAsBody.GetMass(), 0);
}

BOOST_AUTO_TEST_CASE(Test_direct_self_inclusion)
{
	shared_ptr<CCompound> compound(new CCompound());

	BOOST_CHECK_EQUAL(compound->AddBody(compound), false);
}

BOOST_AUTO_TEST_CASE(Add_compound_to_itself_chained)
{
	shared_ptr<CCompound> compound1(new CCompound());
	shared_ptr<CCompound> compound2(new CCompound());

	compound2->AddBody(shared_ptr<CParallelepiped>(new CParallelepiped(10, 3.6, 6, 40)));
	BOOST_CHECK_EQUAL(compound1->AddBody(compound2), true);
	BOOST_CHECK_EQUAL(compound2->AddBody(compound1), false);
}

BOOST_AUTO_TEST_SUITE_END()
