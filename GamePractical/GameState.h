#pragma once
class GameState
{
public:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

};

