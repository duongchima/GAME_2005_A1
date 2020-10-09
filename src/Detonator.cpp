#include "Detonator.h"
#include "TextureManager.h"
#include <iostream>
#include <cmath>
#include <iomanip>

const double PI = 3.141592654, g = -9.8;

Detonator::Detonator()
{
	TextureManager::Instance()->load("../Assets/sprites/detonator.png", "detonator");
	setWidth(65);
	setHeight(65);

	getTransform()->position = glm::vec2(50.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	setType(DETONATOR);
}

Detonator::~Detonator()
= default;

void Detonator::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("detonator", x, y, 0.0f, 255, true);
}

void Detonator::update()
{

}

void Detonator::clean()
{
}