#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Detonator.h"
#include "Button.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void Launch();
	void StartLaunch();
	void Reset();


private:
	// IMGUI Function
	void GUI_Function();

	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;

	// Variables for detonator launching
	Detonator* m_pDetonator;

	glm::vec2 newVelocity;
	glm::vec2 newAcceleration;
	glm::vec2 newPosition;

	bool m_playerFacingRight;

	bool launching = false;

	const float deg2rad = 0.0174532925f;
	const float rad2deg = 57.295779513f;

	float angle = 0.0f;
	float Vo = 0.0f;
	float y_max = 0.0f;
	float initialTime = 0.016667f;
	float accTime = 0.016667f;
	float gravity = 9.8f;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;	
	Label* m_pStepLabel;
};

#endif /* defined (__PLAY_SCENE__) */