#pragma once
#include "engine.h"

class DecisionScene : public Scene
{
public:
	void Load() override;
	void SetBackground();
	void UnLoad() override;
	void Update(const double& dt) override;
	void Render() override;
};