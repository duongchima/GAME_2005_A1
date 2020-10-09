#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}
PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{

	TextureManager::Instance()->draw("background", 0, 0);

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}


	drawDisplayList();
	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	if (launching)
	{
		Launch();
	}

	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Plane Sprite
	m_pPlaneSprite = new Plane();
	addChild(m_pPlaneSprite);

	// Detonator Sprite
	m_pDetonator = new Detonator();
	addChild(m_pDetonator);

	/*Player Sprite*/
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(500.0f, 200.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(700.0f, 200.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 40.0f);

	m_pStepLabel = new Label("1. Click Reset || 2. Adjust variables || 3. Click Fire || 4. Repeat", "Consolas");
	m_pStepLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 60.0f);

	addChild(m_pInstructionsLabel);
	addChild(m_pStepLabel);

}

void PlayScene::Launch()
{
	newVelocity.x = Vo * cos(angle * deg2rad) * 4.4; // Calculate what the new x velocity will be given the inputs.
	newVelocity.y = Vo * -sin(angle * deg2rad) * 4.4; // Same for y velocity.

	newAcceleration = glm::vec2(0.0f, gravity); // Set some acceleration (just gravity).


	// Calculate the new position using a small timestep and the current position of the detonator.
	newPosition = m_pDetonator->getTransform()->position + (glm::vec2(newVelocity.x, newVelocity.y) * initialTime)
		+ ((0.5f * newAcceleration) * (accTime * accTime));

	std::cout << "Position x: " << newPosition.x << std::endl;

	if (launching)
	{
		accTime += initialTime;

		m_pDetonator->getTransform()->position = newPosition;
	}
	if (m_pDetonator->getTransform()->position.y >= 500.0f)
	{
		launching = false;
	}

}

void PlayScene::StartLaunch()
{
	launching = true;
}

void PlayScene::Reset()
{
	m_pDetonator->getTransform()->position = glm::vec2(50, 500);
	launching = false;
	angle = 15.88f;
	Vo = 95.0f;
	y_max = 0.0f;
	initialTime = 0.016667f;
	accTime = 0.016667f;
	gravity = 9.8f;
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Fire"))
	{
		if (m_pDetonator->getTransform()->position.y > 500.0f)
		{
			launching = false;
		}
		else if (m_pDetonator->getTransform()->position.y <= 500.0f)
			StartLaunch();
	}

	else if (ImGui::Button("Reset"))
	{
		Reset();
	}

	ImGui::Separator();
	
	ImGui::SliderFloat("Range", &m_pPlaneSprite->getTransform()->position.x, 180.0f, 750.0f);
	ImGui::SliderFloat("Angle", &angle, 0.0f, 90.0f);
	ImGui::SliderFloat("Gravity", &gravity, 0.0f, 10.0f);
	ImGui::SliderFloat("Velocity", &Vo, 0.0f, 125.0f);


	ImGui::Separator();
	//std::cout << "Velocity: " << newVelocity.x << std::endl;
	//std::cout << "Acceleration: "<< newAcceleration.y << std::endl;

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
