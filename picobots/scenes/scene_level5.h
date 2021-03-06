#pragma once
#include "engine.h"

class Level5Scene : public Scene {
public:
	void Load() override;
	void UnLoad() override;
	void SetTitle();
	void SetBackground();
	void Update(const double& dt) override;
	void Render() override;
};

