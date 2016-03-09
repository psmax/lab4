// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

using namespace std;

shared_ptr<CBody> AddBody();
vector<shared_ptr<CBody>> bodies;

string LCase(string str)
{
	transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

double EnterDouble(const char *text)
{
	double result;

	cout << text;
	while (!(cin >> result))
	{
		cout << "Invalid input! Try again: ";
		cin.clear();
		while (cin.get() != '\n');
	}

	return result;
}

shared_ptr<CBody> AddCone()
{
	double radius, height, density;

	radius = EnterDouble("Enter radius: ");
	height = EnterDouble("Enter height: ");
	density = EnterDouble("Enter density: ");

	return make_shared<CCone>(radius, height, density);
}

shared_ptr<CBody> AddCylinder()
{
	double radius, height, density;

	radius = EnterDouble("Enter radius: ");
	height = EnterDouble("Enter height: ");
	density = EnterDouble("Enter density: ");

	return make_shared<CCylinder>(radius, height, density);
}

shared_ptr<CBody> AddParallelepiped()
{
	double width, height, depth, density;

	width = EnterDouble("Enter width: ");
	height = EnterDouble("Enter height: ");
	depth = EnterDouble("Enter depth: ");
	density = EnterDouble("Enter density: ");

	return make_shared<CParallelepiped>(width, height, depth, density);
}

shared_ptr<CBody> AddSphere()
{
	double radius, density;

	radius = EnterDouble("Enter radius: ");
	density = EnterDouble("Enter density: ");

	return make_shared<CSphere>(radius, density);
}

shared_ptr<CBody> AddCompound()
{
	cout << "Enter bodies that compound would be consisting of:" << endl;

	shared_ptr<CCompound> compound = make_shared<CCompound>();

	shared_ptr<CBody> compoundPart;
	while (compoundPart = AddBody())
	{
		compound->AddBody(compoundPart);
	}

	// Не возвращаем пустое составное тело т.к. оно не имеет плотности
	if (compound->GetContentsCount() == 0)
	{
		cout << "Cannot add empty compound body" << endl;
		return nullptr;
	}
	else
	{
		return compound;
	}
}

shared_ptr<CBody> AddBody()
{
	string bodyName;
	shared_ptr<CBody> body;

	cin.clear();
	fflush(stdin);
	cout << "Enter body name (cone, cylinder, parallelepiped, sphere, compound)"
		" or empty string to exit" << endl;
	getline(cin, bodyName);

	bodyName = LCase(bodyName);

	if (bodyName == "cone")
	{
		body = AddCone();
	}
	else if (bodyName == "cylinder")
	{
		body = AddCylinder();
	}
	else if (bodyName == "parallelepiped")
	{
		body = AddParallelepiped();
	}
	else if (bodyName == "sphere")
	{
		body = AddSphere();
	}
	else if (bodyName == "compound")
	{
		body = AddCompound();

		if (!body)
		{
			body = AddBody();
		}
	}
	else
	{
		if (bodyName.empty())
		{
			return nullptr;
		}
		else
		{
			cout << "Invalid body name" << endl;
			return AddBody();
		}
	}

	return body;
}

bool MassCompareFunct(const shared_ptr<CBody> &a, const shared_ptr<CBody> &b)
{
	return a->GetMass() < b->GetMass();
}

double GetArchimedesForce(const shared_ptr<CBody> &body)
{
	static const double waterDensity = 1000;
	static const double g = 9.81;

	return (body->GetDensity() - waterDensity) * g * body->GetVolume();
}

bool FloatCompareFunct(const shared_ptr<CBody> &a, const shared_ptr<CBody> &b)
{
	return GetArchimedesForce(a) < GetArchimedesForce(b);
}

int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<CBody> body;

	while (body = AddBody())
	{
		bodies.push_back(body);
	}

	if (bodies.empty())
	{
		cout << "You didn't add any bodies" << endl;
		system("PAUSE");
		return 0;
	}

	shared_ptr<CBody> maxMass = *max_element(bodies.begin(), bodies.end(), MassCompareFunct);
	cout << "The body with the greatest mass is:" << endl;
	cout << maxMass->GetInformation() << endl << endl;

	shared_ptr<CBody> lightestInWater = *min_element(bodies.begin(), bodies.end(), FloatCompareFunct);
	cout << "The body which is lightest in water is:" << endl;
	cout << lightestInWater->GetInformation() << endl << endl;

	system("PAUSE");
	return 0;
}
