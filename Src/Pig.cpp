#include "Pig.h"

Pig::Pig(float in_x, float in_y, float width, float height)
	:
	Entity( in_x, in_y, width, height)
{
	xVel = 20.0f;
}

void Pig::move(float dt)
{
	x += xVel * dt;
	// Invert movement if pig reaches maximum displacement 
	if (x > m_initialX + m_maxDisplacement)
		xVel = -xVel;
	if (x < m_initialX)
		xVel = -xVel;
}

void Pig::enrage()
{
	
	// Double velocity when pig enrages
	xVel *= 2.5;
	enraged = true;
}

bool Pig::is_enraged()
{
	return enraged;
}