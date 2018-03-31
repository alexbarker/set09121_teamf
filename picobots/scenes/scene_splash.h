#pragma once
#include "engine.h"

class SplashScene : public Scene
{
public:
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void Render() override;
};
