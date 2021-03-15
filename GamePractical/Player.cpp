#include "Player.h"
#include"GameInput.h"
#include <stdio.h>

Player::Player()
{
	sprite = NULL;
	texture = NULL;
	rotation = 0;
	position.x = 350;

	characterCurrentFrame = 0;
	animationTimer = 0;
	animationDuration = 1.0f / 8;
	speed = (1.0f / animationDuration) * 30;
	animationRow = 0;
	isMoving = false;
	direction.x = 0;
	direction.y = 1;
	force = 0;
	forceTimer = 0;
	maxTimer = 20;
	maxAnimationTimer = 70;
	lockForce = false;

}

Player::~Player()
{
}

void Player::Init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "char_move.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 0),
		NULL, NULL, &texture);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);



	// Texture being used is 64 by 64:
	spriteCentre = D3DXVECTOR2(0, 0);
	// Screen position of the sprite
	position = D3DXVECTOR2(350, 458);
	// Rotate based on the time passed
	rotation += 0;
	// Build our matrix to rotate, scale and position our sprite
	scaling = D3DXVECTOR2(1.0f, 1.0f);

	//1443 / 8 = 178
	//264 / 2 = 126.67
	characterSize.x = 178;
	characterSize.y = 132;

	//Player init
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = spriteRect.left + characterSize.x;
	spriteRect.bottom = spriteRect.top + characterSize.y;


	textRect.left = 0;
	textRect.top = -75;
	textRect.right = 50;
	textRect.bottom = 0;
}

void Player::Update()
{
	//Player movement update
	if (GameInput::getInstance()->KeyboardKeyHold(DIK_LEFT))
	{
		animationRow = 1;
		isMoving = true;
		direction.x = -1;
		direction.y = 0;
		printf("LEFT\n");
		animationDefault[0] = 1;

	}
	
	else if (GameInput::getInstance()->KeyboardKeyHold(DIK_RIGHT))
	{
		animationRow = 0;
		isMoving = true;
		direction.x = 1;
		direction.y = 0;
		printf("RIGHT\n");
		animationDefault[1] = 1;
	}

	else {
		isMoving = false;
	}

	if (GameInput::getInstance()->KeyboardKeyHold(DIK_SPACE))
	{
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
	}

	//HOW TO DETECT SPACEKEY WHEN IT RELEASE, I USING ELSE AND THE CODITION STRAIGHT AWAY WILL BE SPACEPRESS = FALSE
	else if (GameInput::getInstance()->previousKeyStateSpace[DIK_SPACE] == 2)
	{
		animationDefault[2] = 1;
		lockForce = false;
		force = 0;
		animationRow = 2;
		direction.x = 0;
		direction.y = 0;
		isMoving = true;
		if (forceTimer < maxAnimationTimer) {
			forceTimer++;
		}
		printf("timer: %d\n", forceTimer);

		if (forceTimer >= maxAnimationTimer)
		{
			printf("more than");
			forceTimer = 0;
			GameInput::getInstance()->previousKeyStateSpace[DIK_SPACE] = 0;
			isMoving = false;

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

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);

}

void Player::AnimationDefault() {
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
		characterCurrentFrame = 0;
		spriteRect.top = 2 * characterSize.y;
		spriteRect.left = characterSize.x * 0;
		spriteRect.right = spriteRect.left + characterSize.x;
		spriteRect.bottom = spriteRect.top + characterSize.y;
		animationDefault[2] = 0;
	}
}

void Player::Draw()
{
	AnimationDefault();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	D3DXVECTOR3 startP(87 - 27, 75 - 17, 0);
	sprite->Draw(texture, &spriteRect, &startP, NULL, D3DCOLOR_XRGB(255, 255, 255));
	string forceStr = to_string(force);
	font->DrawText(sprite, forceStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void Player::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}