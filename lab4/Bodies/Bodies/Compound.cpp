#include "stdafx.h"
#include "Compound.h"
#include "Cylinder.h"
#include <numeric>
#include <algorithm>
#include <sstream>

using namespace std;

CCompound::CCompound(void)
{
}

CCompound::~CCompound(void)
{
}

bool CCompound::AddBody(const shared_ptr<CBody> &body)
{
	if (this == body.get())
		return false;

	shared_ptr<CCompound> bodyAsCompound = dynamic_pointer_cast<CCompound>(body);
	if (bodyAsCompound.get() != nullptr)
	{
		if (bodyAsCompound->HasBodyInside(this))
		{
			return false;
		}
	}

	m_contents.push_back(body);
	return true;
}

size_t CCompound::GetContentsCount() const
{
	return m_contents.size();
}

double CCompound::GetVolume() const
{
	return accumulate(m_contents.cbegin(), m_contents.cend(), 0.0,
		[](double sum, const shared_ptr<CBody> &body){ return sum + body->GetVolume(); });
}

double CCompound::GetMass() const
{
	return accumulate(m_contents.cbegin(), m_contents.cend(), 0.0,
		[](double sum, const shared_ptr<CBody> &body){ return sum + body->GetMass(); });
}

double CCompound::GetDensity() const
{
	if (m_contents.size() == 0)
		throw runtime_error("Empty body has no density");

	return (GetMass() / GetVolume());
}

bool CCompound::HasBodyInside(const CBody *body) const
{
	for (auto & curBody : m_contents)
	{
		if (body == curBody.get())
		{
			return true;
		}

		shared_ptr<CCompound> curBodyAsCompound = dynamic_pointer_cast<CCompound>(curBody);
		if (curBodyAsCompound)
		{
			if (curBodyAsCompound->HasBodyInside(body))
			{
				return true;
			}
		}
	}

	return false;
}

std::string CCompound::GetInformation() const
{
	std::ostringstream info;

	info << "Compound body composed of " << m_contents.size() << " bodies" << endl;
	info << "With mass " << GetMass() << ", volume " << GetVolume() << " and density " << GetDensity() << endl;
	info << "Contents:" << endl;
	for (auto body : m_contents)
		info << body->GetInformation() << endl;

	return info.str();
}
