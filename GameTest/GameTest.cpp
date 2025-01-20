///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "AABB.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "Level.h"
#include "Goal.h"
#include "Map.h"
//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite;
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------
Echo::EventManager EventManager;
Echo::Level* pLevel;
Echo::Map* pMap1;
Echo::AABB* aabb1;
Echo::Player* pClub;
Echo::Ball* pBall;
Echo::Goal* pGoal;

void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	const float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(1.0f);
	//------------------------------------------------------------------------
	
	pMap1 = new Echo::Map();
	pLevel = new Echo::Level(pMap1, EventManager);
	pMap1->AttachLevel(pLevel);

	//pLevel->LoadMap(pMap1);


	float wallThickness = 20;
	//aabb1 = new Echo::AABB(Vector2(400, 400), 100, 100,0, Vector4(1,1,1,1));
	pBall = new Echo::Ball(Vector2(150, 150), 15.0f, 20, pLevel);
	pClub = new Echo::Player(Vector2(0, 0), Vector2(20, 20), 0.0f, pBall);
	Echo::Wall* border0 = new Echo::Wall({ 40, 400 }, { wallThickness, 700 }, 0, pLevel);	//left
	Echo::Wall* border1 = new Echo::Wall({ 500, 40 }, { 900, wallThickness }, 0, pLevel);	//bottom
	Echo::Wall* border2 = new Echo::Wall({ 500, 760 }, { 900, wallThickness }, 0,pLevel);	//top
	Echo::Wall* border3 = new Echo::Wall({ 960, 400 }, { wallThickness, 700 }, 0,pLevel);	//left

	pGoal = new Echo::Goal(Echo::MeshType::Circle, Echo::ObjectType::interactible, { 600, 400 }, { 30, 20 }, { 0,1,0,1 }, pLevel,*testSprite);

	//pMap1->AddGeometry(pBall);
	//pMap1->AddGeometry(border0);
	//pMap1->AddGeometry(border1);
	//pMap1->AddGeometry(border2);
	//pMap1->AddGeometry(border3);
	//pMap1->AddGeometry(pGoal);
	////
	//pLevel->LoadMap(pMap1);

}

void StartFrame()
{
	// handle collision events here
	EventManager.ProcessQueue();
}

void EndFrame()
{
	pLevel->DetectCollisions();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	// converting the deltaTime to be in seconds, 
	// this is so I can keep the member variable values as numbers that make sense to me 
	// without them being extremely fast (1.0 >=)
	// this is because I am extremely used to using Unity
	float dtSeconds = (deltaTime / 1000);

	pLevel->Update(dtSeconds);

	pClub->Update(dtSeconds);
	
	EndFrame();
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	// this is the closest I can get to the start without modifying the API
	StartFrame();

	pLevel->Draw();
	
	pClub->Draw();

	std::string text{ "ball x: " + std::to_string(pBall->GetPosition().x)};

	std::string text2{ "ball y: " + std::to_string(pBall->GetPosition().y) };

	App::Print(150, 100, text.c_str());
	App::Print(150, 150, text2.c_str());

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	//------------------------------------------------------------------------
}