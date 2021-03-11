#include "lvl2.h"
#include "GameStateManager.h"

lvl2::lvl2() {

}

lvl2::~lvl2() {

}

void lvl2::inti() {
}

void lvl2::update() {
	if (GameInput::getInstance()->isKeyDown(DIK_0))
	{
		GameStateManager::getInstance()->changeGameState(0);
	}
}

void lvl2::draw() {

}

void lvl2::release() {


}
