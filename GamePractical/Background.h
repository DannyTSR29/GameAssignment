#pragma once
#include "GameWin.h"
#include "GameGraphic.h"
#include "Basketball.h"
#include "Player.h"
#include <fmod.hpp>

class Background
{
private:
    LPDIRECT3DTEXTURE9 texture;
    LPDIRECT3DTEXTURE9 textureHoop;
    LPD3DXSPRITE sprite;
    LPD3DXSPRITE spriteHoop;
    LPD3DXLINE line;
    LPD3DXLINE lineBoard;

    FMOD::System* system;               //Fmod system object
    FMOD::Sound* bgmusic;
    FMOD::Channel* bgChannel;

    LPD3DXFONT font;
    RECT spriteRect;
    RECT textRect;

    RECT spriteHoopRect;

    RECT spriteBoardRect;

    RECT spriteBoardFrontRect;
    RECT spriteBoardBackRect;

    RECT spriteScoreFrontRect;
    RECT spriteScoreBackRect;

    D3DXMATRIX mat;

    D3DXVECTOR2 spriteCentre;
    D3DXVECTOR2 trans;
    D3DXVECTOR2 position;
    D3DXVECTOR2 scaling;
    D3DXVECTOR2 direction;
    D3DXVECTOR2 directionmove;
    D3DXVECTOR2 basketballVertices[5];
    D3DXVECTOR2 boardVertices[5];
    D3DXVECTOR2 sBoardVerticesFront[5];
    D3DXVECTOR2 sBoardVerticesBack[5];
    D3DXVECTOR2 scoreVerticesFront[5];
    D3DXVECTOR2 scoreVerticesBack[5];

    bool lockMove;
    float rotation;
    bool isMoving;
    float speed;
    float animationTimer;

    int score;
    int frontScore, backScore;

public:
    Background();
    ~Background();

    void Init();
    void Update();
    void FixedUpdate();
    void Draw();
    void Release();


    bool checkCollisionBoard(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionBoard, RECT rectBoard);

    bool checkCollisionsBoardFront(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionBoard, RECT rectBoard);
    bool checkCollisionsBoardBack(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionBoard, RECT rectBoard);

    bool checkCollisionScoreFront(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionScore, RECT rectScore);
    bool checkCollisionScoreBack(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionScore, RECT rectScore);

};