#include "lvl2.h"
#include "GameStateManager.h"

lvl2::lvl2() {

}

lvl2::~lvl2() {

}

void lvl2::Init() {
}

void lvl2::Update() {
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_0))
	{
		GameStateManager::getInstance()->changeGameState(0);
	}
}

void lvl2::FixedUpdate() {

}

void lvl2::Draw() {

}

void lvl2::Release() {


}

