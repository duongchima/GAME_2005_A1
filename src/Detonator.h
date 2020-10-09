#pragma once
#ifndef __DETONATOR__
#define __DETONATOR__

#include "Sprite.h"

class Detonator final : public Sprite {
public:
	Detonator();
	~Detonator();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
};
#endif