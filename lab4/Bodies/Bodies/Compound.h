#pragma once
#include "Body.h"
#include <vector>
#include <memory>

class CCompound final :
	public CBody
{
public:
	CCompound();
	~CCompound();

	// Добавление тела внутрь составного тела
	bool AddBody(const std::shared_ptr<CBody> &body);

	// Возвращает количество тел, входящих в составное тело
	size_t GetContentsCount() const;

	virtual double GetVolume() const override;
	virtual double GetDensity() const override;
	virtual double GetMass() const override;
	virtual std::string GetInformation() const override;

private:
	std::vector<std::shared_ptr<CBody>> m_contents;

	bool HasBodyInside(const CBody *body) const;
};
