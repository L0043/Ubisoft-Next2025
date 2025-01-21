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
#include "SegmentedWall.h"
#include <time.h>
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
Echo::Map* pMap2;
Echo::Map* pMap3;
Echo::AABB* aabb1;
Echo::Player* pClub;
Echo::Ball* pBall;
Echo::Goal* pGoal;


void Init()
{
	srand(time(NULL));

	pMap1 = new Echo::Map();
	pMap2 = new Echo::Map();
	pMap3 = new Echo::Map();
	pLevel = new Echo::Level(EventManager);
	pMap1->AttachLevel(pLevel);
	pMap2->AttachLevel(pLevel);
	pMap3->AttachLevel(pLevel);

	// topLeft = 60, 680
	// topRight = 940, 680
	// bottomLeft = 60, 60
	// bottomRight= 940, 60
	// center = 470, 340
	pBall = new Echo::Ball(Vector2(70, 660), 15.0f, 20, pLevel);
	pClub = new Echo::Player(Vector2(0, 0), Vector2(40, 20), 0.0f, pBall, Echo::MeshType::Arrow);
	
	pLevel->AddToLayout(pBall);

	float wallThickness = 20;
	float ballFit = pBall->GetRadius() * 2 * 2; // value that will gaurnetee that the ball fits
	int numberOfDivisions = 40;
	

	pGoal = new Echo::Goal(Echo::MeshType::Circle, Echo::ObjectType::Interactible, { 686, 266 }, { 25, 8 }, { 0,1,0,1 }, pLevel);

	#pragma region Map1
	{
		Echo::SegmentedWall* border0 = new Echo::SegmentedWall({ 40, 370 }, { wallThickness, 680 }, numberOfDivisions, pLevel, pMap1);		// left
		border0->m_Name = "Left";
		Echo::SegmentedWall* border1 = new Echo::SegmentedWall({ 500, 40 }, { 900, wallThickness }, numberOfDivisions, pLevel, pMap1);		// bottom
		border1->m_Name = "Bottom";
		Echo::SegmentedWall* border2 = new Echo::SegmentedWall({ 500, 700 }, { 900, wallThickness }, numberOfDivisions, pLevel, pMap1);		// top
		border2->m_Name = "Top";
		Echo::SegmentedWall* border3 = new Echo::SegmentedWall({ 960, 370 }, { wallThickness, 680 }, numberOfDivisions, pLevel, pMap1);		// right
		border3->m_Name = "Right";
		Echo::SegmentedWall* leftLongWall = new Echo::SegmentedWall({ 220, 680 - ballFit }, { 340, wallThickness }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* Obtrusion = new Echo::SegmentedWall({ 330, 700 - ballFit }, { wallThickness, 20 }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* Obtrusion1 = new Echo::SegmentedWall({ 500, 620 }, { wallThickness, 140 }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* cube = new Echo::SegmentedWall({ 700, 550 }, { 100, 100 }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* wall = new Echo::SegmentedWall({ 500, 420 }, { 780, wallThickness }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* wallLeftVert = new Echo::SegmentedWall({ 60 + ballFit, 255 }, { wallThickness, 310 }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* wallMidVert = new Echo::SegmentedWall({ 686, 354 }, { 80, 114 }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* wallRightVert = new Echo::SegmentedWall({ 940 - ballFit, 60 + 145 }, { wallThickness, 310 }, numberOfDivisions, pLevel, pMap1);
		Echo::SegmentedWall* wallLowerHori = new Echo::SegmentedWall({ 390, 260 }, { 300,  wallThickness }, numberOfDivisions, pLevel, pMap1);
		pMap1->AddGeometry(border0);
		pMap1->AddGeometry(border1);
		pMap1->AddGeometry(border2);
		pMap1->AddGeometry(border3);
		pMap1->AddGeometry(leftLongWall);
		pMap1->AddGeometry(Obtrusion);
		pMap1->AddGeometry(Obtrusion1);
		pMap1->AddGeometry(cube);
		pMap1->AddGeometry(wall);
		pMap1->AddGeometry(wallLeftVert);
		pMap1->AddGeometry(wallMidVert);
		pMap1->AddGeometry(wallRightVert);
		pMap1->AddGeometry(wallLowerHori);
		pMap1->SetGoalStartingPosition({ 686, 266 });
		pMap1->SetStartingPosition({ 70, 660 });
	}
#pragma endregion

	#pragma region Map2
	{
		Echo::SegmentedWall* border0 = new Echo::SegmentedWall({ 40, 370 }, { wallThickness, 680 }, numberOfDivisions, pLevel, pMap2);		// left
		border0->m_Name = "Left";
		Echo::SegmentedWall* border1 = new Echo::SegmentedWall({ 500, 40 }, { 900, wallThickness }, numberOfDivisions, pLevel, pMap2);		// bottom
		border1->m_Name = "Bottom";
		Echo::SegmentedWall* border2 = new Echo::SegmentedWall({ 500, 700 }, { 900, wallThickness }, numberOfDivisions, pLevel, pMap2);		// top
		border2->m_Name = "Top";
		Echo::SegmentedWall* border3 = new Echo::SegmentedWall({ 960, 370 }, { wallThickness, 680 }, numberOfDivisions, pLevel, pMap2);		// right
		border3->m_Name = "Right";
		Echo::SegmentedWall* firstWall = new Echo::SegmentedWall({ 120 + ballFit, 420 }, { wallThickness,550 }, numberOfDivisions, pLevel, pMap2);
		Echo::SegmentedWall* secondWall = new Echo::SegmentedWall({ 320 + ballFit, 320 }, { wallThickness,550 }, numberOfDivisions, pLevel, pMap2);
		Echo::SegmentedWall* thirdWall = new Echo::SegmentedWall({ 520 + ballFit, 420 }, { wallThickness,550 }, numberOfDivisions, pLevel, pMap2);
		Echo::SegmentedWall* fourthWall = new Echo::SegmentedWall({ 720 + ballFit, 320 }, { wallThickness,550 }, numberOfDivisions, pLevel, pMap2);
		pMap2->AddGeometry(border0);
		pMap2->AddGeometry(border1);
		pMap2->AddGeometry(border2);
		pMap2->AddGeometry(border3);
		pMap2->AddGeometry(firstWall);
		pMap2->AddGeometry(secondWall);
		pMap2->AddGeometry(thirdWall);
		pMap2->AddGeometry(fourthWall);
		pMap2->SetGoalStartingPosition({ 880, 120 });
		pMap2->SetStartingPosition({ 70, 660 });
	}
#pragma endregion
	
	#pragma region Map3
	{
		Echo::SegmentedWall* border0 = new Echo::SegmentedWall({ 40, 370 }, { wallThickness, 680 }, numberOfDivisions, pLevel, pMap3);		// left
		border0->m_Name = "Left";
		Echo::SegmentedWall* border1 = new Echo::SegmentedWall({ 500, 40 }, { 900, wallThickness }, numberOfDivisions, pLevel, pMap3);		// bottom
		border1->m_Name = "Bottom";
		Echo::SegmentedWall* border2 = new Echo::SegmentedWall({ 500, 700 }, { 900, wallThickness }, numberOfDivisions, pLevel, pMap3);		// top
		border2->m_Name = "Top";
		Echo::SegmentedWall* border3 = new Echo::SegmentedWall({ 960, 370 }, { wallThickness, 680 }, numberOfDivisions, pLevel, pMap3);		// right
		border3->m_Name = "Right";
		Echo::SegmentedWall* block = new Echo::SegmentedWall({ 540, 370 }, { 200, 200 }, numberOfDivisions, pLevel, pMap3);
		Echo::SegmentedWall* leg0 = new Echo::SegmentedWall({ 540, 220 }, { 75, 150 }, numberOfDivisions, pLevel, pMap3, true, { 500, 220 }, { 580, 220 });
		Echo::SegmentedWall* leg1 = new Echo::SegmentedWall({ 540, 520 }, { 75, 150 }, numberOfDivisions, pLevel, pMap3);
		pMap3->AddGeometry(border0);
		pMap3->AddGeometry(border1);
		pMap3->AddGeometry(border2);
		pMap3->AddGeometry(border3);
		pMap3->AddGeometry(block);
		pMap3->AddGeometry(leg0);
		pMap3->AddGeometry(leg1);
		pMap3->SetStartingPosition({ 70, 370 });
		pMap3->SetGoalStartingPosition({ 940 - pGoal->GetSize().x, 370});
	}
#pragma endregion


	//pLevel->AddMap(pMap1);
	pLevel->AddMap(pMap2);
	//pLevel->AddMap(pMap3);
	pLevel->ChangeMap();

	pLevel->AddToLayout(pGoal);
	pBall->SetStartingPosition(pLevel->GetMap()->GetStartingPosition());
	pBall->SetPosition(pLevel->GetMap()->GetStartingPosition());
	pGoal->SetStartingPosition(pLevel->GetMap()->GetGoalStartingPosition());
	pGoal->SetPosition(pLevel->GetMap()->GetGoalStartingPosition());
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
bool pressedLastFrame = false;
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
	
	if (App::IsKeyPressed('Q') && !pressedLastFrame)
	{
		for(Echo::Object* obj : pLevel->GetLayout())
		{
			obj->SetDebug(true);
		}
		
		pressedLastFrame = true;
	}
	else if(App::IsKeyPressed('Q') == false && pressedLastFrame)
	{
		for (Echo::Object* obj : pLevel->GetLayout())
		{
			obj->SetDebug(false);
		}
		pressedLastFrame = false;
	}
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

	std::string scoreText{ "Score: " + std::to_string(pGoal->GetScore())};
	std::string strokesText{ "Strokes: " + std::to_string(pClub->GetStrokes())};

	App::Print(150, APP_INIT_WINDOW_HEIGHT - 20, scoreText.c_str());
	App::Print(250, APP_INIT_WINDOW_HEIGHT - 20, strokesText.c_str());

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