#pragma once
#include "SolidBody.h"

class CSphere final :
	public CSolidBody
{
public:
	CSphere(double radius, double density);
	~CSphere(void);

	double GetRadius() const;

	// ������, ���������������� ������ ������� �������, ������������� 
	// ��������� �� �������������� override
	double GetVolume() const override;
	std::string GetInformation() const override;

private:
	double m_radius;
};
