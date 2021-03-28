#include "Player.h"
#include"GameInput.h"
#include <stdio.h>

bool deleteLine = true;

Player* Player::instance = NULL;

Player* Player::getInstance()
{
	if (instance == NULL) {
		instance = new Player();
	}
	return instance;
}
//comi
void Player::releaseInstance() {
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void Player::setBasketballQty(int qty) {
	this->basketballQty = qty;
}

int Player::getBasketballQty() {
	return basketballQty;
}

Player::Player()
{
	sprite = NULL;
	spriteBasketball = NULL;
	spriteTrajectory = NULL;
	texture = NULL;
	textureForce = NULL;
	textureBasketball = NULL;
	textureTrajectory = NULL;
	line = NULL;

	
}

Player::~Player()
{
}

void Player::Init()
{
	animationRow = 0;
	characterCurrentFrame = 0;
	animationTimer = 0;
	force = 0;
	forceTimer = 0;
	maxTimer = 20;
	maxAnimationTimer = 70;

	animationDuration = 1.0f / 8;
	speed = (1.0f / animationDuration) * 30;

	isMoving = false;
	lockForce = false;

	direction = D3DXVECTOR2(0, 0);
	directionBasketball = D3DXVECTOR2(1, -1);
	gravity = D3DXVECTOR2(0, 3);
	spriteCentre = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2(350, 458);
	scaling = D3DXVECTOR2(0.5f, 0.5f);

	characterSize.x = 178;
	characterSize.y = 132;

	Player::getInstance()->setBasketballQty(15);


	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &spriteBasketball);
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &spriteTrajectory);
	D3DXCreateLine(GameGraphic::getInstance()->getDevice(), &line);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "char_move.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 0),
		NULL, NULL, &texture);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "force.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &textureForce);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "basketball.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(247, 247, 247),
		NULL, NULL, &textureBasketball);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "trajectory.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &textureTrajectory);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 21, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = spriteRect.left + characterSize.x;
	spriteRect.bottom = spriteRect.top + characterSize.y;

	spriteRectForce.left = 0;
	spriteRectForce.top = 0;
	spriteRectForce.right = 237;
	spriteRectForce.bottom = 79;

	textRect.left = 0;
	textRect.top = -73;
	textRect.right = 60;
	textRect.bottom = 0;

	trajectory.left = 0;
	trajectory.top = 0;
	trajectory.right = 8;
	trajectory.bottom = 8;

}

void Player::Update()
{
	if (Player::getInstance()->basketballQty >= 1)
	{
		//Player movement update
		if (GameInput::getInstance()->KeyboardKeyHold(DIK_LEFT))
		{
			animationRow = 1;
			isMoving = true;
			direction.x = -1;
			direction.y = 0;
			animationDefault[0] = 1;

		}

		else if (GameInput::getInstance()->KeyboardKeyHold(DIK_RIGHT))
		{
			animationRow = 0;
			isMoving = true;
			direction.x = 1;
			direction.y = 0;
			animationDefault[1] = 1;
		}

		else {
			isMoving = false;
		}

		
		if (GameInput::getInstance()->KeyboardKeyHold(DIK_SPACE))
		{
			deleteLine = false;
			tempPos = position;
			if (force < 6 && lockForce == false) {
				if (forceTimer < maxTimer) {
					forceTimer += 1;
				}

				if (forceTimer >= maxTimer)
				{
					force++;
					forceTimer = 0;
					if (force == 5)
					{
						lockForce = true;
					}
				}

			}

			else if (force > 0 && lockForce == true) {
				if (forceTimer < maxTimer) {
					forceTimer += 1;
				}

				if (forceTimer >= maxTimer)
				{
					force--;
					forceTimer = 0;
					if (force == 1)
					{
						lockForce = false;
					}
				}
			}


			velocityBasketball = D3DXVECTOR2(directionBasketball.x * (force * 10.0f), directionBasketball.y * 40.0f);

			for (int i = 0; i < 7; i++)
			{
				tempPos += velocityBasketball / 2.5f;
				tempPos += gravity / 2.5f;
				nextPosition[i] = tempPos;
			}
		}

		else if (GameInput::getInstance()->previousKeyStateSpace[DIK_SPACE] == 2)
		{
			animationDefault[2] = 1;
			animationRow = 2;
			direction.x = 0;
			direction.y = 0;
			isMoving = true;
			if (forceTimer < maxAnimationTimer) {
				forceTimer++;
			}

			if (forceTimer >= maxAnimationTimer)
			{
				basketballPosition = position;
				Player::getInstance()->setBasketballQty(Player::getInstance()->getBasketballQty() - 1);
				force = 0;
				lockForce = false;

				Basketball* temp = Basketball::getBasketball(textureBasketball);
				temp->init(basketballPosition, velocityBasketball);
				basketballList.push_back(temp);

				GameInput::getInstance()->previousKeyStateSpace[DIK_SPACE] = 0;
				isMoving = false;
				forceTimer = 0;
				deleteLine = true;

			}

		}
	}

	if (position.x < 120) {
		position.x = 120;
	}

	else if (position.x > 590)
	{
		position.x = 590;
	}

}

void Player::FixedUpdate()
{
	//Player update
	if (isMoving)
	{
		animationTimer += 1 / 60.0f;
		D3DXVECTOR2 velocity = direction * (speed / 60.0f);
		position += velocity;
	}
	if (animationTimer >= animationDuration)
	{
		animationTimer -= animationDuration;
		characterCurrentFrame++;
		characterCurrentFrame %= 8;
	}
	
	spriteRect.top = animationRow * characterSize.y;
	spriteRect.left = characterSize.x * characterCurrentFrame;
	spriteRect.right = spriteRect.left + characterSize.x;
	spriteRect.bottom = spriteRect.top + characterSize.y;

	
	for (int i = 0; i < basketballList.size(); i++)
	{
		if (basketballList[i]->isUsing)
		{
			basketballList[i]->update();
		}

		else
		{
			basketballList.erase(basketballList.begin() + i);
		}
	}

}

void Player::AnimationDefault(){
	if (!isMoving && animationDefault[0] == 1)
	{
		characterCurrentFrame = 0;
		spriteRect.top = 1 * characterSize.y;
		spriteRect.left = characterSize.x * 0;
		spriteRect.right = spriteRect.left + characterSize.x;
		spriteRect.bottom = spriteRect.top + characterSize.y;
		animationDefault[0] = 0;
	}

	else if (!isMoving && animationDefault[1] == 1)
	{
		characterCurrentFrame = 0;
		spriteRect.top = 0 * characterSize.y;
		spriteRect.left = characterSize.x * 0;
		spriteRect.right = spriteRect.left + characterSize.x;
		spriteRect.bottom = spriteRect.top + characterSize.y;
		animationDefault[1] = 0;
	}

	else if (!isMoving && animationDefault[2] == 1)
	{
		characterCurrentFrame = 7;
		spriteRect.top = 2 * characterSize.y;
		spriteRect.left = characterSize.x * 7;
		spriteRect.right = spriteRect.left + characterSize.x;
		spriteRect.bottom = spriteRect.top + characterSize.y;
		animationDefault[2] = 0;
	}
}

void Player::Draw()
{
	AnimationDefault();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//PLAYER
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &position);
	sprite->SetTransform(&mat);
	D3DXVECTOR3 startP(87 - 27, 75 - 17, 0);
	sprite->Draw(texture, &spriteRect, &startP, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//FORCE BAR
	D3DXVECTOR3 startF(-50, -160, 0);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(textureForce, &spriteRectForce, NULL, &startF, D3DCOLOR_XRGB(255, 255, 255));

	//FORCE NUMBER
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &position);
	sprite->SetTransform(&mat);
	string forceStr = to_string(force);
	font->DrawText(sprite, forceStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();

	if (!deleteLine)
	{
		spriteTrajectory->Begin(D3DXSPRITE_ALPHABLEND);
		for (int i = 2; i < 7; i++)
		{
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &nextPosition[i]);
			spriteTrajectory->SetTransform(&mat);
			spriteTrajectory->Draw(textureTrajectory, &trajectory, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}

		spriteTrajectory->End();
	}
	
	else
	{

	}


	//line->Begin();
	//
	//line->Draw(nextPosition, 5, D3DCOLOR_XRGB(100, 255, 120));

	//line->End();


	for (int i = 0; i < basketballList.size(); i++)
	{
		basketballList[i]->draw(spriteBasketball);
	}
}

void Player::Release()
{
	line->Release();
	line = NULL;

	font->Release();
	font = NULL;

	Basketball::releaseAllBasketball();
	sprite->Release();
	sprite = NULL;

	spriteBasketball->Release();
	spriteBasketball = NULL;

	spriteTrajectory->Release();
	spriteTrajectory = NULL;

	textureBasketball->Release();
	textureBasketball = NULL;

	textureForce->Release();
	textureForce = NULL;

	//textureTrajectory->Release();
	//textureTrajectory = NULL;

	texture->Release();
	texture = NULL;

}

