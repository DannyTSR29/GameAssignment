#pragma once
class GameState
{
public:

	virtual void inti() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void release() = 0;
};

