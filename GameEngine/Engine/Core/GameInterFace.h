#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterFace
{
public : 
	GameInterFace() { }
	virtual ~GameInterFace() { }

	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};
#endif 