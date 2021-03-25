#include "Background.h"
#include <stdio.h>
bool run;
Background::Background() {
	sprite = NULL;
	spriteHoop = NULL;
	texture = NULL;
	textureHoop = NULL;
	line = NULL;
	lineBoard = NULL;
	position = D3DXVECTOR2(1100,200);
	scaling = D3DXVECTOR2(1.5f, 1.5f);
	speed = (1.0f) * 30;
	isMoving = true;
	lockMove = false;
	run = false;
	score = 0;
	frontScore = 0;
	backScore = 0;
}

Background::~Background() {

}

void Background::Init() {
	
	sound->Init();
	sound = new Sound("Background_music.wav", false);

	//Create Sprite Device
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &spriteHoop);
	D3DXCreateLine(GameGraphic::getInstance()->getDevice(), &line);
	D3DXCreateLine(GameGraphic::getInstance()->getDevice(), &lineBoard);

	//	Create texture. Study the documentation.
	//D3DXCreateTextureFromFile(dGraphic->d3dDevice, "bg1.png", &texture);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "background.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "hoopRight.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &textureHoop);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);


	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 1252;
	spriteRect.bottom = 624;

	spriteHoopRect.left = 0;
	spriteHoopRect.top = 0;
	spriteHoopRect.right = 60;
	spriteHoopRect.bottom = 106;

	spriteBoardRect.left = 47;
	spriteBoardRect.top = 3;
	spriteBoardRect.right = 51;
	spriteBoardRect.bottom = 65;

	spriteBoardFrontRect.left = 0;
	spriteBoardFrontRect.top = 0;
	spriteBoardFrontRect.right = 3;
	spriteBoardFrontRect.bottom = 3;

	spriteBoardBackRect.left = 0;
	spriteBoardBackRect.top = 0;
	spriteBoardBackRect.right = 15;
	spriteBoardBackRect.bottom = 3;

	spriteScoreFrontRect.left = 47;
	spriteScoreFrontRect.top = 63;
	spriteScoreFrontRect.right = 67;
	spriteScoreFrontRect.bottom = 65;

	spriteScoreBackRect.left = 100;
	spriteScoreBackRect.top = 64;
	spriteScoreBackRect.right = 120;
	spriteScoreBackRect.bottom = 66;

	textRect.left = 0;
	textRect.top = -100;
	textRect.right = 0;
	textRect.bottom = 0;

	trans = D3DXVECTOR2(665, 215);
	tran1 = D3DXVECTOR2(582, 215);
}

void Background::Update() {
	
	sound->play();
	sound->volumeDown();
	sound->Update();
	//else if (tempTimer >= 60)
	//{
	//	tempTimer = 0;
	//	timer += 1;
	//}

	if (checkCollisionBoard(Basketball::getInstance()->getPosition(), Basketball::getInstance()->spriteRectBasketball, position, spriteBoardRect))
	{
		D3DXVECTOR2 tempVelocity = D3DXVECTOR2(-20.0f, 10.0f);
		Basketball::getInstance()->setVelocity(tempVelocity);
	}

	if (checkCollisionsBoardFront(Basketball::getInstance()->getPosition(), Basketball::getInstance()->spriteRectBasketball, position, spriteBoardFrontRect))
	{
		D3DXVECTOR2 tempVelocity = D3DXVECTOR2(-40.0f, -25.0f);
		Basketball::getInstance()->setVelocity(tempVelocity);
	}

	if (checkCollisionsBoardBack(Basketball::getInstance()->getPosition(), Basketball::getInstance()->spriteRectBasketball, position, spriteBoardBackRect))
	{
		D3DXVECTOR2 tempVelocity = D3DXVECTOR2(-40.0f, -25.0f);
		Basketball::getInstance()->setVelocity(tempVelocity);
	}

	if (checkCollisionScoreFront(Basketball::getInstance()->getPosition(), Basketball::getInstance()->spriteRectBasketball, position, spriteScoreFrontRect))
	{
		frontScore = 1;
		run = true;
		D3DXVECTOR2 tempVelocity = D3DXVECTOR2(5.0f, 10.0f);
		Basketball::getInstance()->setVelocity(tempVelocity);
	}

	if (checkCollisionScoreBack(Basketball::getInstance()->getPosition(), Basketball::getInstance()->spriteRectBasketball, position, spriteScoreBackRect))
	{
		backScore = 1;
		run = true;
		D3DXVECTOR2 tempVelocity = D3DXVECTOR2(-5.0f, 10.0f);
		Basketball::getInstance()->setVelocity(tempVelocity);
	}

	//D3DXVECTOR2 velocity;
	//if (isMoving)
	//{
	//	if (position.x <= 1078 && lockMove==false) {
	//		direction.x = -1;
	//		direction.y = 0;
	//		velocity = direction * (speed / 60.0f);
	//		position += velocity;
	//		if (position.x <= 885) {
	//			lockMove = true;
	//			velocity.x = 0;
	//			velocity.y = 0;
	//		}
	//	}
	//	else if (position.x >= 883 && lockMove==true) {
	//		direction.x = 1;
	//		direction.y = 0;
	//		velocity = direction * (speed / 60.0f);
	//		position += velocity;
	//		if (position.x >= 1078) {
	//			lockMove = false;
	//		}
	//	}
	//}
	
}

void Background::FixedUpdate() {
	if (frontScore == 1 && run == false && backScore == 1 && run == false)
	{
		frontScore = 0;
		backScore = 0;
		score += 1;
	}

}

void Background::Draw() {
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &tran1);
	sprite->SetTransform(&mat);
	string ballStr = to_string(Player::getInstance()->getBasketballQty());
	font->DrawText(sprite, ballStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &trans);
	sprite->SetTransform(&mat);
	string scoreStr = to_string(score);
	font->DrawText(sprite, scoreStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();

	spriteHoop->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
	spriteHoop->SetTransform(&mat);
	spriteHoop->Draw(textureHoop, &spriteHoopRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	spriteHoop->End();

	line->Begin();
	line->Draw(basketballVertices, 5, D3DCOLOR_XRGB(100, 255, 120));

	line->Draw(boardVertices, 5, D3DCOLOR_XRGB(0, 0, 255));

	line->Draw(sBoardVerticesFront, 5, D3DCOLOR_XRGB(0, 255, 255));
	line->Draw(sBoardVerticesBack, 5, D3DCOLOR_XRGB(255, 0, 255));

	line->Draw(scoreVerticesFront, 5, D3DCOLOR_XRGB(100, 255, 120));
	line->Draw(scoreVerticesBack, 5, D3DCOLOR_XRGB(255, 0, 0));


	line->End();


}

void Background::Release() {
	
	sound->Release();
	sound = NULL;

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	line->Release();
	line = NULL;

	lineBoard->Release();
	lineBoard = NULL;
}

bool Background::checkCollisionBoard(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionBoard, RECT rectBoard) {
	rectBasketball.right = positionBasketball.x + rectBasketball.right - rectBasketball.left;
	rectBasketball.left = positionBasketball.x;
	rectBasketball.bottom = positionBasketball.y + rectBasketball.bottom - rectBasketball.top;
	rectBasketball.top = positionBasketball.y;

	rectBoard.right = positionBoard.x + 70 + rectBoard.right - rectBoard.left;
	rectBoard.left = positionBoard.x + 70;
	rectBoard.bottom = positionBoard.y +35 + rectBoard.bottom - rectBoard.top;
	rectBoard.top = positionBoard.y + 5;

	basketballVertices[0] = D3DXVECTOR2(rectBasketball.left, rectBasketball.top);
	basketballVertices[1] = D3DXVECTOR2(rectBasketball.right, rectBasketball.top);
	basketballVertices[2] = D3DXVECTOR2(rectBasketball.right, rectBasketball.bottom);
	basketballVertices[3] = D3DXVECTOR2(rectBasketball.left, rectBasketball.bottom);
	basketballVertices[4] = D3DXVECTOR2(rectBasketball.left, rectBasketball.top);

	boardVertices[0] = D3DXVECTOR2(rectBoard.left, rectBoard.top);
	boardVertices[1] = D3DXVECTOR2(rectBoard.right, rectBoard.top);
	boardVertices[2] = D3DXVECTOR2(rectBoard.right, rectBoard.bottom);
	boardVertices[3] = D3DXVECTOR2(rectBoard.left, rectBoard.bottom);
	boardVertices[4] = D3DXVECTOR2(rectBoard.left, rectBoard.top);

	if (rectBasketball.bottom < rectBoard.top) { return false; }
	if (rectBasketball.top > rectBoard.bottom) { return false; }
	if (rectBasketball.right < rectBoard.left) { return false; }
	if (rectBasketball.left > rectBoard.right) { return false; }

	return true;
}

bool Background::checkCollisionsBoardFront(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionBoard, RECT rectBoard) {
	rectBasketball.right = positionBasketball.x + rectBasketball.right - rectBasketball.left;
	rectBasketball.left = positionBasketball.x;
	rectBasketball.bottom = positionBasketball.y + rectBasketball.bottom - rectBasketball.top;
	rectBasketball.top = positionBasketball.y;

	//1100 200
	rectBoard.right = positionBoard.x +5 + rectBoard.right - rectBoard.left;//1102
	rectBoard.left = positionBoard.x + 5; //1100
	rectBoard.bottom = positionBoard.y +100 + rectBoard.bottom - rectBoard.top; //202
	rectBoard.top = positionBoard.y + 100; //200

	sBoardVerticesFront[0] = D3DXVECTOR2(rectBoard.left, rectBoard.top);
	sBoardVerticesFront[1] = D3DXVECTOR2(rectBoard.right, rectBoard.top);
	sBoardVerticesFront[2] = D3DXVECTOR2(rectBoard.right, rectBoard.bottom);
	sBoardVerticesFront[3] = D3DXVECTOR2(rectBoard.left, rectBoard.bottom);
	sBoardVerticesFront[4] = D3DXVECTOR2(rectBoard.left, rectBoard.top);


	if (rectBasketball.bottom < rectBoard.top) { return false; }
	if (rectBasketball.top > rectBoard.bottom) { return false; }
	if (rectBasketball.right < rectBoard.left) { return false; }
	if (rectBasketball.left > rectBoard.right) { return false; }

	return true;
}

bool Background::checkCollisionsBoardBack(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionBoard, RECT rectBoard) {
	rectBasketball.right = positionBasketball.x + rectBasketball.right - rectBasketball.left;
	rectBasketball.left = positionBasketball.x;
	rectBasketball.bottom = positionBasketball.y + rectBasketball.bottom - rectBasketball.top;
	rectBasketball.top = positionBasketball.y;

	//1100 200
	rectBoard.right = positionBoard.x + 55 + rectBoard.right - rectBoard.left;//1002
	rectBoard.left = positionBoard.x + 55; //1000
	rectBoard.bottom = positionBoard.y +100 + rectBoard.bottom - rectBoard.top; //202
	rectBoard.top = positionBoard.y + 100; //200

	sBoardVerticesBack[0] = D3DXVECTOR2(rectBoard.left, rectBoard.top);
	sBoardVerticesBack[1] = D3DXVECTOR2(rectBoard.right, rectBoard.top);
	sBoardVerticesBack[2] = D3DXVECTOR2(rectBoard.right, rectBoard.bottom);
	sBoardVerticesBack[3] = D3DXVECTOR2(rectBoard.left, rectBoard.bottom);
	sBoardVerticesBack[4] = D3DXVECTOR2(rectBoard.left, rectBoard.top);

	if (rectBasketball.bottom < rectBoard.top) { return false; }
	if (rectBasketball.top > rectBoard.bottom) { return false; }
	if (rectBasketball.right < rectBoard.left) { return false; }
	if (rectBasketball.left > rectBoard.right) { return false; }

	return true;
}

bool Background::checkCollisionScoreFront(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionScore, RECT rectScore) {
	rectBasketball.right = positionBasketball.x + rectBasketball.right - rectBasketball.left;
	rectBasketball.left = positionBasketball.x;
	rectBasketball.bottom = positionBasketball.y + rectBasketball.bottom - rectBasketball.top;
	rectBasketball.top = positionBasketball.y;

	rectScore.right = positionScore.x + 10 + rectScore.right - rectScore.left;
	rectScore.left = positionScore.x + 10;
	rectScore.bottom = positionScore.y + 105 + rectScore.bottom - rectScore.top; 
	rectScore.top = positionScore.y + 105;

	scoreVerticesFront[0] = D3DXVECTOR2(rectScore.left, rectScore.top);
	scoreVerticesFront[1] = D3DXVECTOR2(rectScore.right, rectScore.top);
	scoreVerticesFront[2] = D3DXVECTOR2(rectScore.right, rectScore.bottom);
	scoreVerticesFront[3] = D3DXVECTOR2(rectScore.left, rectScore.bottom);
	scoreVerticesFront[4] = D3DXVECTOR2(rectScore.left, rectScore.top);

	run = false;

	if (rectBasketball.bottom < rectScore.top) { return false; }
	if (rectBasketball.top > rectScore.bottom) { return false; }
	if (rectBasketball.right < rectScore.left) { return false; }
	if (rectBasketball.left > rectScore.right) { return false; }

	return true;
}

bool Background::checkCollisionScoreBack(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionScore, RECT rectScore) {
	rectBasketball.right = positionBasketball.x + rectBasketball.right - rectBasketball.left;
	rectBasketball.left = positionBasketball.x;
	rectBasketball.bottom = positionBasketball.y + rectBasketball.bottom - rectBasketball.top;
	rectBasketball.top = positionBasketball.y;

	rectScore.right = positionScore.x + 30 + rectScore.right - rectScore.left;
	rectScore.left = positionScore.x + 30;
	rectScore.bottom = positionScore.y + 105 + rectScore.bottom - rectScore.top;
	rectScore.top = positionScore.y + 105;

	scoreVerticesBack[0] = D3DXVECTOR2(rectScore.left, rectScore.top);
	scoreVerticesBack[1] = D3DXVECTOR2(rectScore.right, rectScore.top);
	scoreVerticesBack[2] = D3DXVECTOR2(rectScore.right, rectScore.bottom);
	scoreVerticesBack[3] = D3DXVECTOR2(rectScore.left, rectScore.bottom);
	scoreVerticesBack[4] = D3DXVECTOR2(rectScore.left, rectScore.top);

	run = false;

	if (rectBasketball.bottom < rectScore.top) { return false; }
	if (rectBasketball.top > rectScore.bottom) { return false; }
	if (rectBasketball.right < rectScore.left) { return false; }
	if (rectBasketball.left > rectScore.right) { return false; }

	return true;
}

