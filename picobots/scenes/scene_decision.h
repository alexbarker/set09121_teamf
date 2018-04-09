#pragma once
#include "engine.h"

class DecisionScene : public Scene
{
public:
	void Load() override;
	void SetTitle();
	void SetBackground();
	void UnLoad() override;
	void Update(const double& dt) override;
	void Render() override;
};