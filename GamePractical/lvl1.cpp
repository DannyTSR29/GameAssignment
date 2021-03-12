#include "lvl1.h"
#include "GameInput.h"
#include "GameStateManager.h"

//COMBINE BACKGROUND AND PLAYER
lvl1::lvl1() {
	dBackGround = new Background();
	dPlayer = new Player();

}

lvl1::~lvl1() {
	delete dBackGround;
	dBackGround = NULL;
	delete dPlayer;
	dPlayer = NULL;

}


void lvl1::Init() {
	dBackGround->Init();
	dPlayer->Init();
}

void lvl1::Update() {
	dPlayer->Update();
}

void lvl1::FixedUpdate() {
	dPlayer->FixedUpdate();
}

void lvl1::Draw() {
	dBackGround->Draw();
	dPlayer->Draw();
}

void lvl1::Release() {
	if (dBackGround) 
	{ delete dBackGround; dBackGround = nullptr; }
	dBackGround->Release();
	if (dPlayer) { delete dPlayer; dPlayer = nullptr; }
	dPlayer->Release();
}
